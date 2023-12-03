#ifndef DEBUGUTILS_H
#define DEBUGUTILS_H

#ifdef DEBUG

#include <iostream>
#define LOG(X) std::cout << X << std::endl;
#define LOG_NNL(X) std::cout << X;

#else

#define LOG(X)
#define LOG_NNL(x)

#endif

#endif