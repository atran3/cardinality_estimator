#ifndef PCSA_Included
#define PCSA_Included

#include "stdlib.h"
#include <functional>
#include "Hashes.h"

class PCSAEstimator {
public:
  PCSAEstimator(size_t numBuckets);
  ~PCSAEstimator();

  void read(size_t elem);
  double estimate();

private:
	unsigned int* buckets;
	size_t numBuckets;
	HashFunction h;

	unsigned int rho(unsigned int y);
};

#endif
