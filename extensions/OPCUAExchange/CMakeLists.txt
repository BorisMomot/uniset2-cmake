# include(FetchContent)
# FetchContent_Declare(open62541pp
#   GIT_REPOSITORY https://github.com/open62541pp/open62541pp.git  
#   GIT_TAG        v0.7.0
#   )
# FetchContent_MakeAvailable(open62541pp)
#---------------------------------------------------------------------------------------
# TODO add option to disable build

add_library(UniSet2OPCUAExchange OPCUAExchange.cc OPCUAClient.cc)
target_compile_features(UniSet2OPCUAExchange PUBLIC cxx_std_17)
target_link_libraries(UniSet2OPCUAExchange
  uniset2
  uniset2extensions 
  UnisetSharedMemory
  open62541pp::open62541pp
  )
add_executable(uniset2-opcua-exchange main.cc)
target_link_libraries(uniset2-opcua-exchange UniSet2OPCUAExchange)
add_executable(uniset2-opcua-tester client.cc)
target_link_libraries(uniset2-opcua-tester UniSet2OPCUAExchange)
