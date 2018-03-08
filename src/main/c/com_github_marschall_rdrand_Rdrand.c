#include <jni.h>

#include <immintrin.h>
#include <cpuid.h>

#ifndef bit_RDSEED
  #define bit_RDSEED  (1 << 18)
#endif

#define __RDRND__ 1

#include "com_github_marschall_rdrand_Rdrand.h"


JNIEXPORT jint JNICALL Java_com_github_marschall_rdrand_Rdrand_rdrand0
  (JNIEnv *env, jclass clazz, jbyteArray bytes, jint array_length)
{
  _Static_assert (sizeof(jbyte) == sizeof(char), "sizeof(jbyte) == sizeof(char)");
  _Static_assert (sizeof(jint) == sizeof(int), "sizeof(jint) == sizeof(int)");

  jboolean is_copy;
  int ret = 0;

  jbyte *buffer = (*env)->GetPrimitiveArrayCritical(env, bytes, &is_copy);
  if (buffer == NULL)
  {
    return -1;
  }

  /* write 8 bytes at a time */
  int long_length = array_length / 8;
  unsigned long long *long_buffer = (unsigned long long *) buffer;
  for (int i = 0; i < long_length; i += 8)
  {
    ret = _rdrand64_step(&long_buffer[i]);
    if (ret != 0)
    {
      break;
    }
  }

  if (ret == 0)
  {
    /* write 4 bytes if necessary */
    int int_length = (array_length - long_length) / 4;
    if (int_length != 0)
    {
      unsigned int *int_buffer = (unsigned int *) buffer;
      ret = _rdrand32_step(&int_buffer[long_length * 2]);
    }

    /* write 2 bytes if necessary */
    if (ret == 0) {
      int short_length = (array_length - long_length - int_length) / 2;
      unsigned short short_value;
    }

    /* write 1 byte if necessary */
      unsigned short last_short_value;
  }

  (*env)->ReleasePrimitiveArrayCritical(env, bytes, buffer, 0);

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
