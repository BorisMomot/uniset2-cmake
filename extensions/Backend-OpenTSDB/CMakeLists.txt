# TODO add option to disable build

add_library(UniSet2BackendOpenTSDB BackendOpenTSDB.cc)
target_link_libraries(UniSet2BackendOpenTSDB
  uniset2
  uniset2extensions 
  UnisetSharedMemory
  )

add_executable(uniset2-backend-opentsdb main.cc)
target_link_libraries(uniset2-backend-opentsdb UniSet2BackendOpenTSDB)
