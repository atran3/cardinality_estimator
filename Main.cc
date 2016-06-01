#include <iostream>
#include <algorithm>
#include "Testing.h"
#include "PCSAEstimator.h"
#include "LogLogEstimator.h"
#include "HyperLogLogEstimator.h"
#include "RoughEstimator.h"

int main() {
  std::cout << "Practice Test with PCSA Estimator..." << std::endl;
  double estimate = runTest<PCSAEstimator>(1, 1, 1);
  std::cout << "  Test:    " << ((estimate == 1.0) ? "passed" : "failed") << std::endl;
}

double mean(double* estimates, int numEstimators) {
  double total = 0;
  for (size_t i = 0; i < numEstimators; ++i) {
    total += estimates[i];
  }
  return total/numEstimators;
}

double median(double* estimates, int numEstimators) {
  std::sort(estimates, estimates + numEstimators);
  if (numEstimators % 2) {
    return estimates[numEstimators/2];
  } else {
    return (estimates[numEstimators/2] + estimates[(numEstimators/2)-1])/2;
  }
}
