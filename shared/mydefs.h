#pragma once

#ifdef _MSC_VER
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLLEXPORT  __attribute__ ((dllexport))
#endif //#ifdef _MSC_VER

#define HAVE_STRUCT_TIMESPEC 1
#include <stdio.h>
extern FILE _iob[3];

#ifdef __cplusplus
extern "C"
{
#endif
	FILE * __cdecl __iob_func(void);
#ifdef __cplusplus
}
#endif
