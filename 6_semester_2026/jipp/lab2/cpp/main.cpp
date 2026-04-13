#include <cassert>
#include <exception>
#include <iostream>
#include <optional>
#include <print>
#include <stdexcept>

#include "ring.hpp"

void test_op_add();
void test_op_sub();
void test_op_mul();
void test_op_div_prime();
void test_op_div_composite();
void test_comparisons();
void test_subst_eq();
void test_subst_add();
void test_subst_sub();
void test_subst_mul();
void test_subst_div();
void test_streams();

// template <uint64_t N>
// std::optional<Ring<N>> ring_initializer(uint64_t value) { 
//   if (value == 7) { return std::nullopt; };
//   return Ring<N>(7);
// }

int main(void) {
  // auto x = ring_initializer<5>(7);
  // if (not x.has_value()) {
  //   std::println("Cannot instantiate std::optional");
  // }

  // (+) operator
  test_op_add();

  // (-) operator
  test_op_sub();

  // (*) operator
  test_op_mul();

  // (/) operator
  test_op_div_prime();
  test_op_div_composite();

  // (==,!=,<=,>=,<,>)
  test_comparisons();

  // (=,+=,-=,*=,/=)
  test_subst_eq();
  test_subst_add();
  test_subst_sub();
  test_subst_mul();
  test_subst_div();

  // repr/streams
  test_streams();
}

void test_op_add() {
  Ring<17> op1{8};
  Ring<17> op2{10};

  assert((op1 + op2) == 1);

  Ring<15> oq1{4};
  Ring<15> oq2{9};

  // 4 + 9 = 13 (mod 15)
  assert((oq1 + oq2) == 13);

  // 4 + 4 + 9 = 17 = 2 (mod 15)
  assert((oq1 + oq1 + oq2) == 2);
  std::println("{} passed", __FUNCTION__);
}

void test_op_sub() {
  Ring<17> op1{9};
  Ring<17> op2{13};

  // 13 - 9 = 4 (mod 17)
  assert((op2 - op1) == 4);

  // 9 - 13 = -4 -> 17 - 4 = 13 (mod 17)
  assert((op1 - op2) == 13);

  Ring<15> oq1{9};
  Ring<15> oq2{13};

  // 13 - 9 = 4 (mod 15)
  assert((oq2 - oq1) == 4);

  // 9 - 13 = -4 -> 15-4 = 11 (mod 15)
  assert((oq1 - oq2) == 11);

  std::println("{} passed", __FUNCTION__);
}

void test_op_mul() {
  Ring<17> op1{9};
  Ring<17> op2{13};

  // 9 * 13 = 117 = 15 (mod 17)
  assert((op1 * op2) == 15);

  Ring<15> oq1{9};
  Ring<15> oq2{13};

  assert((oq1 * oq2) == 12);

  std::println("{} passed", __FUNCTION__);
}

void test_op_div_prime() {
  Ring<17> op1{9};
  Ring<17> op2{13};

  // op1 / op2 = op1 * inv(op2) = 9 * 4 = 36 mod 17 = 2

  assert((op1 / op2) == 2);
}

void test_op_div_composite() {
  Ring<15> oq1{9};
  Ring<15> oq2{13};

  // oq1 / oq2 = oq1 * inv(oq2) = 9 * 7 = 3
  assert((oq1 / oq2) == 3);

  Ring<15> thr(12);
  try {
    [[maybe_unused]]
    volatile Ring<15> res = oq1 / thr;
    throw std::invalid_argument("Should've thrown no invertible element error");
  } catch (std::exception e) {
    // good
  }

  std::println("{} passed", __FUNCTION__);
}

void test_comparisons() {
  Ring<15> a{9};
  Ring<15> b{13};
  Ring<15> c{14};
  Ring<15> d{9};

  assert((a == b) == false);
  assert((a == c) == false);
  assert((a == d) == true);

  assert((a != b) == true);
  assert((a != c) == true);
  assert((a != d) == false);

  assert((a <= b) == true);
  assert((a <= c) == true);
  assert((a <= d) == true);

  assert((a >= b) == false);
  assert((a >= c) == false);
  assert((a >= d) == true);

  assert((a > b) == false);
  assert((a > c) == false);
  assert((a > d) == false);

  assert((a < b) == true);
  assert((a < c) == true);
  assert((a < d) == false);

  std::println("{} passed", __FUNCTION__);
}

void test_subst_eq() {
  Ring<15> a{5};
  Ring<15> b = a;

  assert(b == 5);

  std::println("{} passed", __FUNCTION__);
}

void test_subst_add() {
  Ring<15> a{5};
  Ring<15> b{10};

  a += b;
  assert(a == 0);

  std::println("{} passed", __FUNCTION__);
}

void test_subst_sub() {
  Ring<15> a{6};
  Ring<15> b{8};

  a -= b;
  assert(a == 13);

  std::println("{} passed", __FUNCTION__);
}

void test_subst_mul() {
  Ring<15> a{6};
  Ring<15> b{8};

  a *= b;
  assert(a == 3);

  std::println("{} passed", __FUNCTION__);
}

void test_subst_div() {
  Ring<17> a{9};
  Ring<17> b{13};

  a /= b;
  // op1 / op2 = op1 * inv(op2) = 9 * 4 = 36 mod 17 = 2
  assert(a == 2);

  std::println("{} passed", __FUNCTION__);
}

void test_streams() {
  Ring<17> a{10};
  a.operator<<(std::cout) << std::endl;
}
