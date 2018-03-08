module com.github.marschall.rdrand {
  provides java.security.Provider with com.github.marschall.rdrand.RdrandProvider;
  exports com.github.marschall.rdrand;
}
