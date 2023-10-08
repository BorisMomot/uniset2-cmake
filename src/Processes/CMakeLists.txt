set(uniset_processes_sources 
  IOController.cc 
  IONotifyController.cc 
	IOConfig_XML.cc 
	EventLoopServer.cc 
	CommonEventLoop.cc 
	ProxyManager.cc 
	PassiveObject.cc 
	RunLock.cc
  # ${PROJECT_BINARY_DIR}/IDL/Processes/IOController_i.hh 
  # ${PROJECT_BINARY_DIR}/IDL/Processes/IOController_iSK.cc 
  )

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${uniset_processes_sources})

add_library(uniset_processes OBJECT ${uniset_processes_sources})
target_include_directories(uniset_processes 
  PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/IDL/UniSetTypes
    ${PROJECT_BINARY_DIR}/IDL/Processes
    ${SIGC_INCLUDE_DIRS}
    ${EV_INCLUDE_DIRS}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CPP_UNISET_TYPES_DIR}
  )
target_link_libraries(uniset_processes 
  # poco 
  LibXml2::LibXml2
  ${SIGC_LIBRARIES}
  ${EV_LIBRARIES}
  )
##########################
