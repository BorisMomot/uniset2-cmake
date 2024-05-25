if(UNISET2_BUILD_LOGDB)
  add_executable(uniset2-logdb
    LogDB.cc 
    main.cc
    )
  target_link_libraries(uniset2-logdb
    uniset2
    UniSet2-sqlite
    )

  add_executable(uniset2-logdb-conv logdb-conv.cc)
  target_link_libraries(uniset2-logdb-conv
    uniset2
    UniSet2-sqlite
    )

  # Add installation
  #---------------------------------------------------------------------------------------
  install(TARGETS uniset2-logdb uniset2-logdb-conv 
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
      COMPONENT uniset2-logdb
    )
  # TODO: install script uniset2-logdb-adm
endif()
