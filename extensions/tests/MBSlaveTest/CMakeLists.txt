add_custom_command(OUTPUT TestProc_SK.cc
  COMMAND ${PROJECT_BINARY_DIR}/Utilities/codegen/uniset2-codegen -l ${PROJECT_SOURCE_DIR}/Utilities/codegen --ask -n TestProc --local-include --topdir ${PROJECT_SOURCE_DIR}/ --no-main ${CMAKE_CURRENT_SOURCE_DIR}/testproc.src.xml
  DEPENDS testproc.src.xml
  )

add_executable(mbslave-test 
  TestProc_SK.cc 
  TestProc.cc 
  mbslave-test.cc
  )
target_include_directories(mbslave-test PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(mbslave-test 
  uniset2
  UnisetSharedMemory
  )
