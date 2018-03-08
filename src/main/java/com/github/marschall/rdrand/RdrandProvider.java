package com.github.marschall.rdrand;

import java.security.Provider;

/**
 * A security provider that installs one random number generation
 * algorithms that use the <a href="https://lwn.net/Articles/606141/">RDAND</a>
 * and <code>RDSEED<code> hardware instructions.
 *
 * @see <a href="https://docs.oracle.com/javase/8/docs/technotes/guides/security/crypto/HowToImplAProvider.html">How to Implement a Provider in the Java Cryptography Architecture</a>
 */
public final class RdrandProvider extends Provider {

  /**
   * The name of this security provider.
   */
  public static final String NAME = "rdrand";

  /**
   * The name algorithm that uses the {@code RDRAND} and {@code RDSEED} hardware instructions.
   */
  public static final String ALGORITHM = "rdrand";

  private static final long serialVersionUID = 1L;

  public RdrandProvider() {
    super(NAME, 0.1d, "rdrand (SecureRandom)");
    this.put("SecureRandom." + ALGORITHM, RdrandSecureRandomSpi.class.getName());
    this.put("SecureRandom." + ALGORITHM + " ThreadSafe", "true");
//    this.put("SecureRandom." + ALGORITHM + " ImplementedIn", "Hardware");
  }

}
