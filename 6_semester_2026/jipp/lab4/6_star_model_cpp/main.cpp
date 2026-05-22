#include <print>
#include <pthread.h>
#include <random>
#include <unistd.h>
#include <vector>

const int NUsers = 5;
const int NFrames = 100;
const useconds_t BaseBackoff = 2 * 1000;    // 2ms
const useconds_t MaxBackoff = 2000 * 1000;  // 2s
const useconds_t ProcessingTime = 1 * 1000; // 1ms
const useconds_t ThinkTime = 20 * 1000;     // 20ms

struct Frame {
  int From;
  int To;
};

class Switch {
public:
  pthread_mutex_t mutex;
  pthread_cond_t cond_frame_ready;
  pthread_cond_t cond_forward_done;

  Switch() {
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond_frame_ready, NULL);
    pthread_cond_init(&cond_forward_done, NULL);
  }

  ~Switch() {
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_frame_ready);
    pthread_cond_destroy(&cond_forward_done);
  }

  Frame *ActiveFrame = nullptr;
  bool ForwardDone = false;
  bool Quit = false;
};

class User {
public:
  pthread_mutex_t mutex;

  User() { pthread_mutex_init(&mutex, NULL); }

  ~User() { pthread_mutex_destroy(&mutex); }

  int IngressCount = 0;
  int FailCount = 0;
};

Switch sw;
std::vector<User> users(NUsers);
pthread_mutex_t io_mutex;

useconds_t randomThinkTime() {
  static thread_local std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<useconds_t> dist(0, ThinkTime);
  return dist(gen);
}

useconds_t exponentialBackoff(int attempt) {
  static thread_local std::mt19937 gen(std::random_device{}());
  uint64_t power = static_cast<uint64_t>(1) << attempt;
  uint64_t max_val = power * BaseBackoff;
  if (max_val > MaxBackoff) {
    max_val = MaxBackoff;
  }
  std::uniform_int_distribution<useconds_t> dist(
      0, static_cast<useconds_t>(max_val));
  return dist(gen);
}

void *userWorker(void *arg) {
  int id = *static_cast<int *>(arg);
  delete static_cast<int *>(arg);

  std::mt19937 gen(std::random_device{}());
  std::uniform_real_distribution<double> think_dist(
      0.0, static_cast<double>(ThinkTime));

  for (std::size_t i = 0; i < NFrames; ++i) {
    usleep(randomThinkTime());

    std::uniform_int_distribution<int> user_dist(1, NUsers);
    int targetID = user_dist(gen);

    Frame *frame = new Frame{id, targetID};
    int attempt = 1;

    while (true) {
      pthread_mutex_lock(&sw.mutex);
      if (sw.ActiveFrame == nullptr) {
        pthread_mutex_lock(&io_mutex);
        std::println(
            "User(id {}) successfully acquired Switch Lock for transfer {}.",
            id, i);
        pthread_mutex_unlock(&io_mutex);
        break;
      }
      pthread_mutex_unlock(&sw.mutex);

      pthread_mutex_lock(&users[id - 1].mutex);
      users[id - 1].FailCount++;
      pthread_mutex_unlock(&users[id - 1].mutex);

      useconds_t backoff = exponentialBackoff(attempt);

      pthread_mutex_lock(&io_mutex);
      std::println("User(id {}, transfer {}) found Switch busy. Backing off "
                   "for {} (attempt {}).",
                   id, i, std::to_string(backoff).c_str(), attempt);
      pthread_mutex_unlock(&io_mutex);

      usleep(backoff);
      attempt++;
    }

    sw.ActiveFrame = frame;
    sw.ForwardDone = false;

    pthread_cond_signal(&sw.cond_frame_ready);

    while (!sw.ForwardDone) {
      pthread_cond_wait(&sw.cond_forward_done, &sw.mutex);
    }

    pthread_mutex_unlock(&sw.mutex);
  }

  pthread_mutex_lock(&io_mutex);
  std::println("User(id {}) finished sending all {} Frames.", id, NFrames);
  pthread_mutex_unlock(&io_mutex);

  return nullptr;
}

void *switchTask(void *_) {
  while (true) {
    pthread_mutex_lock(&sw.mutex);

    while (sw.ActiveFrame == nullptr && !sw.Quit) {
      pthread_cond_wait(&sw.cond_frame_ready, &sw.mutex);
    }

    if (sw.Quit && sw.ActiveFrame == nullptr) {
      pthread_mutex_unlock(&sw.mutex);
      break;
    }

    if (sw.ActiveFrame != nullptr) {
      Frame *frame = sw.ActiveFrame;
      User &recipient = users[frame->To - 1];

      pthread_mutex_lock(&io_mutex);
      std::println("Switch: Received Frame from User {} destined for User {}. "
                   "Forwarding...",
                   frame->From, frame->To);
      pthread_mutex_unlock(&io_mutex);

      pthread_mutex_lock(&recipient.mutex);
      usleep(ProcessingTime);
      recipient.IngressCount++;
      pthread_mutex_unlock(&recipient.mutex);

      pthread_mutex_lock(&io_mutex);
      std::println(
          "Switch: Successfully delivered Frame from User {} to User {}.",
          frame->From, frame->To);
      pthread_mutex_unlock(&io_mutex);

      delete frame;
      sw.ActiveFrame = nullptr;
      sw.ForwardDone = true;

      pthread_cond_broadcast(&sw.cond_forward_done);
    }

    pthread_mutex_unlock(&sw.mutex);
  }
  return nullptr;
}

int main() {
  std::println("Starting star topology communication");

  pthread_mutex_init(&io_mutex, NULL);

  pthread_t dispatcher_thread;
  pthread_create(&dispatcher_thread, nullptr, switchTask, nullptr);

  pthread_t worker_threads[NUsers];
  for (std::size_t i = 0; i < NUsers; ++i) {
    int *id_arg = new int(i + 1);
    pthread_create(&worker_threads[i], nullptr, userWorker, id_arg);
  }

  for (std::size_t i = 0; i < NUsers; ++i) {
    pthread_join(worker_threads[i], nullptr);
  }

  pthread_mutex_lock(&sw.mutex);
  sw.Quit = true;
  pthread_cond_broadcast(&sw.cond_frame_ready);
  pthread_mutex_unlock(&sw.mutex);

  pthread_join(dispatcher_thread, nullptr);

  std::println("\nStar topology communication complete.");
  int recv = 0;
  int fail = 0;

  for (std::size_t i = 0; i < NUsers; ++i) {
    pthread_mutex_lock(&users[i].mutex);
    int received = users[i].IngressCount;
    int failCount = users[i].FailCount;
    pthread_mutex_unlock(&users[i].mutex);

    recv += received;
    fail += failCount;
    std::println("User(id {}) received {} Frames ({} failed attempts).", i + 1,
                 received, failCount);
  }

  std::println("\nTotal Frames sent across system: {}", NUsers * NFrames);
  std::println("Total Frames verified delivered: {}", recv);
  std::println("Total failed send attempts across all users: {}", fail);

  pthread_mutex_destroy(&io_mutex);

  return 0;
}
