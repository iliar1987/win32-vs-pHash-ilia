#include "pHash.h"

int main()
{
	int npoints;
	char filename[] = "C:\source\pHash\win32-vs-pHash\include\pngconf.h";
	TxtHashPoint* p = ph_texthash(filename, &npoints);

	return 0;
}