execute_process(
  COMMAND ${PROJECT_BINARY_DIR}/Utilities/codegen/uniset2-codegen -l ${PROJECT_SOURCE_DIR}/Utilities/codegen --ask -n TestProc --local-include --topdir ${PROJECT_SOURCE_DIR}/ --no-main testproc.src.xml
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
add_custom_target(generate_testfiles DEPENDS TestProc_SK.cc)

add_executable(smemory-test 
  TestProc_SK.cc 
  TestProc.cc 
  smemory-test.cc
  )
target_link_libraries(smemory-test
  uniset2
  UnisetSharedMemory
  )
add_dependencies(smemory-test generate_testfiles)

#-------------------------------------------------------------------------------------------------------------
execute_process(
  COMMAND ${PROJECT_BINARY_DIR}/Utilities/codegen/uniset2-codegen -l ${PROJECT_SOURCE_DIR}/Utilities/codegen --ask -n LostTestProc --local-include --topdir ${PROJECT_SOURCE_DIR}/ --no-main losttestproc.src.xml
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
# add dependency on file generation
add_custom_target(generate_losttest_files DEPENDS LostTestProc_SK.cc)

add_executable(sm-lostmessage-test 
  LostTestProc_SK.cc 
  LostTestProc.cc 
  LostPassiveTestProc.cc 
  sm-lostmessage-test.cc
  )

target_link_libraries(sm-lostmessage-test 
  uniset2
  UnisetSharedMemory
  )
add_dependencies(sm-lostmessage-test generate_mq_test_files)
