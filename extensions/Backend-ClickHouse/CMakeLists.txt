if(UNISET2_BUILD_CLICKHOUSE)
  message("Build Clickhouse")
  #---------------------------------------------------------------------------------------
  include(FetchContent)
  FetchContent_Declare(clickhouse-cpp
    GIT_REPOSITORY https://github.com/ClickHouse/clickhouse-cpp.git  
    GIT_TAG        v2.5.1                                 
    )
  FetchContent_MakeAvailable(clickhouse-cpp)
  #---------------------------------------------------------------------------------------
  # TODO: setup static or shared
  add_library(UniSet2BackendClickHouse SHARED
    BackendClickHouse.cc 
    ClickHouseInterface.cc 
    ClickHouseTagsConfig.cc
    )
  set_target_properties(UniSet2BackendClickHouse PROPERTIES
    VERSION ${CMAKE_PROJECT_VERSION}
    SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
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

  # Add installation
  #---------------------------------------------------------------------------------------
  include(CPack)
  cpack_add_component(uniset2-clickhouse
    DESCRIPTION "Backend for Clickhouse DB"
    )
  install(TARGETS UniSet2BackendClickHouse uniset2-backend-clickhouse uniset2-clickhouse-helper
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
      COMPONENT uniset2-clickhouse
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT uniset2-clickhouse
      ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT uniset2-clickhouse
    )
endif()
