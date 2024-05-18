# TODO add option to disable build
include(FetchContent)
FetchContent_Declare(open62541pp
  GIT_REPOSITORY https://github.com/open62541pp/open62541pp.git  
  GIT_TAG        v0.7.0
  )
FetchContent_MakeAvailable(open62541pp)
#---------------------------------------------------------------------------------------
# TODO setup static or shared
add_library(UniSet2OPCUAServer SHARED OPCUAServer.cc)
set_target_properties(UniSet2OPCUAServer PROPERTIES
  VERSION ${CMAKE_PROJECT_VERSION}
  SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
  )
target_compile_features(UniSet2OPCUAServer PUBLIC cxx_std_17)
target_link_libraries(UniSet2OPCUAServer
  uniset2
  uniset2extensions 
  UnisetSharedMemory
  open62541pp::open62541pp
  )
add_executable(uniset2-opcua-server main.cc)
target_link_libraries(uniset2-opcua-server UniSet2OPCUAServer)
