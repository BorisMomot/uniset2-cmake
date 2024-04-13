set(CMAKE_SHARED_LINKER_FLAGS "-Wl,-fPIC")
# TODO: now could build only with this flag
# bm@bm-dsa:~/pr/uniset/uniset2_cmake/build$ cmake -DCMAKE_POSITION_INDEPENDENT_CODE=ON ..

# TODO: setup shared or static
add_library(uniset2 
  SHARED 
    $<TARGET_OBJECTS:uniset_core>
    # $<TARGET_OBJECTS:uniset_http>
    # $<TARGET_OBJECTS:uniset_modbus>
    # $<TARGET_OBJECTS:uniset_tcp>
    # $<TARGET_OBJECTS:uniset_log>
    # $<TARGET_OBJECTS:uniset_communications>
    # $<TARGET_OBJECTS:uniset_obj_repo>
    # $<TARGET_OBJECTS:uniset_processes>
    # $<TARGET_OBJECTS:uniset_services>
    # $<TARGET_OBJECTS:uniset_timers>
    # $<TARGET_OBJECTS:uniset_various>
  )

target_link_libraries(uniset2
  PUBLIC
    LibXml2::LibXml2
    omniORB4
    omnithread
    )


add_executable(uniset_test_bin main.cpp)
target_include_directories(uniset_test_bin 
  PUBLIC 
    ${PROJECT_BINARY_DIR}/IDL/UniSetTypes/
    ${PROJECT_BINARY_DIR}/IDL/Processes/
    ${SIGC_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(uniset_test_bin 
    uniset2
    ${SIGC_LIBRARIES}
  )
