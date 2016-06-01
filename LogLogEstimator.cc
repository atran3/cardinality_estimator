#include "LogLogEstimator.h"
#include <math.h>
#include <strings.h>

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
  size_t hash = elem & 0x7;
  size_t index = ffs(elem >> 7);
  
  if (index > 0 && index < 6)
    buckets[hash] |= 1 << (index-1);
}

double LogLogEstimator::estimate() {
  double mean = 0.0;
  for (size_t i = 0; i < numBuckets; ++i) {
    size_t r = 0;
    while (buckets[i] >>= 1) {
      r++;
    }

    mean += r;
  }
  mean /= numBuckets;

  return numBuckets * pow(2.0, mean);
}
