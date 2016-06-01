#ifndef HyperLogLog_Included
#define HyperLogLog_Included

#include "stdlib.h"
#include <functional>
#include "Hashes.h"

class HyperLogLogEstimator {
public:
  HyperLogLogEstimator(size_t numBuckets);
  ~HyperLogLogEstimator();

  void read(size_t elem);
  double estimate();

private:
  char *buckets;
  size_t numBuckets;
  size_t k;
  HashFunction h;
};

#endif
