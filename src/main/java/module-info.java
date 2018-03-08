module com.github.marschall.rdrand {
  provides java.security.Provider with com.github.marschall.rdrand.GetrandomProvider;
  exports com.github.marschall.getrandom;
}
