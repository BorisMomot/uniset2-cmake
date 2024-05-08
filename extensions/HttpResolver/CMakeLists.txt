# TODO build only if ENABLE_RESTAPI
add_executable(uniset2-httpresolver 
  HttpResolver.cc
  main.cc
  ) 
target_link_libraries(uniset2-httpresolver uniset2)
