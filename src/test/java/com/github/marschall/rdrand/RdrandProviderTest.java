package com.github.marschall.rdrand;

import static com.github.marschall.rdrand.AllZeros.allZeros;
import static org.hamcrest.Matchers.not;
import static org.hamcrest.junit.MatcherAssert.assertThat;
import static org.junit.jupiter.api.Assertions.assertNotNull;

import java.security.GeneralSecurityException;
import java.security.SecureRandom;

import org.junit.jupiter.api.Test;

import com.github.marschall.rdrand.RdrandProvider;

class RdrandProviderTest {

  @Test
  void getrandom() throws GeneralSecurityException {
    SecureRandom secureRandom;

    secureRandom = SecureRandom.getInstance(RdrandProvider.RDRAND);
    verify(secureRandom, 1024);

    secureRandom = SecureRandom.getInstance(RdrandProvider.RDRAND, RdrandProvider.NAME);
    verify(secureRandom, 1024);
  }

  private static void verify(SecureRandom secureRandom, int poolSize) {
    assertNotNull(secureRandom);

    byte[] buffer = new byte[poolSize];
    assertThat(buffer, allZeros());

    secureRandom.nextBytes(buffer);
    assertThat(buffer, not(allZeros()));

    byte[] seed = secureRandom.generateSeed(poolSize);
    assertThat(seed, not(allZeros()));
  }

}
