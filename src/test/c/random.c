#include <x86intrin.h>

#include <stdio.h>

int main(void)
{
  unsigned short value;
  int success = _rdrand16_step(&value);

  printf("value: %d\n", value);
  printf("success: %d\n", success);
}
