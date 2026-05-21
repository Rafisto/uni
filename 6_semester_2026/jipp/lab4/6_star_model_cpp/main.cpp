#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <random>
#include <vector>
#include <string>
#include <iomanip>

const int NUsers = 5;
const int NMessages = 20;
const useconds_t BaseBackoff = 2000;       
const useconds_t MaxBackoff = 2000000;     
const useconds_t ProcessingTime = 1000;    

struct Message {
    int From;
    int To;
    std::string Body;
};

struct Server {
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond_msg_ready = PTHREAD_COND_INITIALIZER;    
    pthread_cond_t cond_forward_done = PTHREAD_COND_INITIALIZER; 
    
    Message* ActiveMessage = nullptr;
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
    std::uniform_int_distribution<useconds_t> dist(0, static_cast<useconds_t>(max_val));
    return dist(gen);
}

void* userWorker(void* arg) {
    int id = *static_cast<int*>(arg);
    delete static_cast<int*>(arg);

    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<double> think_dist(0.0, static_cast<double>(BaseBackoff));

    for (int i = 1; i <= NMessages; ++i) {
        useconds_t thinkTime = static_cast<useconds_t>(think_dist(gen));
        usleep(thinkTime);

        std::uniform_int_distribution<int> user_dist(1, NUsers);
        int targetID = user_dist(gen);

        Message* msg = new Message{
            id, 
            targetID, 
            "Msg " + std::to_string(i) + " from User " + std::to_string(id)
        };

        int attempt = 1;

        while (true) {
            pthread_mutex_lock(&server.mutex);
            if (server.ActiveMessage == nullptr) {
                pthread_mutex_lock(&io_mutex);
                std::cout << "User(id " << id << ") successfully acquired Server Inbox for transfer " << i << ".\n";
                pthread_mutex_unlock(&io_mutex);
                break;
            }
            pthread_mutex_unlock(&server.mutex);

            pthread_mutex_lock(&users[id - 1].mutex);
            users[id - 1].FailCount++;
            pthread_mutex_unlock(&users[id - 1].mutex);

            useconds_t backoff = exponentialBackoff(attempt);
            
            pthread_mutex_lock(&io_mutex);
            std::cout << "User(id " << id << ", transfer " << i << ") found Server busy. Backing off for ";
            if (backoff < 1000) {
                std::cout << backoff << "µs";
            } else {
                std::cout << std::fixed << std::setprecision(3) << (backoff / 1000.0) << "ms";
            }
            std::cout << " (attempt " << attempt << ").\n";
            pthread_mutex_unlock(&io_mutex);

            usleep(backoff);
            attempt++;
        }

        server.ActiveMessage = msg;
        server.ForwardDone = false;
        
        pthread_cond_signal(&server.cond_msg_ready);

        while (!server.ForwardDone) {
            pthread_cond_wait(&server.cond_forward_done, &server.mutex);
        }

        pthread_mutex_unlock(&server.mutex); 
    } 

    pthread_mutex_lock(&io_mutex);
    std::cout << "User(id " << id << ") finished sending all " << NMessages << " messages.\n";
    pthread_mutex_unlock(&io_mutex);

    return nullptr;
}

void* serverDispatcher(void* arg) {
    while (true) {
        pthread_mutex_lock(&server.mutex);
        
        while (server.ActiveMessage == nullptr && !server.Quit) {
            pthread_cond_wait(&server.cond_msg_ready, &server.mutex);
        }

        if (server.Quit && server.ActiveMessage == nullptr) {
            pthread_mutex_unlock(&server.mutex);
            break;
        }

        if (server.ActiveMessage != nullptr) {
            Message* msg = server.ActiveMessage;
            User& recipient = users[msg->To - 1];

            pthread_mutex_lock(&io_mutex);
            std::cout << "Server: Received message from User " << msg->From 
                      << " destined for User " << msg->To << ". Forwarding...\n";
            pthread_mutex_unlock(&io_mutex);

            pthread_mutex_lock(&recipient.mutex);
            usleep(ProcessingTime);
            recipient.InboxCount++;
            pthread_mutex_unlock(&recipient.mutex);

            pthread_mutex_lock(&io_mutex);
            std::cout << "Server: Successfully delivered message from User " << msg->From 
                      << " to User " << msg->To << ".\n";
            pthread_mutex_unlock(&io_mutex);

            delete msg;
            server.ActiveMessage = nullptr;
            server.ForwardDone = true;
            
            pthread_cond_broadcast(&server.cond_forward_done);
        }

        pthread_mutex_unlock(&server.mutex);
    }
    return nullptr;
}

int main() {
    std::cout << "Star Topology Communication System (No Buffer Server)\n";

    pthread_t dispatcher_thread;
    pthread_create(&dispatcher_thread, nullptr, serverDispatcher, nullptr);

    pthread_t worker_threads[NUsers];
    for (int i = 0; i < NUsers; ++i) {
        int* id_arg = new int(i + 1);
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

    std::cout << "\n--- Final System Statistics ---\n";
    int totalReceived = 0;
    int totalFailed = 0;

    for (int i = 1; i <= NUsers; ++i) {
        pthread_mutex_lock(&users[i - 1].mutex);
        int received = users[i - 1].InboxCount;
        int failCount = users[i - 1].FailCount;
        pthread_mutex_unlock(&users[i - 1].mutex);

        totalFailed += failCount;
        totalReceived += received;
        std::cout << "User(id " << i << ") received " << received 
                  << " messages (" << failCount << " failed attempts).\n";
    }

    std::cout << "\nTotal messages sent across system: " << (NUsers * NMessages) << "\n";
    std::cout << "Total messages verified delivered: " << totalReceived << "\n";
    std::cout << "Total failed send attempts across all users: " << totalFailed << "\n";

    return 0;
}