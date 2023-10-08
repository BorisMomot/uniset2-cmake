set(uniset_tcp_sources 
  UTCPCore.cc 
  UTCPStream.cc 
  USocket.cc 
  UTCPSocket.cc 
  TCPCheck.cc
  )

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${uniset_tcp_sources})

add_library(uniset_tcp OBJECT ${uniset_tcp_sources})
target_include_directories(uniset_tcp
  PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/IDL/UniSetTypes
    ${PROJECT_BINARY_DIR}/IDL/Processes
    ${SIGC_INCLUDE_DIRS}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
  )
target_link_libraries(uniset_tcp 
  poco 
  LibXml2::LibXml2
  ${SIGC_LIBRARIES}
  )
