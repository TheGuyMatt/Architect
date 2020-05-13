#ifndef LOG_HPP
#define LOG_HPP

//https://github.com/MetaCipher/sdl-2.0-textures/blob/master/Log.h

#include <stdio.h>

#define DEBUG 1

#ifdef DEBUG
#define Log(...) printf(__VA_ARGS__); printf("\n");
#else
#define Log(...) ;
#endif

#endif