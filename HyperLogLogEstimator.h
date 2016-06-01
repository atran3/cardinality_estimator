#ifndef HyperLogLog_Included
#define HyperLogLog_Included

#include "stdlib.h"

class HyperLogLogEstimator {
public:
  HyperLogLogEstimator(size_t numBuckets);
  ~HyperLogLogEstimator();

  void read(double elem);
  double estimate();

private:
};

#endif
