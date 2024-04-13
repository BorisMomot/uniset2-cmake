set(uniset_sharedmemory_source SharedMemory.cc)
add_library(UnisetSharedMemory ${uniset_sharedmemory_source})
target_include_directories(UnisetSharedMemory
  PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    # ${PROJECT_BINARY_DIR}/IDL/UniSetTypes
    # ${PROJECT_BINARY_DIR}/IDL/Processes
    ${SIGC_INCLUDE_DIRS}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CPP_UNISET_TYPES_DIR}
  )
target_link_libraries(UnisetSharedMemory
  uniset2extensions
  uniset_core
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

