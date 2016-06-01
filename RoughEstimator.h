#ifndef Rough_Included
#define Rough_Included

#include "stdlib.h"

class RoughEstimator {
public:
  RoughEstimator(size_t numBuckets);
  ~RoughEstimator();

  void read(size_t elem);
  double estimate();

private:
};

#endif
