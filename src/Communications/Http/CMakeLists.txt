set(uniset_http_source 
  UHttpRequestHandler.cc 
  UHttpServer.cc 
  UHttpClient.cc
  )

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${uniset_http_source})

add_library(uniset_http OBJECT ${uniset_http_source})
target_include_directories(uniset_http
  PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${SIGC_INCLUDE_DIRS}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
  )
target_link_libraries(uniset_http 
  poco 
  ${SIGC_LIBRARIES}
  )
