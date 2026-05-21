#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <random>

const int N_PHILOSOPHERS = 100;
const int N_ITERATIONS = 100;
const double TIME_CONSTRAINT = 0.01; 

void random_delay() {
    static thread_local std::mt19937 generator(std::random_device{}());
    std::uniform_real_distribution<double> distribution(0.0, TIME_CONSTRAINT);
    
    double sleep_time = distribution(generator);
    usleep(static_cast<useconds_t>(sleep_time * 1000000.0));
}

struct CountFinished {
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
    int count = 0;

    void increment() {
        pthread_mutex_lock(&mutex);
        count++;
        if (count == N_PHILOSOPHERS) {
            pthread_cond_signal(&cond);
        }
        pthread_mutex_unlock(&mutex);
    }

    void wait() {
        pthread_mutex_lock(&mutex);
        while (count < N_PHILOSOPHERS) {
            pthread_cond_wait(&cond, &mutex);
        }
        pthread_mutex_unlock(&mutex);
    }
};

pthread_mutex_t forks[N_PHILOSOPHERS] = {
    PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER
};

CountFinished counter;
pthread_mutex_t io_mutex = PTHREAD_MUTEX_INITIALIZER;

struct PhilosopherData {
    int id;
    int fork_left;
    int fork_right;
};

void* philosopher_worker(void* arg) {
    PhilosopherData* data = static_cast<PhilosopherData*>(arg);
    int failures = 0;

    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<double> dist(0.0, TIME_CONSTRAINT);

    for (int i = 1; i <= N_ITERATIONS; ++i) {
        double think_time = dist(gen);
        
        pthread_mutex_lock(&io_mutex);
        std::cout << "Philosopher(id " << data->id << ", meal " << i 
                  << ") thinks for " << think_time << " sec.\n";
        pthread_mutex_unlock(&io_mutex);

        random_delay();

        while (true) {
            pthread_mutex_lock(&forks[data->fork_left]);

            int right_status = pthread_mutex_trylock(&forks[data->fork_right]);

            if (right_status == 0) {
                break;
            }

            pthread_mutex_unlock(&forks[data->fork_left]);

            pthread_mutex_lock(&io_mutex);
            std::cout << "Philosopher(id " << data->id << ", meal " << i 
                      << ") failed to pick up forks.\n";
            pthread_mutex_unlock(&io_mutex);

            failures++;
            random_delay(); 
        }

        double eat_time = dist(gen);
        pthread_mutex_lock(&io_mutex);
        std::cout << "Philosopher(id " << data->id << ", meal " << i 
                  << ") eats for " << eat_time << " sec.\n";
        pthread_mutex_unlock(&io_mutex);

        random_delay();

        pthread_mutex_unlock(&forks[data->fork_right]);
        pthread_mutex_unlock(&forks[data->fork_left]);
    }

    counter.increment();
    
    pthread_mutex_lock(&io_mutex);
    std::cout << "Philosopher(id " << data->id << ") finished with " << failures << " failures.\n";
    pthread_mutex_unlock(&io_mutex);

    int* total_failures = new int(failures);
    return static_cast<void*>(total_failures);
}

int main() {
    std::cout << "Dining Philosophers Problem\n";

    pthread_t threads[N_PHILOSOPHERS];
    PhilosopherData thread_data[N_PHILOSOPHERS];

    for (int i = 0; i < N_PHILOSOPHERS; ++i) {
        thread_data[i].id = i + 1;
        thread_data[i].fork_left = i;
        thread_data[i].fork_right = (i + 1) % N_PHILOSOPHERS;

        pthread_create(&threads[i], nullptr, philosopher_worker, &thread_data[i]);
    }

    counter.wait();
    std::cout << "Philosophers have concluded the feast.\n";

    int total_failures = 0;

    for (int i = 0; i < N_PHILOSOPHERS; ++i) {
        void* retval;
        pthread_join(threads[i], &retval);
        
        int* failures = static_cast<int*>(retval);
        total_failures += *failures;

        std::cout << "Philosopher(id " << (i + 1) << ") had " << *failures << " failures.\n";
        delete failures; 
    }

    std::cout << "Total failures: " << total_failures << "\n";
    return 0;
}
