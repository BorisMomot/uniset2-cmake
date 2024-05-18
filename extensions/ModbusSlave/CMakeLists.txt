# TODO add tests directory
# TODO setup shared or static
add_library(UniSet2MBSlave SHARED MBSlave.cc)
set_target_properties(UniSet2MBSlave PROPERTIES
  VERSION ${CMAKE_PROJECT_VERSION}
  SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
  )
target_include_directories(UniSet2MBSlave
  PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${SIGC_INCLUDE_DIRS}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CPP_UNISET_TYPES_DIR}
  )
target_link_libraries(UniSet2MBSlave
  uniset2
  uniset2extensions
  UnisetSharedMemory
  ${SIGC_LIBRARIES}
  )
# Add executable
add_executable(uniset2_mbslave mbslave.cc)
target_link_libraries(uniset2_mbslave UniSet2MBSlave)
