#include "HyperLogLogEstimator.h"
#include <math.h>

static const double alpha = 0.72134;

HyperLogLogEstimator::HyperLogLogEstimator(size_t numBuckets) {
  this->numBuckets = numBuckets;
  // Each bitmap is 5 bits by construction
  // We will simulate using only 5 of 8 bits
  buckets = new char[numBuckets]();
  k = (size_t) log2(numBuckets);
}

HyperLogLogEstimator::~HyperLogLogEstimator() {
  delete[] buckets;
}

void HyperLogLogEstimator::read(size_t elem) {
  size_t hash = h(elem);
  size_t index = 1 + hash & ((1 << k) - 1);
  size_t val = ffs(elem >> k);

  if (val == 0)
    return;

  // 5 bit limit
  val = val & 31;

  if (val > buckets[index]) {
    buckets[index] = val;
  }
}

double HyperLogLogEstimator::estimate() {
  double indicator = 0.0;
  for (size_t i = 0; i < numBuckets; ++i) {
    indicator += pow(2, -buckets[i]);
  }
  
  indicator = 1.0/indicator;

  return alpha * indicator * numBuckets * numBuckets;
}
