#ifndef RADIX_HEAP_HPP
#define RADIX_HEAP_HPP

#include <vector>
#include <limits>
#include <utility>

class RadixHeap {
private:
    using Key = long long;
    using Value = long long;

    std::vector<std::pair<Key, Value>> buckets[33];
    Key last_deleted = 0;
    size_t sz = 0;

    static long long bucket_index(Key last, Key key) {
        if (key == last) return 0;
        return 32 - __builtin_clz(key ^ last);
    }

public:
    RadixHeap() = default;

    bool empty() const { return sz == 0; }

    void push(Key key, Value value) {
        long long idx = bucket_index(last_deleted, key);
        buckets[idx].push_back({key, value});
        sz++;
    }

    std::pair<Key, Value> top() {
        if (buckets[0].empty()) {
            long long i = 1;
            while (i < 33 && buckets[i].empty())
                i++;

            Key new_last = std::numeric_limits<Key>::max();
            for (auto& p : buckets[i])
                if (p.first < new_last)
                    new_last = p.first;

            last_deleted = new_last;

            for (auto& p : buckets[i]) {
                long long idx = bucket_index(last_deleted, p.first);
                buckets[idx].push_back(p);
            }
            buckets[i].clear();
        }

        return buckets[0].back();
    }

    void pop() {
        if (buckets[0].empty()) top();
        buckets[0].pop_back();
        sz--;
    }
};

#endif // RADIX_HEAP_HPP
