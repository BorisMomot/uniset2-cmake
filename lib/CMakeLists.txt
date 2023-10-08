set(CMAKE_SHARED_LINKER_FLAGS "-Wl,-fPIC")
# TODO: now could build only with this flag
# bm@bm-dsa:~/pr/uniset/uniset2_cmake/build$ cmake -DCMAKE_POSITION_INDEPENDENT_CODE=ON ..

# TODO: setup shared or static
add_library(uniset2 
  SHARED 
    $<TARGET_OBJECTS:uniset_core>
    $<TARGET_OBJECTS:uniset_http>
    $<TARGET_OBJECTS:uniset_modbus>
    $<TARGET_OBJECTS:uniset_tcp>
    $<TARGET_OBJECTS:uniset_log>
    $<TARGET_OBJECTS:uniset_communications>
    $<TARGET_OBJECTS:uniset_obj_repo>
    $<TARGET_OBJECTS:uniset_processes>
    $<TARGET_OBJECTS:uniset_services>
    $<TARGET_OBJECTS:uniset_timers>
    $<TARGET_OBJECTS:uniset_various>
    
  )
