if(UNISET2_BUILD_SQLITE)
  message("Build SQLite")
  #---------------------------------------------------------------------------------------
  set(uniset_sqlite_source 
    SQLiteInterface.cc 
    DBServer_SQLite.cc
    )
  # TODO: setup static or shared
  add_library(UniSet2-sqlite SHARED ${uniset_sqlite_source})
  set_target_properties(UniSet2-sqlite PROPERTIES
    VERSION ${CMAKE_PROJECT_VERSION}
    SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
    )
  target_include_directories(UniSet2-sqlite PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  target_link_libraries(UniSet2-sqlite
    uniset2extensions
    UnisetSharedMemory
    ${SQLITE3_LIBRARIES}
    )

  # Add executable
  add_executable(uniset2-sqlite-dbserver main.cc) 
  target_link_libraries(uniset2-sqlite-dbserver UniSet2-sqlite)

  add_executable(sqlite-test test.cc)
  target_link_libraries(sqlite-test UniSet2-sqlite)

  # Add installation
  #---------------------------------------------------------------------------------------
  include(CPack)
  cpack_add_component(uniset2-sqlite
    DESCRIPTION "Backend for sqlite DB"
    )
  install(TARGETS UniSet2-sqlite uniset2-sqlite-dbserver
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
      COMPONENT uniset2-sqlite
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT uniset2-sqlite
      ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT uniset2-sqlite
    )
endif()
