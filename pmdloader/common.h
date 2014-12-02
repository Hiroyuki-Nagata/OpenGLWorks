#ifndef COMMON_H_
#define COMMON_H_

#ifdef _WIN32
   #include <windows.h>
#else
   #include <cstring>
   typedef unsigned char      BYTE;
   typedef bool               BOOL;
   typedef unsigned short int WORD;
   typedef unsigned long int  DWORD;
   #define __USE_POSIX          1   // needed for limits.h
   #define __USE_XOPEN2K        1
   #define __STDC_FORMAT_MACROS 1   // needed for unix formatting output
   #include <cstdio>
   #include <cstdarg>
   #include <cstring>
   #include <unistd.h>
   #include <limits.h>
   #include <errno.h>

   #ifndef TRUE
      #define TRUE true
   #endif

   #ifndef FALSE
      #define FALSE false
   #endif

   /** MSW _countof */
   #include <type_traits>
   template < typename T, size_t N >
   size_t countof( T ( & arr )[ N ] )
   {
       return std::extent< T[ N ] >::value;
   }

#endif

#ifdef _WIN32
   #if defined(WIN32) && !defined(__MINGW32__) && !defined(__MINGW64__)
      #define MAX_PATH _MAX_PATH
   #else  // MSVC
      #define MAX_PATH FILENAME_MAX
   #endif // MinGW32,64
#elif  __unix__
   #define MAX_PATH _POSIX_PATH_MAX
#else // Linux/BSD/MacOSX
   #error "MAX_PATH is undefined"
#endif

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <algorithm>
#include <functional> 
#include <iomanip>

typedef std::vector<std::string> FIELDS;

float ToRadian(float x);
float ToDegree(float x);

#define NEW_FIELD(x) (x).clear()  

/** For debug log. Usage ./configure CXXFLAGS=-DDEBUG_BUILD; make */
#if defined(DEBUG_BUILD) && defined(__GNUC__)
#  define DEBUG(fmt, ...) printf("%s(): " fmt, __func__, ## __VA_ARGS__)
#else
#  define DEBUG(x, ...) do {} while (0)
#endif

#endif /** COMMON_H_ */
