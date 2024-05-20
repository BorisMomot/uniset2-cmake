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
  include(CPack)
  cpack_add_component(uniset2-httpresolver
    DESCRIPTION "HTTP Resolver"
    )
  install(TARGETS uniset2-httpresolver
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
      COMPONENT uniset2-httpresolver
    )
endif()
