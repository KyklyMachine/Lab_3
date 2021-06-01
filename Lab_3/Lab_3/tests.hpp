#ifndef tests_hpp
#define tests_hpp

#include <stdio.h>
#include "Tree_3.hpp"

void TestCreationTree3();
void TestFunctionsTree3();
void TestReduce();
void TestMap();
void AllTests();
double SpeedTestAdd(size_t num);
double SpeedTestSearch(size_t num);
void GraphTestAdd(int step, int max);
void GraphTestSearch(int step, int max);

#endif /* tests_hpp */
