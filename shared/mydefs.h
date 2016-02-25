#ifdef _MSC_VER
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLLEXPORT  __attribute__ ((dllexport))
#endif //#ifdef _MSC_VER

#define HAVE_STRUCT_TIMESPEC 1
#include <stdio.h>
FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}
