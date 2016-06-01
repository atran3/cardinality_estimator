#ifndef HyperLogLog_Included
#define HyperLogLog_Included

#include "stdlib.h"
#include <functional>

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
  std::hash<size_t> h;
};

#endif
