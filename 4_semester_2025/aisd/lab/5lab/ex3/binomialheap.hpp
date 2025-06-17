#ifndef BINOMIAL_HEAP_HPP
#define BINOMIAL_HEAP_HPP

#include <cstddef>
#include <cstdlib>
#include <limits>

typedef struct BHNode {
    int key;
    BHNode* p;
    BHNode* child;
    int degree;
    BHNode* sibling;

    BHNode() : key(0), p(nullptr), child(nullptr), degree(0), sibling(nullptr) {}
    BHNode(int k) : key(k), p(nullptr), child(nullptr), degree(0), sibling(nullptr) {}
} BHNode;

struct BinomialHeap {
    BHNode* head;
    BinomialHeap() : head(nullptr) {}
};

inline BinomialHeap* make_binomial_heap() {
    return new BinomialHeap();
}

inline BHNode* binomial_heap_minimum(BinomialHeap* H, size_t &comparions) {
    BHNode* y = nullptr;
    BHNode* x = H->head;
    int min = std::numeric_limits<int>::max();
    while (x != nullptr) {
        comparions++;
        if (x->key < min) {
            min = x->key;
            y = x;
        }
        x = x->sibling;
    }
    return y;
}

inline void binomail_heap_link(BHNode* y, BHNode* z) {
    y->p = z;
    y->sibling = z->child;
    z->child = y;
    z->degree = z->degree + 1;
}

inline BHNode* binomial_heap_merge(BinomialHeap* H1, BinomialHeap* H2) {
    if (!H1->head) return H2->head;
    if (!H2->head) return H1->head;

    BHNode* head = nullptr;
    BHNode* tail = nullptr;
    BHNode* h1 = H1->head;
    BHNode* h2 = H2->head;

    if (h1->degree <= h2->degree) {
        head = h1;
        h1 = h1->sibling;
    } else {
        head = h2;
        h2 = h2->sibling;
    }
    tail = head;

    while (h1 && h2) {
        if (h1->degree <= h2->degree) {
            tail->sibling = h1;
            h1 = h1->sibling;
        } else {
            tail->sibling = h2;
            h2 = h2->sibling;
        }
        tail = tail->sibling;
    }
    tail->sibling = h1 ? h1 : h2;
    return head;
}

inline BinomialHeap* binomial_heap_union(BinomialHeap* H1, BinomialHeap* H2, size_t &comparisons) {
    BinomialHeap* H = make_binomial_heap();
    H->head = binomial_heap_merge(H1, H2);

    delete H1;
    delete H2;

    if (!H->head)
        return H;

    BHNode* prev_x = nullptr;
    BHNode* x = H->head;
    BHNode* next_x = x->sibling;

    while (next_x != nullptr) {
        if ((x->degree != next_x->degree) ||
            (next_x->sibling != nullptr && next_x->sibling->degree == x->degree)) {
            prev_x = x;
            x = next_x;
        } else if (x->key <= next_x->key) {
            ++comparisons;
            x->sibling = next_x->sibling;
            binomail_heap_link(next_x, x);
        } else {
            ++comparisons;
            if (prev_x == nullptr) {
                H->head = next_x;
            } else {
                prev_x->sibling = next_x;
            }
            binomail_heap_link(x, next_x);
            x = next_x;
        }
        next_x = x->sibling;
    }
    return H;
}

inline void binomial_heap_insert(BinomialHeap*& H, BHNode* x, size_t &comparisons) {
    BinomialHeap* H_prime = make_binomial_heap();
    x->p = nullptr;
    x->child = nullptr;
    x->sibling = nullptr;
    x->degree = 0;
    H_prime->head = x;
    H = binomial_heap_union(H, H_prime, comparisons);
}

inline BHNode* binomial_heap_extract_min(BinomialHeap*& H, size_t &comparisons) {
    if (!H || !H->head) return nullptr;

    BHNode* prev_min = nullptr;
    BHNode* min_node = H->head;
    BHNode* prev = nullptr;
    BHNode* curr = H->head;
    int min_key = curr->key;

    while (curr != nullptr) {
        comparisons++;
        if (curr->key < min_key) {
            min_key = curr->key;
            prev_min = prev;
            min_node = curr;
        }
        prev = curr;
        curr = curr->sibling;
    }

    if (prev_min != nullptr) {
        prev_min->sibling = min_node->sibling;
    } else {
        H->head = min_node->sibling;
    }

    BinomialHeap* H_prime = make_binomial_heap();
    BHNode* child = min_node->child;
    BHNode* prev_child = nullptr;
    while (child != nullptr) {
        BHNode* next = child->sibling;
        child->sibling = prev_child;
        child->p = nullptr;
        prev_child = child;
        child = next;
    }
    H_prime->head = prev_child;

    H = binomial_heap_union(H, H_prime, comparisons);

    return min_node;
}

inline size_t binomial_heap_size(BinomialHeap* H) {
    if (!H || !H->head) return 0;

    size_t size = 0;
    BHNode* curr = H->head;
    while (curr != nullptr) {
        size += (1 << curr->degree);
        curr = curr->sibling;
    }
    return size;
}

#endif