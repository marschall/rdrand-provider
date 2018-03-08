#include <jni.h>

#include <immintrin.h>
#include <cpuid.h>

#ifndef bit_RDSEED
  #define bit_RDSEED  (1 << 18)
#endif

#include "com_github_marschall_rdrand_Rdrand.h"


JNIEXPORT jint JNICALL Java_com_github_marschall_rdrand_Rdrand_rdrand0
  (JNIEnv *env, jclass clazz, jbyteArray bytes, jint arrayLength)
{
  _Static_assert (sizeof(jbyte) == sizeof(char), "sizeof(jbyte) == sizeof(char)");

  return 0;
}

JNIEXPORT jint JNICALL Java_com_github_marschall_rdrand_Rdrand_rdseed0
  (JNIEnv *env, jclass clazz, jbyteArray bytes, jint arrayLength)
{
  _Static_assert (sizeof(jbyte) == sizeof(char), "sizeof(jbyte) == sizeof(char)");

  return 0;
}

JNIEXPORT jboolean JNICALL Java_com_github_marschall_rdrand_Rdrand_isAvailable0
  (JNIEnv *env, jclass clazz)
{

  unsigned int sig, eax, ebx, ecx, edx;

  __get_cpuid_max (0x80000000, &sig);
  if (__get_cpuid(sig, &eax, &ebx, &ecx, &edx))
  {
    if (((ecx & bit_RDRND) == bit_RDRND) && ((ebx & bit_RDSEED) == bit_RDSEED))
    {
      return JNI_TRUE;
    }
    else
    {
      return JNI_FALSE;
    }
  }
  else
  {
    return JNI_FALSE;
  }
}
