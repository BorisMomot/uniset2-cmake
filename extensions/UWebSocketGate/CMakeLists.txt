# TODO build only if ENABLE_UWEBSOCKETGATE
# TODO setup share or static
add_library(UniSet2UWebSocketGate SHARED UWebSocketGate.cc) 
set_target_properties(UniSet2UWebSocketGate PROPERTIES
  VERSION ${CMAKE_PROJECT_VERSION}
  SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
  )
target_compile_features(UniSet2UWebSocketGate PUBLIC cxx_std_17)
target_link_libraries(UniSet2UWebSocketGate 
  uniset2
  uniset2extensions
  UnisetSharedMemory
  )

add_executable(uniset2-wsgate main.cc) 
target_compile_features(uniset2-wsgate PUBLIC cxx_std_17)
target_link_libraries(uniset2-wsgate UniSet2UWebSocketGate)
