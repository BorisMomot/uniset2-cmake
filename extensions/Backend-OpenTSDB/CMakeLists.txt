if(UNISET2_BUILD_TSDB)
  message("Build TSDB")
  #---------------------------------------------------------------------------------------
  # TODO setup static or shared
  add_library(UniSet2BackendOpenTSDB SHARED BackendOpenTSDB.cc)
  set_target_properties(UniSet2BackendOpenTSDB PROPERTIES
    VERSION ${CMAKE_PROJECT_VERSION}
    SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
    )
  target_link_libraries(UniSet2BackendOpenTSDB
    uniset2
    uniset2extensions 
    UnisetSharedMemory
    )

  add_executable(uniset2-backend-opentsdb main.cc)
  target_link_libraries(uniset2-backend-opentsdb UniSet2BackendOpenTSDB)

  # Add installation
  #---------------------------------------------------------------------------------------
  install(TARGETS UniSet2BackendOpenTSDB uniset2-backend-opentsdb
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
      COMPONENT uniset2-opentsdb
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT uniset2-opentsdb
      ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT uniset2-opentsdb
    )
endif()
