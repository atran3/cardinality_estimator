#include "RoughEstimator.h"
#include "OptimalEstimator.h"
#include <math.h>
#include <strings.h>
#include <iostream>

OptimalEstimator::OptimalEstimator(size_t numBuckets) {
	this->numBuckets = numBuckets;
	// Each bitmap is 5 bits by construction
	// We will simulate using only 5 of 8 bits
	buckets = new char[numBuckets]();
	rough = new RoughEstimator();
	b = 0;
	est = 0;
	h0 = threeIndependentHashFamily()->get();
	h1 = threeIndependentHashFamily()->get();
}

OptimalEstimator::~OptimalEstimator() {
	delete[] buckets;
	delete rough;
}

void OptimalEstimator::read(size_t elem) {
		size_t index = h0(elem) % numBuckets;
		size_t val = ffs(h1(elem));
		// 5 bit limit
		val = (val-1) & 31;

		if ((val - b) > buckets[index]) {
			buckets[index] = val - b;
		}
		rough->read(elem);
		double R = rough->estimate();
		if(R > pow(2, est)) {
			est = log2(R);
			int candidate = est - log2(numBuckets / 32);
			int b_new = candidate > 0 ? candidate : 0;
			for(int i = 0; i < numBuckets; i++) {
				candidate = buckets[i] + b - b_new;
				buckets[i] = candidate > -1 ? candidate : -1;
			}
			b = b_new;
		}
}

double OptimalEstimator::estimate() {
	int T = 0;
	for(int i = 0; i < numBuckets; i++) {
		if(buckets[i] >= 0) T++;
	}
	double numerator = log(1 - T/(double)numBuckets);
	double denominator = log(1 - 1.0/numBuckets);
	return pow(2, b) * numerator / denominator;
}
