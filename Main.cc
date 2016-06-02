#include <iostream>
#include <algorithm>
#include "Testing.h"
#include "PCSAEstimator.h"
#include "LogLogEstimator.h"
#include "HyperLogLogEstimator.h"
#include "OptimalEstimator.h"
#include <fstream>
#include <string>
#include <math.h>
#include <functional>

double mean(double* estimates, int numEstimators) {
  double total = 0;
  for (size_t i = 0; i < numEstimators; ++i) {
    total += estimates[i];
  }
  return total/numEstimators;
}

double median(double* estimates, int numEstimators) {
  std::sort(estimates, estimates + numEstimators);
  if (numEstimators % 2) {
    return estimates[numEstimators/2];
  } else {
    return (estimates[numEstimators/2] + estimates[(numEstimators/2)-1])/2;
  }
}

void runBucketCardinalityTest();
void runStreamUniverseTest();
void runMemoryTest(size_t exp);
void runAggregationTests(bool useMean);

int main() {
  size_t numBuckets = 1024;
  size_t numElements = 10000;
  size_t stddev = 100;
  
  kAllUnique = false;
  kUniformDist = true;
  kTrackGold = false;
  size_t gold = 0;
  std::cout << "Practice Tests with " << numBuckets << " buckets and " \
	    << numElements << " elements..." << std::endl;
  std::cout << "  PCSA:    " << runFixedTest<PCSAEstimator>(numBuckets, numElements, stddev, &gold) << std::endl;
  std::cout << "  LgLg:    " << runFixedTest<LogLogEstimator>(numBuckets, numElements, stddev, NULL) << std::endl;
  std::cout << " HLgLg:    " << runFixedTest<HyperLogLogEstimator>(numBuckets, numElements, stddev, NULL) << std::endl;
  std::cout << std::endl << "=======================================" << std::endl;
  //runBucketCardinalityTest();
  //runStreamUniverseTest();
  //runMemoryTest(7);
  runAggregationTests(false);
}

void runBucketCardinalityTest() {
  kAllUnique = true;
  kTrackGold = false;

  std::ofstream pcsa, ll, hll;
  pcsa.open("bct_pcsa.tab");
  ll.open("bct_ll.tab");
  hll.open("bct_hll.tab");

  std::cout << "Running BucketCardinalityTest..." << std::endl;
  for (size_t numElements = 100; numElements <= 1000000000; numElements *= 10) {
    std::cout << "  iterating over bucket sizes for " << numElements << " elements..." << std::endl;;
    for (size_t numBuckets = 2; numBuckets <= 2048; numBuckets *= 2) {
      size_t gold = numElements;
      double e_pcsa = runFixedTest<PCSAEstimator>(numBuckets, numElements, 0, NULL);
      double e_ll = runFixedTest<LogLogEstimator>(numBuckets, numElements, 0, NULL);
      double e_hll = runFixedTest<HyperLogLogEstimator>(numBuckets, numElements, 0, NULL);

      //std::cout << gold << "(" << numBuckets << ") " << e_pcsa << " " << e_ll << " " << e_hll << std::endl;

      pcsa << numElements << "\t" << numBuckets << "\t" << (std::abs(e_pcsa-gold)/gold) << "\n";
      ll << numElements << "\t" << numBuckets << "\t" << (std::abs(e_ll-gold)/gold) << "\n";
      hll << numElements << "\t" << numBuckets << "\t" << (std::abs(e_hll-gold)/gold) << "\n";
    }
  }

  pcsa.close();
  ll.close();
  hll.close();
}

void runStreamUniverseTest() {
  kAllUnique = false;
  kUniformDist = true;
  kTrackGold = true;

  std::ofstream pcsa, ll, hll;
  pcsa.open("sut_pcsa.tab");
  ll.open("sut_ll.tab");
  hll.open("sut_hll.tab");

  size_t numBuckets = 1024;
  size_t numElements = 10000;
  std::cout << "Running StreamUniverseTest..." << std::endl;
  for (size_t universeSize = 100; universeSize < 100000000000; universeSize *= 10) {
    kUniverseSize = universeSize;
    size_t gold = 0;
    double e_pcsa = runFixedTest<PCSAEstimator>(numBuckets, numElements, 0, &gold);
    double e_ll = runFixedTest<LogLogEstimator>(numBuckets, numElements, 0, NULL);
    double e_hll = runFixedTest<HyperLogLogEstimator>(numBuckets, numElements, 0, NULL);

    double ratio = ((double)numElements)/universeSize;
    pcsa << ratio << "\t" << (std::abs(e_pcsa-gold)/gold) << "\n";
    ll << ratio << "\t" << (std::abs(e_ll-gold)/gold) << "\n";
    hll << ratio << "\t" << (std::abs(e_hll-gold)/gold) << "\n";
  }

  pcsa.close();
  ll.close();
  hll.close();

  kUniverseSize = UINT_MAX;
}

void runMemoryTest(size_t exp) {
  kAllUnique = false;
  kUniformDist = true;
  kTrackGold = true;

  std::ofstream pcsa, ll, hll;
  pcsa.open("mt_pcsa_e" + std::to_string(exp) + ".tab");
  ll.open("mt_ll_e" + std::to_string(exp) + ".tab");
  hll.open("mt_hll_e" + std::to_string(exp) + ".tab");

  size_t numElements = pow(10, exp);
  std::cout << "Running MemoryTest (" << numElements << " elements)..." << std::endl;
  for (size_t numHllBuckets = 32; numHllBuckets <= 2048; numHllBuckets *= 2) {
    size_t gold = 0;
    size_t bytes = numHllBuckets*5/8;
    double e_pcsa = runFixedTest<PCSAEstimator>(bytes/4, numElements, 0, &gold);
    double e_ll = runFixedTest<LogLogEstimator>(numHllBuckets, numElements, 0, NULL);
    double e_hll = runFixedTest<HyperLogLogEstimator>(numHllBuckets, numElements, 0, NULL);

    std::cout << bytes << "(" << numHllBuckets << ") " << e_pcsa << " " << e_ll << " " << e_hll << std::endl;

    pcsa << bytes << "\t" << (std::abs(e_pcsa-gold)/gold) << "\n";
    ll << bytes << "\t" << (std::abs(e_ll-gold)/gold) << "\n";
    hll << bytes << "\t" << (std::abs(e_hll-gold)/gold) << "\n";
  }

  pcsa.close();
  ll.close();
  hll.close();
}

void runAggregationTests(bool useMean) {
  kAllUnique = false;
  kUniformDist = true;
  kTrackGold = true;

  std::function<double (double*, int)> combiner;
  if (useMean) {
    combiner = mean;
  } else {
    combiner = median;
  }

  std::ofstream pcsa, ll, hll;
  std::string extension = useMean? "mean" : "median";
  pcsa.open("at_pcsa_" + extension + ".tab");
  ll.open("at_ll_" + extension + ".tab");
  hll.open("at_hll_" + extension + ".tab");

  size_t numBuckets = 1024;
  size_t numElements = 100000;
  std::cout << "Running Aggregation Tests (" << extension << " on " << numElements << " elements)..." << std::endl;
  for (size_t numEstimators = 1; numEstimators <= 128; numEstimators *= 2) {
    size_t gold = 0;
    double e_pcsa = runAggregatedTest<PCSAEstimator>(numBuckets, numElements,
						     numEstimators, 0, &gold, combiner);
    double e_ll = runAggregatedTest<LogLogEstimator>(numBuckets, numElements,
						     numEstimators, 0, NULL, combiner);
    double e_hll = runAggregatedTest<HyperLogLogEstimator>(numBuckets, numElements,
							   numEstimators, 0, NULL, combiner);

    std::cout << numEstimators << " " << e_pcsa << " " << e_ll << " " << e_hll << std::endl;

    pcsa << numEstimators << "\t" << (std::abs(e_pcsa-gold)/gold) << "\n";
    ll << numEstimators << "\t" << (std::abs(e_ll-gold)/gold) << "\n";
    hll << numEstimators << "\t" << (std::abs(e_hll-gold)/gold) << "\n";
  }

  pcsa.close();
  ll.close();
  hll.close();
}
