#include <iostream>
#include <vector>

using namespace std;

class PrimeNumbers {
private:
    vector<int> primes;
public:
    explicit PrimeNumbers(int n) {
        bool prime[n + 1];
        for (int i = 0; i < n; i++) {
            prime[i] = true;
        }

        for (int p = 2; p * p <= n; p++) {
            if (prime[p]) {
                for (int i = p * p; i <= n; i += p) {
                    prime[i] = false;
                }
            }
        }

        for (int p = 2; p <= n; p++) {
            if (prime[p]) {
                this->primes.push_back(p);
            }
        }

    }

    int getPrime(int index) {
        if (0 > index) return -1;
        if (primes.size() - 1 < index) return -1;
        return primes[index];
    }
};

int main(int argc, char *argv[]) {
    PrimeNumbers* p;
    p = new PrimeNumbers(strtol(argv[1], nullptr, 10));
    for (int i = 0; i < argc; i++) {
        int arg = strtol(argv[i], nullptr, 10);
        printf("prime(%d) = %d\n", arg, p->getPrime(arg));
    }
    return 0;
}