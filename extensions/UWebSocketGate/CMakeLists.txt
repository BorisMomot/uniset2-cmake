# TODO build only if ENABLE_UWEBSOCKETGATE
add_library(UniSet2UWebSocketGate UWebSocketGate.cc) 
target_compile_features(UniSet2UWebSocketGate PUBLIC cxx_std_17)
target_link_libraries(UniSet2UWebSocketGate 
  uniset2
  uniset2extensions
  UnisetSharedMemory
  )

add_executable(uniset2-wsgate main.cc) 
target_compile_features(uniset2-wsgate PUBLIC cxx_std_17)
target_link_libraries(uniset2-wsgate UniSet2UWebSocketGate)
