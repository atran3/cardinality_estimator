#ifndef LogLog_Included
#define LogLog_Included

#include "stdlib.h"

class LogLogEstimator {
public:
  LogLogEstimator(size_t numBuckets);
  ~LogLogEstimator();

  void read(double elem);
  double estimate();

private:
};

#endif
