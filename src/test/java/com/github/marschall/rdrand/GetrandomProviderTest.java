package com.github.marschall.rdrand;

import static com.github.marschall.rdrand.AllZeros.allZeros;
import static org.hamcrest.Matchers.not;
import static org.hamcrest.junit.MatcherAssert.assertThat;
import static org.junit.jupiter.api.Assertions.assertNotNull;

import java.security.GeneralSecurityException;
import java.security.SecureRandom;

import org.junit.jupiter.api.Test;

import com.github.marschall.rdrand.RdrandProvider;

class GetrandomProviderTest {

  @Test
  void getrandom() throws GeneralSecurityException {
    SecureRandom secureRandom;

    secureRandom = SecureRandom.getInstance(RdrandProvider.RDRAND);
    verify(secureRandom, 16); // avoid emptying the entropy pool (/proc/sys/kernel/random/entropy_avail)

    secureRandom = SecureRandom.getInstance(RdrandProvider.RDRAND, RdrandProvider.NAME);
    verify(secureRandom, 16); // avoid emptying the entropy pool (/proc/sys/kernel/random/entropy_avail)
  }

  @Test
  void geturandom() throws GeneralSecurityException {
    SecureRandom secureRandom;

    secureRandom = SecureRandom.getInstance(RdrandProvider.GETURANDOM);
    verify(secureRandom, 128);

    secureRandom = SecureRandom.getInstance(RdrandProvider.GETURANDOM, RdrandProvider.NAME);
    verify(secureRandom, 128);
  }

  private static void verify(SecureRandom secureRandom, int poolSize) {
    assertNotNull(secureRandom);

    byte[] buffer = new byte[poolSize];
    assertThat(buffer, allZeros());

    secureRandom.nextBytes(buffer);
    assertThat(buffer, not(allZeros()));
  }

}
