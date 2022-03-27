#include <jni.h>

#include <x86intrin.h>
#include <cpuid.h>

#ifndef bit_RDSEED
  #define bit_RDSEED  (1 << 18)
#endif

/*
 * The maximum number of retries.
 *
 * RDSEED and RDRAND and fail either due to recoverable or not recoverable errors.
 * There is no way to distinct between them so we have to retry but not forever.
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
    if (success != 1)
    {
      _mm_pause();
    }
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
    int length_left = array_length - long_length * 8;
    if (length_left > 0)
    {
      unsigned long long unaligned_data;
      success = _rdrand64_step_retry(&unaligned_data);
      if (success == 1)
      {

        /* write 4 bytes if necessary */
        int int_length = (array_length - long_length * 8) / 4;
        if (int_length != 0)
        {
          unsigned int *int_buffer = (unsigned int*) buffer;
          unsigned int int_value = (unsigned int) (unaligned_data >> 32);
          int_buffer[long_length * 2] = int_value;
        }

        int short_length = (array_length - long_length * 8 - int_length * 4) / 2;
        if (short_length != 0)
        {
          unsigned short *short_buffer = (unsigned short*) buffer;
          unsigned short short_value = (unsigned int) ((unaligned_data >> 16) & 0xffff);
          short_buffer[long_length * 4 + int_length * 2] = short_value;
        }

        /* write 1 byte if necessary */
        int byte_length = array_length - long_length * 8 - int_length * 4 - short_length * 2;
        if (byte_length != 0)
        {
          jbyte byte_value = (jbyte) (unaligned_data & 0xff);
          buffer[array_length - 1] = byte_value;
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
    int length_left = array_length - long_length * 8;
    if (length_left > 0)
    {
      unsigned long long unaligned_data;
      success = _rdseed64_step_retry(&unaligned_data);
      if (success == 1)
      {

        /* write 4 bytes if necessary */
        int int_length = (array_length - long_length * 8) / 4;
        if (int_length != 0)
        {
          unsigned int *int_buffer = (unsigned int*) buffer;
          unsigned int int_value = (unsigned int) (unaligned_data >> 32);
          int_buffer[long_length * 2] = int_value;
        }

        int short_length = (array_length - long_length * 8 - int_length * 4) / 2;
        if (short_length != 0)
        {
          unsigned short *short_buffer = (unsigned short*) buffer;
          unsigned short short_value = (unsigned int) ((unaligned_data >> 16) & 0xffff);
          short_buffer[long_length * 4 + int_length * 2] = short_value;
        }

        /* write 1 byte if necessary */
        int byte_length = array_length - long_length * 8 - int_length * 4 - short_length * 2;
        if (byte_length != 0)
        {
          jbyte byte_value = (jbyte) (unaligned_data & 0xff);
          buffer[array_length - 1] = byte_value;
        }
      }
    }
  }

  (*env)->ReleasePrimitiveArrayCritical(env, bytes, buffer, 0);

  return (success == 1) ? 0 : 1;
}

JNIEXPORT jboolean JNICALL Java_com_github_marschall_rdrand_Rdrand_isRdrandSupported0
  (JNIEnv *env, jclass clazz)
{

  unsigned int eax, ebx, ecx, edx;

  if (__get_cpuid(1, &eax, &ebx, &ecx, &edx))
  {
    if ((ecx & bit_RDRND) == bit_RDRND)
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

JNIEXPORT jboolean JNICALL Java_com_github_marschall_rdrand_Rdrand_isRdseedSupported0
  (JNIEnv *env, jclass clazz)
{

  unsigned int eax, ebx, ecx, edx;

  if (__get_cpuid(7, &eax, &ebx, &ecx, &edx))
  {
    if ((ebx & bit_RDSEED) == bit_RDSEED)
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
