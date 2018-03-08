package com.github.marschall.rdrand;

import static org.junit.jupiter.api.Assertions.assertNotNull;

import java.security.GeneralSecurityException;
import java.security.SecureRandom;
import static org.assertj.core.api.Assertions.assertThat;

import org.junit.jupiter.api.Test;

class RdrandProviderTest {

  @Test
  void getrandom() throws GeneralSecurityException {
    SecureRandom secureRandom;

    secureRandom = SecureRandom.getInstance(RdrandProvider.ALGORITHM);
    verify(secureRandom, 1024);

    secureRandom = SecureRandom.getInstance(RdrandProvider.ALGORITHM, RdrandProvider.NAME);
    verify(secureRandom, 1024);
  }

  private static void verify(SecureRandom secureRandom, int poolSize) {
    assertNotNull(secureRandom);

    byte[] buffer = new byte[poolSize];
    AllZeroBytesAssert.assertThat(buffer).allZeros();

    secureRandom.nextBytes(buffer);
    AllZeroBytesAssert.assertThat(buffer).notAllZeros();

    byte[] seed = secureRandom.generateSeed(poolSize);
    assertThat(seed).hasSize(poolSize);
    AllZeroBytesAssert.assertThat(seed).notAllZeros();
  }

}
