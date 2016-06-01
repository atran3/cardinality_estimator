#ifndef Rough_Included
#define Rough_Included

#include "stdlib.h"

class RoughEstimator {
public:
  RoughEstimator(size_t numBuckets);
  ~RoughEstimator();

  void read(double elem);
  double estimate();

private:
};

#endif
