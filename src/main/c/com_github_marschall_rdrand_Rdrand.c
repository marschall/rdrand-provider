#include <jni.h>

//#include <immintrin.h>
#include <x86intrin.h>
#include <cpuid.h>

#ifndef bit_RDSEED
  #define bit_RDSEED  (1 << 18)
#endif

/*
 * The maximum number of retries.
 */
#define MAX_RETRIES 100

#include "com_github_marschall_rdrand_Rdrand.h"

static inline int _rdrand64_step_retry(unsigned long long *__P)
{
  int success = 0;
  int calls = 0;
  do
  {
    success = _rdrand64_step(__P);
    calls += 1;
  }
  while (success != 1 && calls < MAX_RETRIES);
  return success;
}

static inline int _rdrand32_step_retry(unsigned int *__P)
{
  int success = 0;
  int calls = 0;
  do
  {
    success = _rdrand32_step(__P);
    calls += 1;
  }
  while (success != 1 && calls < MAX_RETRIES);
  return success;
}

static inline int _rdrand16_step_retry(unsigned short *__P)
{
  int success = 0;
  int calls = 0;
  do
  {
    success = _rdrand16_step(__P);
    calls += 1;
  }
  while (success != 1 && calls < MAX_RETRIES);
  return success;
}

static inline int _rdseed64_step_retry(unsigned long long *__P)
{
  int success = 0;
  int calls = 0;
  do
  {
    success = _rdseed64_step(__P);
    calls += 1;
  }
  while (success != 1 && calls < MAX_RETRIES);
  return success;
}

static inline int _rdseed32_step_retry(unsigned int *__P)
{
  int success = 0;
  int calls = 0;
  do
  {
    success = _rdseed32_step(__P);
    calls += 1;
  }
  while (success != 1 && calls < MAX_RETRIES);
  return success;
}

static inline int _rdseed16_step_retry(unsigned short *__P)
{
  int success = 0;
  int calls = 0;
  do
  {
    success = _rdseed16_step(__P);
    calls += 1;
  }
  while (success != 1 && calls < MAX_RETRIES);
  return success;
}

JNIEXPORT jint JNICALL Java_com_github_marschall_rdrand_Rdrand_rdrand0
  (JNIEnv *env, jclass clazz, jbyteArray bytes, jint array_length)
{
  _Static_assert (sizeof(jbyte) == sizeof(char), "sizeof(jbyte) == sizeof(char)");
  _Static_assert (sizeof(jint) == sizeof(int), "sizeof(jint) == sizeof(int)");

  jboolean is_copy;
  int success = 1;

  jbyte *buffer = (*env)->GetPrimitiveArrayCritical(env, bytes, &is_copy);
  if (buffer == NULL)
  {
    return -1;
  }

  /* write 8 bytes at a time */
  int long_length = array_length / 8;
  unsigned long long *long_buffer = (unsigned long long*) buffer;
  for (int i = 0; i < long_length; i++)
  {
    success = _rdrand64_step_retry(&long_buffer[i]);
    if (success != 1)
    {
      break;
    }
  }

  if (success == 1)
  {
    /* write 4 bytes if necessary */
    int int_length = (array_length - long_length * 8) / 4;
    if (int_length != 0)
    {
      unsigned int *int_buffer = (unsigned int*) buffer;
      success = _rdrand32_step_retry(&int_buffer[long_length * 2]);
    }

    /* write 2 bytes if necessary */
    if (success == 1)
    {
      int short_length = (array_length - long_length * 8 - int_length * 4) / 2;
      if (short_length != 0)
      {
        unsigned short *short_buffer = (unsigned short*) buffer;
        success = _rdrand16_step_retry(&short_buffer[long_length * 4 + int_length * 2]);
      }

      /* write 1 byte if necessary */
      if ((success == 1) && (array_length - long_length * 8 - int_length * 4 - short_length * 2 != 0)) {
        unsigned short last_short_value;
        success = _rdrand16_step_retry(&last_short_value);
        if (success == 1)
        {
          buffer[array_length - 1] = (jbyte) last_short_value;
        }
      }

    }
  }

  (*env)->ReleasePrimitiveArrayCritical(env, bytes, buffer, 0);

  return (success == 1) ? 0 : 1;
}

JNIEXPORT jint JNICALL Java_com_github_marschall_rdrand_Rdrand_rdseed0
  (JNIEnv *env, jclass clazz, jbyteArray bytes, jint array_length)
{
  _Static_assert (sizeof(jbyte) == sizeof(char), "sizeof(jbyte) == sizeof(char)");
  _Static_assert (sizeof(jint) == sizeof(int), "sizeof(jint) == sizeof(int)");

  jboolean is_copy;
  int success = 1;

  jbyte *buffer = (*env)->GetPrimitiveArrayCritical(env, bytes, &is_copy);
  if (buffer == NULL)
  {
    return -1;
  }

  /* write 8 bytes at a time */
  int long_length = array_length / 8;
  unsigned long long *long_buffer = (unsigned long long*) buffer;
  for (int i = 0; i < long_length; i++)
  {
    success = _rdseed64_step_retry(&long_buffer[i]);
    if (success != 1)
    {
      break;
    }
  }

  if (success == 1)
  {
    /* write 4 bytes if necessary */
    int int_length = (array_length - long_length * 8) / 4;
    if (int_length != 0)
    {
      unsigned int *int_buffer = (unsigned int*) buffer;
      success = _rdseed32_step_retry(&int_buffer[long_length * 2]);
    }

    /* write 2 bytes if necessary */
    if (success == 1)
    {
      int short_length = (array_length - long_length * 8 - int_length * 4) / 2;
      if (short_length != 0)
      {
        unsigned short *short_buffer = (unsigned short*) buffer;
        success = _rdseed16_step_retry(&short_buffer[long_length * 4 + int_length * 2]);
      }

      /* write 1 byte if necessary */
      if ((success == 1) && (array_length - long_length * 8 - int_length * 4 - short_length * 2 != 0)) {
        unsigned short last_short_value;
        success = _rdseed16_step_retry(&last_short_value);
        if (success == 1)
        {
          buffer[array_length - 1] = (jbyte) last_short_value;
        }
      }

    }
  }

  (*env)->ReleasePrimitiveArrayCritical(env, bytes, buffer, 0);

  return (success == 1) ? 0 : 1;
}

JNIEXPORT jboolean JNICALL Java_com_github_marschall_rdrand_Rdrand_isAvailable0
  (JNIEnv *env, jclass clazz)
{

  unsigned int sig, eax, ebx, ecx, edx;

  __get_cpuid_max(0x80000000, &sig);
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
