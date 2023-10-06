include(CMakePackageConfigHelpers)

set(uniset_core_headers 
  include/
  )

set(uniset_core_sources 
  ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/UniSetBaseConstants.hh
  ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/UniSetBaseConstantsSK.cc
  ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/UniSetTypes_i.hh 
  ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/UniSetTypes_iSK.cc 
  ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/UniSetObject_i.hh 
  ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/UniSetObject_iSK.cc 
	${PROJECT_BINARY_DIR}/IDL/UniSetTypes/UniSetManager_i.hh 
	${PROJECT_BINARY_DIR}/IDL/UniSetTypes/UniSetManager_iSK.cc 
	${PROJECT_BINARY_DIR}/IDL/Processes/IOController_i.hh
	${PROJECT_BINARY_DIR}/IDL/Processes/IOController_iSK.cc
  UniSetTypes.cc 
	UniSetObject.cc 
	UniSetManager.cc 
	UniSetActivator.cc 
	Configuration.cc 
	MessageType.cc 
	UInterface.cc
  )

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${mur_sources})

add_library(uniset_core ${uniset_core_sources})
target_include_directories(uniset_core 
  PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/IDL/UniSetTypes
    ${PROJECT_BINARY_DIR}/IDL/Processes
    ${SIGC_INCLUDE_DIRS}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CPP_UNISET_TYPES_DIR}
  )
target_link_libraries(uniset_core 
  poco 
  LibXml2::LibXml2
  ${SIGC_LIBRARIES}
  city_hash102
  murmurhash
  )

