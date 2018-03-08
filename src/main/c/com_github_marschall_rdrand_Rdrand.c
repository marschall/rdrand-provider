#include <jni.h>

#include <immintrin.h>
#include <cpuid.h>

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

  unsigned int eax, ebx, ecx, edx;
  if (__get_cpuid(1, &eax, &ebx, &ecx, &edx))
  {
    /* if (((ecx & bit_RDRND) == bit_RDRND) && ((ebx & bit_RDSEED) == bit_RDSEED)) */
    if (((ecx & bit_RDRND) == bit_RDRND))
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
