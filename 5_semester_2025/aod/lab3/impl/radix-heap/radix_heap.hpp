#ifndef RADIX_HEAP_HPP
#define RADIX_HEAP_HPP

#include <limits>
#include <utility>
#include <vector>

#define INT_MAX std::numeric_limits<long long>::max()
#define SIZE 64+1

class RadixHeap {
  private:
    std::vector<std::pair<long long, long long>> buckets[SIZE];
    // do którego kubełka następny rzut
    long long last_deleted = 0;
    size_t size = 0;

    static long long bucket_index(long long last, long long key) {
        if (key == last)
            return 0;

        // pierwszy różny bit od lewej
        long long mask = 1LL << 63;
        for (int i = 1; i <= 64; i++) {
            if ((key & mask) != (last & mask))
                return i;
            mask >>= 1;
        }

        return 0;
    }

  public:
    RadixHeap() = default;

    bool empty() const { return size == 0; }

    void insert(long long key, long long value) {
        // po prostu dorzucamy do odpowiedniego kubełka
        long long idx = bucket_index(last_deleted, key);
        buckets[idx].push_back({key, value});
        size++;
    }

    std::pair<long long, long long> extract_min() {
        if (buckets[0].empty()) {
            // szukamy niepustego kubełka
            long long i = 1;
            while (i < SIZE && buckets[i].empty())
                i++;

            // wyciągamy element o najmniejszym kluczu z pierwszego niepustego kubełka
            long long new_last = INT_MAX;
            for (auto &p : buckets[i])
                if (p.first < new_last)
                    new_last = p.first;

            last_deleted = new_last;

            // rozdzielamy elementy do odpowiednich kubełków
            for (auto &p : buckets[i]) {
                long long idx = bucket_index(last_deleted, p.first);
                buckets[idx].push_back(p);
            }
            buckets[i].clear();
        }

        return buckets[0].back();
    }

    void pop() {
        // usuwamy element o najmniejszym kluczu
        if (buckets[0].empty())
            extract_min();
        buckets[0].pop_back();
        size--;
    }
};

#endif // RADIX_HEAP_HPP
