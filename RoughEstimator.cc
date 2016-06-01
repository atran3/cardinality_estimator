#include "RoughEstimator.h"
#include <math.h>
#include <strings.h>
#include "Hashes.h"
#include <algorithm>
#include <iostream>

static const int K = 3;
static const int M = 8;
static const int L = 32;
static const double rho = 0.280634;

RoughEstimator::RoughEstimator() {
	buckets = new char[M * K]();
	h0 = threeIndependentHashFamily()->get();
	h1 = threeIndependentHashFamily()->get();
	h2 = threeIndependentHashFamily()->get();
	h3 = threeIndependentHashFamily()->get();
	h4 = threeIndependentHashFamily()->get();
	h5 = threeIndependentHashFamily()->get();
}

RoughEstimator::~RoughEstimator() {
	delete[] buckets;
}

void RoughEstimator::read(size_t elem) {
	for(int i = 0; i < K; i++) {
		size_t index;
		size_t val;
		size_t hash;
		if(i == 0) {
			hash = h0(elem);
			index = h1(hash % (K * M)) % M;
			val = ffs(hash);
		} else if (i == 1) {
			hash = h2(elem);
			index = h3(hash % (K * M)) % M;
			val = ffs(hash);
		} else {
			hash = h4(elem);
			index = h5(hash % (K * M)) % M;
			val = ffs(hash);
		}
		if (val == 0)
			return;
		// 5 bit limit
		val = (val-1) & 31;
		if (val > buckets[index + i * M]) {
			buckets[index + i * M] = val;
		}
	}
}

double RoughEstimator::estimate() {
	double min_r = rho * M;
	int F[K];
	for(int i = 0; i < K; i++) {
		int T[L] = {0};
		for(int r = 0; r < L; r++) {
			for(int k = 0; k < M; k++) {
				if(buckets[k + i * M] >= r) T[r]++;
			}
		}
		int best_r = 0;
		int best_T = T[0];
		for(int r = 0; r < L; r++){
			if(T[r] >= min_r) {
				best_T = T[r];
				best_r = r;
			}
		}
		if(best_T >= min_r) {
			F[i] = pow(2, best_r) * M;
		} else {
			F[i] = -1;
		}
	}
	std::sort(std::begin(F), std::end(F));
	return F[1];
}
