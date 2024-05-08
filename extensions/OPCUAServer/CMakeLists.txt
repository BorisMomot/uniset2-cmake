# TODO add option to disable build
include(FetchContent)
FetchContent_Declare(open62541pp
  GIT_REPOSITORY https://github.com/open62541pp/open62541pp.git  
  GIT_TAG        v0.13.0
  )
FetchContent_MakeAvailable(open62541pp)
#---------------------------------------------------------------------------------------
add_library(UniSet2OPCUAServer OPCUAServer.cc)
target_compile_features(UniSet2OPCUAServer PUBLIC cxx_std_17)
target_link_libraries(UniSet2OPCUAServer
  uniset2
  uniset2extensions 
  UnisetSharedMemory
  open62541pp::open62541pp
  )
add_executable(uniset2-opcua-server main.cc)
target_link_libraries(uniset2-opcua-server UniSet2OPCUAServer)
