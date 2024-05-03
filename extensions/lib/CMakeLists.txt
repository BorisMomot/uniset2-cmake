include(CMakePackageConfigHelpers)

set(uniset2extensions_sources 
  Extensions.cc 
  SMInterface.cc 
  Calibration.cc  
  IOBase.cc 
  DigitalFilter.cc 
  PID.cc 
  MTR.cc 
  VTypes.cc 
  # TODO: make it generatable
  UObject_SK.cc
  )

# source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${uniset2extensions_sources})

add_library(uniset2extensions  ${uniset2extensions_sources})
target_include_directories(uniset2extensions 
  PUBLIC 
    ${PROJECT_SOURCE_DIR}/extensions/include
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/IDL/UniSetTypes
    ${PROJECT_BINARY_DIR}/IDL/Processes
    ${SIGC_INCLUDE_DIRS}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CPP_UNISET_TYPES_DIR}
  )
target_link_libraries(uniset2extensions 
  PUBLIC
  uniset2
  LibXml2::LibXml2
  ${SIGC_LIBRARIES}
  )
