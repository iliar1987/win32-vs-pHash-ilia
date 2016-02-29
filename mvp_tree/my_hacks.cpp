#include <stdio.h>
#include "mydefs.h"

FILE _iob[] = { *stdin, *stdout, *stderr };

FILE * __cdecl __iob_func(void)
{
	return _iob;
}
