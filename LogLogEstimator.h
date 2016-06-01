#ifndef LogLog_Included
#define LogLog_Included

#include "stdlib.h"
#include "Hashes.h"

class LogLogEstimator {
public:
  LogLogEstimator(size_t numBuckets);
  ~LogLogEstimator();

  void read(size_t elem);
  double estimate();

private:
  char *buckets;
  size_t numBuckets;
  size_t k;
  HashFunction h;
};

#endif
