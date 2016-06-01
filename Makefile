CXXFLAGS = -std=c++11 -Wall -Werror -O0 -g
CXX = g++

OBJECTS = Main.o PCSAEstimator.o LogLogEstimator.o HyperLogLogEstimator.o RoughEstimator.o

default: run-tests

run-tests: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

Main.o: Main.cc Testing.h PCSAEstimator.h LogLogEstimator.h HyperLogLogEstimator.h RoughEstimator.h

%.o: %.cc %.h

clean:
	rm -f run-tests *.o *~