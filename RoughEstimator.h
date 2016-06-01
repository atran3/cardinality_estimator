#ifndef Rough_Included
#define Rough_Included

#include "stdlib.h"
#include "Hashes.h"
#include <functional>

class RoughEstimator {
public:
  RoughEstimator();
  ~RoughEstimator();

  void read(size_t elem);
  double estimate();

private:
  char* buckets;
  HashFunction h0;
  HashFunction h1;
  HashFunction h2;
  HashFunction h3;
  HashFunction h4;
  HashFunction h5;
};

#endif
