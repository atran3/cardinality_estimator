#include "PCSAEstimator.h"
#include <strings.h>
#include <math.h>

static const double phi = 0.77351;
static const unsigned int L = 32;

PCSAEstimator::PCSAEstimator(size_t numBuckets) {
	this->numBuckets = numBuckets;
	//assumes each bitmap is sizeof(int) * 8
	buckets = new unsigned int[numBuckets](); 
}

PCSAEstimator::~PCSAEstimator() {
	delete[] buckets;
}

void PCSAEstimator::read(double elem) {
	unsigned int hash = h(elem);
	unsigned int alpha = hash % numBuckets;
	unsigned int index = rho(hash / numBuckets);
	buckets[alpha] |= 1 << index;
}

unsigned int PCSAEstimator::rho(unsigned int y) {
	if(y == 0) return L;
	return ffs(y) - 1;
}

double PCSAEstimator::estimate() {
	unsigned int S = 0;
	for(unsigned int i = 0; i < numBuckets; i++) {
		S += rho(~buckets[i]);
	}
	return (numBuckets / phi) * pow(2, (double)S / numBuckets);
}
