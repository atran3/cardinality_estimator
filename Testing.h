#ifndef Testing_Included
#define Testing_Included

#include <random>
#include <functional>

static const size_t kRandomSeed = 1337;

template <typename E>
double runTest(size_t buckets, size_t numElements, size_t universeSize) {
  E estimator(buckets);
  std::default_random_engine engine;
  engine.seed(kRandomSeed);
  auto gen = std::uniform_int_distribution<int>(0, universeSize);

  for (size_t i = 0; i < numElements; ++i) {
    int val = gen(engine);
    estimator.read(val);
  }

  return estimator.estimate();
}

template <typename E>
double runAggregatedTest(size_t buckets, size_t numElements,
			 size_t universeSize, size_t numEstimators,
			 std::function<double (double *, int)> combiner) {
  double* estimates = (double *) malloc(numEstimators * sizeof(double));
  for (size_t i = 0; i < numEstimators; ++i) {
    estimates[i] = runTest<E>(buckets, numElements, universeSize);    
  }

  double result = combiner(estimates, numEstimators);
  free (estimates);
  return result;
}

#endif

