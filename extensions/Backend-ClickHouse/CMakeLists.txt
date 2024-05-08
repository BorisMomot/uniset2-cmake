# TODO add option to disable build
include(FetchContent)
FetchContent_Declare(clickhouse-cpp
  GIT_REPOSITORY https://github.com/ClickHouse/clickhouse-cpp.git  
  GIT_TAG        v2.5.1                                 
  )
FetchContent_MakeAvailable(clickhouse-cpp)
#---------------------------------------------------------------------------------------
add_library(UniSet2BackendClickHouse
  BackendClickHouse.cc 
  ClickHouseInterface.cc 
  ClickHouseTagsConfig.cc
  )
target_compile_features(UniSet2BackendClickHouse PUBLIC cxx_std_17)
target_link_libraries(UniSet2BackendClickHouse
  uniset2
  uniset2extensions 
  UnisetSharedMemory
  clickhouse-cpp-lib
  )
add_executable(uniset2-backend-clickhouse main.cc)
target_link_libraries(uniset2-backend-clickhouse UniSet2BackendClickHouse)
add_executable(uniset2-clickhouse-helper helper.cc)
target_link_libraries(uniset2-clickhouse-helper UniSet2BackendClickHouse)
add_executable(clickhouse-test test.cc)
target_link_libraries(clickhouse-test UniSet2BackendClickHouse)
