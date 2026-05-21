#include <pthread.h>
#include <random>
#include <unistd.h>
#include <vector>
#include <print>

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

struct Server {
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  pthread_cond_t cond_msg_ready = PTHREAD_COND_INITIALIZER;
  pthread_cond_t cond_forward_done = PTHREAD_COND_INITIALIZER;

  Frame *ActiveFrame = nullptr;
  bool ForwardDone = false;
  bool Quit = false;
};

struct User {
  pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
  int InboxCount = 0;
  int FailCount = 0;
};

Server server;
std::vector<User> users(NUsers);
pthread_mutex_t io_mutex = PTHREAD_MUTEX_INITIALIZER;

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

  for (int i = 1; i <= NFrames; ++i) {
    useconds_t thinkTime = static_cast<useconds_t>(think_dist(gen));
    usleep(thinkTime);

    std::uniform_int_distribution<int> user_dist(1, NUsers);
    int targetID = user_dist(gen);

    Frame *msg = new Frame{id, targetID};
    int attempt = 1;

    while (true) {
      pthread_mutex_lock(&server.mutex);
      if (server.ActiveFrame == nullptr) {
        pthread_mutex_lock(&io_mutex);
        std::println("User(id {}) successfully acquired Server Inbox for transfer {}.",
                id, i);
        pthread_mutex_unlock(&io_mutex);
        break;
      }
      pthread_mutex_unlock(&server.mutex);

      pthread_mutex_lock(&users[id - 1].mutex);
      users[id - 1].FailCount++;
      pthread_mutex_unlock(&users[id - 1].mutex);

      useconds_t backoff = exponentialBackoff(attempt);

      pthread_mutex_lock(&io_mutex);
      std::println("User(id {}, transfer {}) found Server busy. Backing off for {} (attempt {}).",
              id, i, std::to_string(backoff).c_str(), attempt);
      pthread_mutex_unlock(&io_mutex);

      usleep(backoff);
      attempt++;
    }

    server.ActiveFrame = msg;
    server.ForwardDone = false;

    pthread_cond_signal(&server.cond_msg_ready);

    while (!server.ForwardDone) {
      pthread_cond_wait(&server.cond_forward_done, &server.mutex);
    }

    pthread_mutex_unlock(&server.mutex);
  }

  pthread_mutex_lock(&io_mutex);
  std::println("User(id {}) finished sending all {} Frames.", id, NFrames);
  pthread_mutex_unlock(&io_mutex);

  return nullptr;
}

void *serverDispatcher(void *_) {
  while (true) {
    pthread_mutex_lock(&server.mutex);

    while (server.ActiveFrame == nullptr && !server.Quit) {
      pthread_cond_wait(&server.cond_msg_ready, &server.mutex);
    }

    if (server.Quit && server.ActiveFrame == nullptr) {
      pthread_mutex_unlock(&server.mutex);
      break;
    }

    if (server.ActiveFrame != nullptr) {
      Frame *msg = server.ActiveFrame;
      User &recipient = users[msg->To - 1];

      pthread_mutex_lock(&io_mutex);
      std::println("Server: Received Frame from User {} destined for User {}. Forwarding...",
              msg->From, msg->To);
      pthread_mutex_unlock(&io_mutex);

      pthread_mutex_lock(&recipient.mutex);
      usleep(ProcessingTime);
      recipient.InboxCount++;
      pthread_mutex_unlock(&recipient.mutex);

      pthread_mutex_lock(&io_mutex);
      std::println("Server: Successfully delivered Frame from User {} to User {}.",
              msg->From, msg->To);
      pthread_mutex_unlock(&io_mutex);

      delete msg;
      server.ActiveFrame = nullptr;
      server.ForwardDone = true;

      pthread_cond_broadcast(&server.cond_forward_done);
    }

    pthread_mutex_unlock(&server.mutex);
  }
  return nullptr;
}

int main() {
  std::println("Starting star topology communication");

  pthread_t dispatcher_thread;
  pthread_create(&dispatcher_thread, nullptr, serverDispatcher, nullptr);

  pthread_t worker_threads[NUsers];
  for (int i = 0; i < NUsers; ++i) {
    int *id_arg = new int(i + 1);
    pthread_create(&worker_threads[i], nullptr, userWorker, id_arg);
  }

  for (int i = 0; i < NUsers; ++i) {
    pthread_join(worker_threads[i], nullptr);
  }

  pthread_mutex_lock(&server.mutex);
  server.Quit = true;
  pthread_cond_broadcast(&server.cond_msg_ready);
  pthread_mutex_unlock(&server.mutex);

  pthread_join(dispatcher_thread, nullptr);

  std::println("\nStar topology communication complete.");
  int totalReceived = 0;
  int totalFailed = 0;

  for (int i = 1; i <= NUsers; ++i) {
    pthread_mutex_lock(&users[i - 1].mutex);
    int received = users[i - 1].InboxCount;
    int failCount = users[i - 1].FailCount;
    pthread_mutex_unlock(&users[i - 1].mutex);

    totalFailed += failCount;
    totalReceived += received;
    std::println("User(id {}) received {} Frames ({} failed attempts).",
            i, received, failCount);
  }

  std::println("\nTotal Frames sent across system: {}", NUsers * NFrames);
  std::println("Total Frames verified delivered: {}", totalReceived);
  std::println("Total failed send attempts across all users: {}", totalFailed);
  return 0;
}