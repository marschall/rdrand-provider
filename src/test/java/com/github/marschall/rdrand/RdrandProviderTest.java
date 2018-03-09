package com.github.marschall.rdrand;

import static org.assertj.core.api.Assertions.assertThat;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assumptions.assumeTrue;

import java.security.GeneralSecurityException;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;

class RdrandProviderTest {

  private SecureRandom secureRandom;

  @BeforeEach
  void setUp() throws NoSuchAlgorithmException {
    this.secureRandom = SecureRandom.getInstance(RdrandProvider.ALGORITHM);
  }

  @Test
  @Disabled("does not work on old mac")
  void isavailalbe() {
    Rdrand.assertAvailable();
  }

  @Test
  void alternativeInstantiation() throws GeneralSecurityException {
    assertNotNull(SecureRandom.getInstance(RdrandProvider.ALGORITHM, RdrandProvider.NAME));
  }

  @Test
  void rdrand() throws GeneralSecurityException {
    assertNotNull(this.secureRandom);
    verifyBytesVariousBufferSizes(this.secureRandom);
  }

  @Test
  void rdseed() throws GeneralSecurityException {
    assumeTrue(Rdrand.isRdseedSupported());
    assertNotNull(this.secureRandom);
    verifySeedVariousBufferSizes(this.secureRandom);
  }

  private static void verifyBytesVariousBufferSizes(SecureRandom secureRandom) {
    for (int i = 1; i < 16; i++) {
      verifyBytes(secureRandom, i);
    }

    verifyBytes(secureRandom, 1024);
  }

  private static void verifyBytes(SecureRandom secureRandom, int poolSize) {
    byte[] buffer = new byte[poolSize];
    AllZeroBytesAssert.assertThat(buffer).allZeros();

    secureRandom.nextBytes(buffer);
    AllZeroBytesAssert.assertThat(buffer).notAllZeros();
  }

  private static void verifySeedVariousBufferSizes(SecureRandom secureRandom) {
    for (int i = 1; i < 16; i++) {
      verifySeed(secureRandom, i);
    }

    verifySeed(secureRandom, 1024);
  }

  private static void verifySeed(SecureRandom secureRandom, int poolSize) {
    byte[] seed = secureRandom.generateSeed(poolSize);
    assertThat(seed).hasSize(poolSize);
    AllZeroBytesAssert.assertThat(seed).notAllZeros();
  }

}
