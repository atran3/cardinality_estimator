#include "LogLogEstimator.h"
#include <math.h>
#include <strings.h>
#include <iostream>

LogLogEstimator::LogLogEstimator(size_t numBuckets) {
  this->numBuckets = numBuckets;
  // Each bitmap is 5 bits by construction
  // We will simulate using only 5 of 8 bits
  buckets = new char[numBuckets]();
  k = (size_t) log2(numBuckets);
}

LogLogEstimator::~LogLogEstimator() {
  delete[] buckets;
}

void LogLogEstimator::read(size_t elem) {
  // Hard coded 32 bits for size_t
  size_t index = elem & ((1 << k) - 1);
  size_t val = ffs(elem >> k);
  
  if (val == 0)
    return;

  // 5 bit limit
  // Subtract 1 because using the rank starting at 0
  val = (val-1) & 31;

  if (val > buckets[index]) {
    buckets[index] = val;
  }
}

double LogLogEstimator::estimate() {
  double mean = 0.0;
  for (size_t i = 0; i < numBuckets; ++i) {
    mean += buckets[i];
  }

  mean /= numBuckets;

  double temp = tgamma(-1.0/numBuckets) * (pow(2, -1.0/numBuckets) -1.0) / (log(2));
  double constant = pow(temp, -1 * (int)numBuckets);

  return constant * numBuckets * pow(2.0, mean);
}
