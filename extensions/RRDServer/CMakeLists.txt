if(UNISET2_BUILD_RRD)
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

  # Add installation
  #---------------------------------------------------------------------------------------
  install(TARGETS UniSet2RRDServer uniset2-rrdserver
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT uniset2-rrd
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT uniset2-rrd
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT uniset2-rrd
      )
endif()
