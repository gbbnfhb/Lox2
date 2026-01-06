#ifdef _WIN32
  #define DLLEXPORT __declspec(dllexport)
#else
  #define DLLEXPORT
#endif

DLLEXPORT int add(int a, int b) {
    return a + b;
}