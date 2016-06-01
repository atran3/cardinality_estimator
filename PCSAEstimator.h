#ifndef PCSA_Included
#define PCSA_Included

#include "stdlib.h"

class PCSAEstimator {
public:
  PCSAEstimator(size_t numBuckets);
  ~PCSAEstimator();

  void read(double elem);
  double estimate();

private:
};

#endif
