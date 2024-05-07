execute_process(
  COMMAND ${PROJECT_BINARY_DIR}/Utilities/codegen/uniset2-codegen -l ${PROJECT_SOURCE_DIR}/Utilities/codegen --ask -n TestProc --local-include --topdir ${PROJECT_SOURCE_DIR}/ --no-main testproc.src.xml
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
# add dependency on file generation
add_custom_target(generate_mb_test_files DEPENDS TestProc_SK.cc)

add_executable(mbslave-test 
  TestProc_SK.cc 
  TestProc.cc 
  mbslave-test.cc
  )
target_link_libraries(mbslave-test 
  uniset2
  UnisetSharedMemory
  )
add_dependencies(mbslave-test generate_mb_test_files)
