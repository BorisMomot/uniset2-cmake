set(uniset_sharedmemory_source SharedMemory.cc)
# TODO setup static or shared
add_library(UnisetSharedMemory SHARED ${uniset_sharedmemory_source})
set_target_properties(UnisetSharedMemory PROPERTIES
  VERSION ${CMAKE_PROJECT_VERSION}
  SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
  )
target_include_directories(UnisetSharedMemory
  PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    # ${PROJECT_BINARY_DIR}/IDL/UniSetTypes
    # ${PROJECT_BINARY_DIR}/IDL/Processes
    ${SIGC_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE
    ${CPP_UNISET_TYPES_DIR}
  )
target_link_libraries(UnisetSharedMemory
  uniset2extensions
  uniset2
  # Poco 
  # LibXml2::LibXml2
  ${SIGC_LIBRARIES}
  # city_hash102
  # murmurhash
  )


set(smemory_source smemory.cc)
add_executable(uniset2-smemory ${smemory_source})
target_link_libraries(uniset2-smemory 
  UnisetSharedMemory
  # poco 
  )

