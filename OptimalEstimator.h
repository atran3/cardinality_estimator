#ifndef Optimal_Included
#define Optimal_Included

#include "stdlib.h"
#include "RoughEstimator.h"
#include "Hashes.h"
#include <functional>

class OptimalEstimator {
public:
  OptimalEstimator(size_t numBuckets);
  ~OptimalEstimator();

  void read(size_t elem);
  double estimate();

private:
  char *buckets;
  size_t numBuckets;
  RoughEstimator* rough;
  HashFunction h0;
  HashFunction h1;
  int b;
  int est;

};

#endif
