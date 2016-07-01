  
#ifndef bagchal_engine_types_h
#define bagchal_engine_types_h

#include <stdio.h>

//#define MS_VC_PLUS_PLUS
#ifdef MS_VC_PLUS_PLUS
	typedef unsigned __int64 i64_t;
	typedef unsigned __int32 i32_t;
	typedef unsigned __int8 i8_t;
#else
	typedef unsigned long long i64_t;
	typedef unsigned long i32_t;
	typedef unsigned char i8_t;
#endif

typedef char i2_t;
typedef char i1_t;


typedef i1_t Boolean_t;

#define TRUE 1
#define FALSE 0

#endif

