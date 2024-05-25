if(UNISET2_BUILD_MQTT)
  message("Build MQTT")
  #---------------------------------------------------------------------------------------
  # TODO setup shared or static
  add_library(UniSet2MQTTPublisher SHARED MQTTPublisher.cc)
  set_target_properties(UniSet2MQTTPublisher PROPERTIES
    VERSION ${CMAKE_PROJECT_VERSION}
    SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
    )
  target_link_libraries(UniSet2MQTTPublisher
    uniset2extensions
    UnisetSharedMemory
    ${MQTT_LIBRARIES}
    )
  # Add executable
  add_executable(uniset2-mqttpublisher main.cc) 
  target_link_libraries(uniset2-mqttpublisher UniSet2MQTTPublisher)

  # Add installation
  #---------------------------------------------------------------------------------------
  install(TARGETS UniSet2MQTTPublisher uniset2-mqttpublisher
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
      COMPONENT uniset2-mqtt
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT uniset2-mqtt
      ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT uniset2-mqtt
    )
endif()
