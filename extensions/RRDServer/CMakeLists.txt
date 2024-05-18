# TODO build only if ENABLE_MQTT
# TODO setup shared or static
add_library(UniSet2RRDServer SHARED RRDServer.cc)
set_target_properties(UniSet2RRDServer PROPERTIES
  VERSION ${CMAKE_PROJECT_VERSION}
  SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
  )
target_link_libraries(UniSet2RRDServer
  uniset2extensions
  UnisetSharedMemory
  ${RRD_LIBRARIES}
  )
# Add executable
add_executable(uniset2-rrdserver main.cc) 
target_link_libraries(uniset2-rrdserver UniSet2RRDServer)

