package com.github.marschall.rdrand;

import static org.junit.jupiter.api.Assertions.assertNotNull;

import java.security.Security;

import org.junit.jupiter.api.Test;

class ProviderInstallationTest {


  @Test
  void getProvider() {
    assertNotNull(Security.getProvider(RdrandProvider.NAME));
  }

}
