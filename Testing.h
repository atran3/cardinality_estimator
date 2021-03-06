#ifndef Testing_Included
#define Testing_Included

#include <random>
#include <functional>
#include <chrono>
#include <set>

static const size_t kRandomSeed = 1337;
static size_t kUniverseSize = UINT_MAX;
static bool kAllUnique = false;
static bool kUniformDist = true;
static bool kTrackGold = false;
typedef std::chrono::high_resolution_clock myclock;
static myclock::time_point beginning = myclock::now();

double get_p(size_t n, size_t stddev) {
  double variance = pow(stddev, 2);
  double temp = sqrt(1 - 4.0*variance/n);
  return 0.5 * (1 - temp);
}

template <typename E>
double runTest(size_t buckets, size_t numElements, size_t seed, size_t stddev, size_t* gold) {
  E estimator(buckets);
  std::default_random_engine engine;
  engine.seed(seed);
  auto u_gen = std::uniform_int_distribution<size_t>(0, kUniverseSize);
  // Simulate normal distribution for integers using binomial
  auto n_gen = std::binomial_distribution<size_t>(kUniverseSize,
						  get_p(kUniverseSize, stddev));

  std::set<size_t> s;
  for (size_t i = 0; i < numElements; ++i) {
    size_t val = kAllUnique ? i :
      (kUniformDist ? u_gen(engine) : n_gen(engine));
    estimator.read(val);
    
    if (kTrackGold && gold)
      s.insert(val);
  }
  
  if (kTrackGold && gold) {
    *gold = s.size();
  }

  return estimator.estimate();
}

template <typename E>
double runFixedTest(size_t buckets, size_t numElements, size_t stddev, size_t* gold) {
  return runTest<E>(buckets, numElements, kRandomSeed, stddev, gold);
}

template <typename E>
double runRandomTest(size_t buckets, size_t numElements, size_t stddev, size_t* gold) {
  myclock::duration d = myclock::now() - beginning;
  return runTest<E>(buckets, numElements, d.count(), stddev, gold);
}

template <typename E>
double runAggregatedTest(size_t buckets, size_t numElements,
			 size_t numEstimators, size_t stddev, size_t* gold,
			 std::function<double (double *, int)> combiner) {
  double* estimates = (double *) malloc(numEstimators * sizeof(double));
  for (size_t i = 0; i < numEstimators; ++i) {
    estimates[i] = runFixedTest<E>(buckets, numElements, stddev, gold);    
  }

  double result = combiner(estimates, numEstimators);
  free (estimates);
  return result;
}

#endif

