# TODO build only if ENABLE_IO is activated
# TODO add tests directory
set(uniset_io_source ComediInterface.cc IOControl.cc)
# TODO: setup static or shared
add_library(UniSet2IOControl SHARED ${uniset_io_source})
set_target_properties(UniSet2IOControl PROPERTIES
  VERSION ${CMAKE_PROJECT_VERSION}
  SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
  )
target_include_directories(UniSet2IOControl
  PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${SIGC_INCLUDE_DIRS}
    ${COMEDI_INCLUDE_DIRS}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CPP_UNISET_TYPES_DIR}
  )
target_link_libraries(UniSet2IOControl
  uniset2extensions
  uniset2
  UnisetSharedMemory
  ${SIGC_LIBRARIES}
  ${COMEDI_LIBRARIES}
  )

# add binaries
add_executable(iocontrol iocontrol.cc)
target_link_libraries(iocontrol 
  uniset2
  uniset2extensions
  UnisetSharedMemory
  UniSet2IOControl
  )

add_executable(iotest iotest.cc)
target_link_libraries(iotest 
  uniset2
  uniset2extensions
  UnisetSharedMemory
  UniSet2IOControl
  )

add_executable(iocalibr iocalibr.cc)
target_link_libraries(iocalibr 
  uniset2
  uniset2extensions
  UnisetSharedMemory
  UniSet2IOControl
  )
