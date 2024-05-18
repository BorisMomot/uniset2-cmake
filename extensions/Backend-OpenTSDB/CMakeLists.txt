# TODO add option to disable build

# TODO setup static or shared
add_library(UniSet2BackendOpenTSDB SHARED BackendOpenTSDB.cc)
set_target_properties(UniSet2BackendOpenTSDB PROPERTIES
  VERSION ${CMAKE_PROJECT_VERSION}
  SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
  )
target_link_libraries(UniSet2BackendOpenTSDB
  uniset2
  uniset2extensions 
  UnisetSharedMemory
  )

add_executable(uniset2-backend-opentsdb main.cc)
target_link_libraries(uniset2-backend-opentsdb UniSet2BackendOpenTSDB)
