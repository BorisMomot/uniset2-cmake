# TODO build only if ENABLE_MQTT
add_library(UniSet2MQTTPublisher MQTTPublisher.cc)
target_link_libraries(UniSet2MQTTPublisher
  uniset2extensions
  UnisetSharedMemory
  ${MQTT_LIBRARIES}
  )
# Add executable
add_executable(uniset2-mqttpublisher main.cc) 
target_link_libraries(uniset2-mqttpublisher UniSet2MQTTPublisher)
