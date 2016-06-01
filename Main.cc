#include <iostream>
#include <algorithm>
#include "Testing.h"
#include "PCSAEstimator.h"
#include "LogLogEstimator.h"
#include "HyperLogLogEstimator.h"
#include "RoughEstimator.h"

int main() {
  std::cout << "Practice Test with PCSA Estimator..." << std::endl;
  double estimate = runTest<LogLogEstimator>(1024, 100000);
  std::cout << "  Estimate:    " << estimate << std::endl;
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
