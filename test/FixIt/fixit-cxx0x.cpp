// RUN: %clang_cc1 -verify -std=c++11 %s
// RUN: cp %s %t
// RUN: not %clang_cc1 -x c++ -std=c++11 -fixit %t
// RUN: %clang_cc1 -Wall -pedantic -x c++ -std=c++11 %t

/* This is a test of the various code modification hints that only
   apply in C++0x. */
struct A {
  explicit operator int(); // expected-note{{conversion to integral type}}
};

void x() {
  switch(A()) { // expected-error{{explicit conversion to}}
  }
}

using ::T = void; // expected-error {{name defined in alias declaration must be an identifier}}
using typename U = void; // expected-error {{name defined in alias declaration must be an identifier}}
using typename ::V = void; // expected-error {{name defined in alias declaration must be an identifier}}

namespace SemiCommaTypo {
  int m {},
  n [[]], // expected-error {{expected ';' at end of declaration}}
  int o;

  struct Base {
    virtual void f2(), f3();
  };
  struct MemberDeclarator : Base {
    int k : 4,
        //[[]] : 1, FIXME: test this once we support attributes here
        : 9, // expected-error {{expected ';' at end of declaration}}
    char c, // expected-error {{expected ';' at end of declaration}}
    typedef void F(), // expected-error {{expected ';' at end of declaration}}
    F f1,
      f2 final,
      f3 override, // expected-error {{expected ';' at end of declaration}}
  };
}

namespace ScopedEnum {
  enum class E { a };

  enum class E b = E::a; // expected-error {{must use 'enum' not 'enum class'}}
  struct S {
    friend enum class E; // expected-error {{must use 'enum' not 'enum class'}}
  };
}

struct S2 { 
  void f(int i); 
  void g(int i);
};

void S2::f(int i) {
  (void)[&, &i, &i]{}; // expected-error 2{{'&' cannot precede a capture when the capture default is '&'}}
  (void)[=, this]{ this->g(5); }; // expected-error{{'this' cannot be explicitly captured}}
  (void)[i, i]{ }; // expected-error{{'i' can appear only once in a capture list}}
  (void)[&, i, i]{ }; // expected-error{{'i' can appear only once in a capture list}}
  (void)[] mutable { }; // expected-error{{lambda requires '()' before 'mutable'}}
  (void)[] -> int { }; // expected-error{{lambda requires '()' before return type}}
}

#define bar "bar"
const char *p = "foo"bar; // expected-error {{requires a space between}}
#define ord - '0'
int k = '4'ord; // expected-error {{requires a space between}}

void operator""_x(char); // expected-error {{requires a space}}
void operator"x" _y(char); // expected-error {{must be '""'}}
void operator L"" _z(char); // expected-error {{encoding prefix}}
void operator "x" "y" U"z" ""_whoops "z" "y"(char); // expected-error {{must be '""'}}

void f() {
  'a'_x;
  'b'_y;
  'c'_z;
  'd'_whoops;
}

template<typename ...Ts> struct MisplacedEllipsis {
  int a(Ts ...(x)); // expected-error {{'...' must immediately precede declared identifier}}
  int b(Ts ...&x); // expected-error {{'...' must immediately precede declared identifier}}
  int c(Ts ...&); // expected-error {{'...' must be innermost component of anonymous pack declaration}}
  int d(Ts ...(...&...)); // expected-error 2{{'...' must be innermost component of anonymous pack declaration}}
  int e(Ts ...*[]); // expected-error {{'...' must be innermost component of anonymous pack declaration}}
  int f(Ts ...(...*)()); // expected-error 2{{'...' must be innermost component of anonymous pack declaration}}
  int g(Ts ...()); // ok
};
namespace TestMisplacedEllipsisRecovery {
  MisplacedEllipsis<int, char> me;
  int i; char k;
  int *ip; char *kp;
  int ifn(); char kfn();
  int a = me.a(i, k);
  int b = me.b(i, k);
  int c = me.c(i, k);
  int d = me.d(i, k);
  int e = me.e(&ip, &kp);
  int f = me.f(ifn, kfn);
  int g = me.g(ifn, kfn);
}
