
#include <inttypes.h>

typedef float  f;
typedef double d;
typedef unsigned int  uint;
typedef unsigned char bool;
typedef unsigned char flags;
typedef unsigned char byte;
typedef unsigned char u8;
typedef          char i8;
typedef unsigned short u16;
typedef          short i16;
typedef unsigned int u32;
typedef          int i32;
typedef unsigned long long ull;
typedef unsigned long long u64;
typedef          long long i64;
typedef unsigned long ulong;
typedef unsigned long ul;
typedef  int_fast8_t  dc;
typedef uint_fast8_t  db;
typedef  int_fast16_t ds;
typedef uint_fast16_t dw;
typedef  int_fast32_t di;
typedef uint_fast32_t dd;
typedef  int_fast64_t dl;
typedef uint_fast64_t dq;
typedef  int_fast64_t clockT;
typedef uint_fast8_t* cstr;

// MISSING DECLARATIONS >:(
#include <stdio.h>
errno_t freopen_s(FILE**newstreamptr,
	char*filename, char*mode, FILE*stream);
int __getmainargs(int * _Argc, char *** _Argv, char *** _Env, int _DoWildCard);

#ifndef COMMON_H_
#define COMMON_H_
#endif//COMMON_H_
