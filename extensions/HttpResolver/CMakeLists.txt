if(ENABLE_REST_API)
  message("Build REST resolver")
  #---------------------------------------------------------------------------------------
  add_executable(uniset2-httpresolver 
    HttpResolver.cc
    main.cc
    ) 
  target_link_libraries(uniset2-httpresolver uniset2)

  # Add installation
  #---------------------------------------------------------------------------------------
  install(TARGETS uniset2-httpresolver
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
      COMPONENT uniset2-uresolver
    )
endif()
