if(UNISET2_BUILD_MYSQL)
  message("Build MYSQL")
  #---------------------------------------------------------------------------------------
  set(uniset_mysql_source 
    MySQLInterface.cc 
    DBServer_MySQL.cc
    )
  # TODO: setup static or shared
  add_library(UniSet2-mysql SHARED ${uniset_mysql_source})
  set_target_properties(UniSet2-mysql PROPERTIES
    VERSION ${CMAKE_PROJECT_VERSION}
    SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
    )
  target_link_libraries(UniSet2-mysql
    uniset2extensions
    UnisetSharedMemory
    ${MYSQL_LIBRARIES}
    )
  # Add executable
  add_executable(uniset2-mysql-dbserver main.cc) 
  target_link_libraries(uniset2-mysql-dbserver UniSet2-mysql)

  add_executable(mysql-test test.cc)
  target_link_libraries(mysql-test UniSet2-mysql)

  # Add installation
  #---------------------------------------------------------------------------------------
  install(TARGETS UniSet2-mysql uniset2-mysql-dbserver
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
      COMPONENT uniset2-mysql
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT uniset2-mysql
      ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT uniset2-mysql
    )
endif()
