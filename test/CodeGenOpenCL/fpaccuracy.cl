// RUN: %clang_cc1 %s -emit-llvm -o - | FileCheck %s

typedef __attribute__(( ext_vector_type(4) )) float float4;

float spscalardiv(float a, float b) {
  // CHECK: @spscalardiv
  // CHECK: fdiv{{.*}}, !fpaccuracy ![[MD:[0-9]+]]
  return a / b;
}

float4 spvectordiv(float4 a, float4 b) {
  // CHECK: @spvectordiv
  // CHECK: fdiv{{.*}}, !fpaccuracy ![[MD]]
  return a / b;
}

#pragma OPENCL EXTENSION cl_khr_fp64 : enable

double dpscalardiv(double a, double b) {
  // CHECK: @dpscalardiv
  // CHECK-NOT: !fpaccuracy
  return a / b;
}

// CHECK: ![[MD]] = metadata !{i{{[0-9]+}} 5, i{{[0-9]+}} 2}
