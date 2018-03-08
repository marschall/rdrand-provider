package com.github.marschall.rdrand;

import org.assertj.core.api.AbstractAssert;

final class AllZeroBytesAssert extends AbstractAssert<AllZeroBytesAssert, byte[]> {

  AllZeroBytesAssert(byte[] actual) {
    super(actual, AllZeroBytesAssert.class);
  }

  static AllZeroBytesAssert assertThat(byte[] actual) {
    return new AllZeroBytesAssert(actual);
  }

  AllZeroBytesAssert allZeros() {
    isNotNull();

    for (byte b : this.actual) {
      if (b != 0) {
        failWithMessage("Expected only 0 but found <%s> in <%s>", b, this.actual);
      }
    }

    return this;
  }

  AllZeroBytesAssert notAllZeros() {
    isNotNull();

    boolean foundNotZero = false;
    for (byte b : this.actual) {
      if (b != 0) {
        foundNotZero = true;
        break;
      }
    }

    if (!foundNotZero) {
      failWithMessage("Expected at least one 0 value but found only 0 in <%s>", this.actual);
    }

    return this;
  }

}
