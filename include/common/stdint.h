//
// include/common/stdint.h
//

#ifndef _STDINT_H_
#define _STDINT_H_

// Definite length types
typedef   signed char  int8_t;
typedef   signed short int16_t;
typedef   signed int   int32_t;
typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;

#if __WORDSIZE == 64
  typedef   signed long int64_t;
  typedef unsigned long uint64_t;
#else
  typedef   signed long long int64_t;
  typedef unsigned long long uint64_t;
#endif

// Least types
typedef int8_t   int_least8_t;
typedef int16_t  int_least16_t;
typedef int32_t  int_least32_t;
typedef int64_t  int_least64_t;
typedef uint8_t  uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;

// Fast types
typedef int32_t  int_least8_t;
typedef int32_t  int_least16_t;
typedef int32_t  int_least32_t;
typedef int64_t  int_least64_t;
typedef uint32_t uint_least8_t;
typedef uint32_t uint_least16_t;
typedef uint32_t uint_least32_t;
typedef uint64_t uint_least64_t;

// Intptr types
typedef   signed long intptr_t;
typedef unsigned long uintptr_t;

// Max length types
typedef   signed long long intmax_t;
typedef unsigned long long uintmax_t;

#endif
