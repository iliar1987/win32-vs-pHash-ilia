#ifdef _MSC_VER
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLLEXPORT  __attribute__ ((dllexport))
#endif //#ifdef _MSC_VER
