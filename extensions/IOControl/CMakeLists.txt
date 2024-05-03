# TODO build only if ENABLE_IO is activated
set(uniset_io_source ComediInterface.cc IOControl.cc)
add_library(UniSet2IOControl ${uniset_io_source})
target_include_directories(UniSet2IOControl
  PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    # ${PROJECT_BINARY_DIR}/IDL/UniSetTypes
    # ${PROJECT_BINARY_DIR}/IDL/Processes
    ${SIGC_INCLUDE_DIRS}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CPP_UNISET_TYPES_DIR}
  )
target_link_libraries(UniSet2IOControl
  uniset2extensions
  uniset2
  UnisetSharedMemory
  ${SIGC_LIBRARIES}
  )

# add binaries
# set(smemory_source smemory.cc)
# add_executable(uniset2-smemory ${smemory_source})
# target_link_libraries(uniset2-smemory 
#   UniSet2IOControl
#   )


