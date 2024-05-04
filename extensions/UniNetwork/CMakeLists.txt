add_library(UniSet2Network UniExchange.cc)
target_link_libraries(UniSet2Network
  uniset2extensions
  UnisetSharedMemory
  )
# Add executable
add_executable(uniset2-network uninet.cc)
target_link_libraries(uniset2-network UniSet2Network)
