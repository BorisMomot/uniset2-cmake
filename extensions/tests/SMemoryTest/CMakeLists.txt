add_custom_command(OUTPUT TestProc_SK.cc
  COMMAND ${PROJECT_BINARY_DIR}/Utilities/codegen/uniset2-codegen -l ${PROJECT_SOURCE_DIR}/Utilities/codegen --ask -n TestProc --local-include --topdir ${PROJECT_SOURCE_DIR}/ --no-main ${CMAKE_CURRENT_SOURCE_DIR}/testproc.src.xml
  DEPENDS testproc.src.xml
  )

add_executable(smemory-test 
  TestProc_SK.cc 
  TestProc.cc 
  smemory-test.cc
  )
target_include_directories(smemory-test PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(smemory-test
  uniset2
  UnisetSharedMemory
  )

#-------------------------------------------------------------------------------------------------------------
add_custom_command(OUTPUT LostTestProc_SK.cc
  COMMAND ${PROJECT_BINARY_DIR}/Utilities/codegen/uniset2-codegen -l ${PROJECT_SOURCE_DIR}/Utilities/codegen --ask -n LostTestProc --local-include --topdir ${PROJECT_SOURCE_DIR}/ --no-main ${CMAKE_CURRENT_SOURCE_DIR}/losttestproc.src.xml
  DEPENDS losttestproc.src.xml
  )

add_executable(sm-lostmessage-test 
  LostTestProc_SK.cc 
  LostTestProc.cc 
  LostPassiveTestProc.cc 
  sm-lostmessage-test.cc
  )
target_include_directories(sm-lostmessage-test PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(sm-lostmessage-test 
  uniset2
  UnisetSharedMemory
  )
