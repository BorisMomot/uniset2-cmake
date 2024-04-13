# include(CMakePackageConfigHelpers)
set(test_main_SRC 
  # ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/UniSetBaseConstants.hh
  # ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/UniSetBaseConstantsSK.cc
  # ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/UniSetTypes_i.hh 
  # ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/UniSetTypes_iSK.cc 
 #  ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/UniSetObject_i.hh 
 #  ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/UniSetObject_iSK.cc 
	# ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/UniSetManager_i.hh 
	# ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/UniSetManager_iSK.cc 
	# ${PROJECT_BINARY_DIR}/IDL/Processes/IOController_i.hh
	# ${PROJECT_BINARY_DIR}/IDL/Processes/IOController_iSK.cc
  main.cpp
  )

add_executable(main ${test_main_SRC})

target_include_directories(main
  PUBLIC 
    # ${PROJECT_SOURCE_DIR}/include
    # ${PROJECT_BINARY_DIR}/IDL/UniSetTypes
    # ${PROJECT_BINARY_DIR}/IDL/Processes
    # ${CPP_UNISET_TYPES_DIR}
  )
target_link_libraries(main PUBLIC
  omniORB4
  omnithread
  uniset_types
  # Threads::Threads
  # ${SIGC_LIBRARIES}
  )
