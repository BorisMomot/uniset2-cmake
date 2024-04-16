# set(CMAKE_SHARED_LINKER_FLAGS "-shared,-Wl,-fPIC")
# TODO: now could build only with this flag
# bm@bm-dsa:~/pr/uniset/uniset2_cmake/build$ cmake -DCMAKE_POSITION_INDEPENDENT_CODE=ON ..

# TODO: setup shared or static
add_library(uniset2 
  SHARED 
  ${uniset_sources}
  ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/UniSetBaseConstantsSK.cc
  ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/UniSetManager_iSK.cc
  ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/UniSetTypes_iSK.cc
  ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/UniSetObject_iSK.cc
  ${PROJECT_BINARY_DIR}/IDL/Processes/IOController_iSK.cc
  # ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/UniSetManager_i.hh
  # ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/UniSetBaseConstants.hh
  # ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/UniSetTypes_i.hh
  # ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/UniSetObject_i.hh
  # ${PROJECT_BINARY_DIR}/IDL/Processes/IOController_i.hh
#     # $<TARGET_OBJECTS:uniset_core>
#     # $<TARGET_OBJECTS:uniset_http>
#     # $<TARGET_OBJECTS:uniset_modbus>
#     # $<TARGET_OBJECTS:uniset_tcp>
#     # $<TARGET_OBJECTS:uniset_log>
#     # $<TARGET_OBJECTS:uniset_communications>
#     # $<TARGET_OBJECTS:uniset_obj_repo>
#     # $<TARGET_OBJECTS:uniset_processes>
#     # $<TARGET_OBJECTS:uniset_services>
#     # $<TARGET_OBJECTS:uniset_timers>
#     # $<TARGET_OBJECTS:uniset_various>
  )
target_include_directories(uniset2 
  PUBLIC
    ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/
    ${PROJECT_BINARY_DIR}/IDL/Processes/
    ${PROJECT_SOURCE_DIR}/include
    ${SIGC_INCLUDE_DIRS}
    ${EV_INCLUDE_DIRS}
    ${EV_CORE_INCLUDE_DIRS}
    ${EV_PTHREADS_INCLUDE_DIRS}
    ${OMNI_INCLUDE_DIRS}
    )
target_link_libraries(uniset2
  PUBLIC
    ${SIGC_LIBRARIES}
    ${EV_LIBRARIES}
    ${EV_CORE_LIBRARIES}
    ${EV_PTHREADS_LIBRARIES}
    ${OMNI_LIBRARIES}
    ev
    # omniORB4
    # omnithread
    Poco::Net
    Poco::JSON
    LibXml2::LibXml2
    city_hash102
    murmurhash
    )


add_executable(uniset_test_bin 
  main.cpp
  )
# target_include_directories(uniset_test_bin 
#   PUBLIC 
#     ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/
#     ${PROJECT_BINARY_DIR}/IDL/Processes/
#     ${SIGC_INCLUDE_DIRS}
#     ${PROJECT_SOURCE_DIR}/include
#     )
target_link_libraries(uniset_test_bin 
    uniset2
    # ${SIGC_LIBRARIES}
    # ${EV_LIBRARIES}
    # Poco::Net
    # LibXml2::LibXml2
    # omniORB4
    # omnithread
    # city_hash102
    # murmurhash
  )
