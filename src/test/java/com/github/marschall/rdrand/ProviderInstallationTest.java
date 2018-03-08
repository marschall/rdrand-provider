package com.github.marschall.rdrand;

import java.security.Security;

import org.junit.jupiter.api.Test;

import com.github.marschall.rdrand.GetrandomProvider;

class ProviderInstallationTest {


  @Test
  void getProvider() {
    Security.getProvider(GetrandomProvider.NAME);
  }

}
