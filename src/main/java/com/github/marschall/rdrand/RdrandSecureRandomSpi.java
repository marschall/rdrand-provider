package com.github.marschall.rdrand;

import java.security.SecureRandomSpi;
import java.util.Objects;

/**
 * A {@link SecureRandomSpi}s that uses the {@code RDRAND} and {@code RDSEED} hardware instructions.
 *
 * <p>This class should not be instantiated directly.</p>
 */
public class RdrandSecureRandomSpi extends SecureRandomSpi {

  private static final long serialVersionUID = 1L;

  @Override
  protected void engineSetSeed(byte[] seed) {
    Objects.requireNonNull(seed);
    // ignore
  }

  @Override
  protected byte[] engineGenerateSeed(int numBytes) {
    if (numBytes < 0) {
      throw new IllegalArgumentException("numBytes must not be negative");
    }
    byte[] bytes = new byte[numBytes];
    if (numBytes > 0) {
      Rdrand.rdseed(bytes);
    }
    return bytes;
  }


  @Override
  protected void engineNextBytes(byte[] bytes) {
    Objects.requireNonNull(bytes);
    Rdrand.rdrand(bytes);
  }

}
