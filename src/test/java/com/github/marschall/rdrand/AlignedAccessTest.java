package com.github.marschall.rdrand;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.Test;
import org.openjdk.jol.info.ClassLayout;
import org.openjdk.jol.info.FieldLayout;

class AlignedAccessTest {

  @Test
  void byteArrayDoubleWordAligned() {
    ClassLayout classLayout = ClassLayout.parseInstance(new byte[2]);
    System.out.println(classLayout.toPrintable());

    FieldLayout byteField = classLayout.fields().stream()
            .filter(fieldLayout -> fieldLayout.typeClass().equals("byte"))
            .findFirst()
            .get();

    assertEquals(0, byteField.offset() % 8, "byte array content is not double word aligned");
  }

}
