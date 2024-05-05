# TODO build only if ENABLE_MQTT
add_library(UniSet2RRDServer RRDServer.cc)
target_link_libraries(UniSet2RRDServer
  uniset2extensions
  UnisetSharedMemory
  ${RRD_LIBRARIES}
  )
# Add executable
add_executable(uniset2-rrdserver main.cc) 
target_link_libraries(uniset2-rrdserver UniSet2RRDServer)

