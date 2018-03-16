package com.github.marschall.rdrand;

import org.junit.jupiter.api.Test;
import org.openjdk.jol.info.ClassLayout;

class AlignedAccessTest {

  @Test
  void byteArrayDoubleWordAligned() {
    ClassLayout classLayout = ClassLayout.parseInstance(new byte[2]);
    System.out.println(classLayout.toPrintable());
  }

}
