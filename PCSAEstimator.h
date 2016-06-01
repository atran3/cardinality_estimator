#ifndef PCSA_Included
#define PCSA_Included

#include "stdlib.h"
#include <functional>

class PCSAEstimator {
public:
  PCSAEstimator(size_t numBuckets);
  ~PCSAEstimator();

  void read(double elem);
  double estimate();

private:
	unsigned int* buckets;
	size_t numBuckets;
	std::hash<double> h;

	unsigned int rho(unsigned int y);
};

#endif
