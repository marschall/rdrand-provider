#include <cpuid.h>
#include <stdio.h>

#ifndef bit_RDSEED
  #define bit_RDSEED  (1 << 18)
#endif

int main(void)
{
  unsigned int sig, eax, ebx, ecx, edx;

  __get_cpuid_max(0, &sig);
  printf("sig %d\n", sig);
  if (__get_cpuid(7, &eax, &ebx, &ecx, &edx))
  {
    printf("(ebx & bit_RDSEED) == bit_RDSEED %d\n", (ebx & bit_RDSEED) == bit_RDSEED);
    printf("true\n");
  }
  else
  {
    printf("false\n");
  }
  if (__get_cpuid(1, &eax, &ebx, &ecx, &edx))
  {
    printf("(ecx & bit_RDRND) == bit_RDRND %d\n", (ecx & bit_RDRND) == bit_RDRND);
    printf("true\n");
  }
  else
  {
    printf("false\n");
  }
}
