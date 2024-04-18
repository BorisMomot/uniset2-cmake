add_executable(uniset2-log log.cc)
target_link_libraries(uniset2-log uniset2)

add_executable(uniset2-logserver-wrap log-wrap.cc)
target_link_libraries(uniset2-logserver-wrap uniset2)

add_executable(uniset2-log2val log2val.cc)
target_link_libraries(uniset2-log2val uniset2)

add_executable(uniset2-test-logserver logserver.cc)
target_link_libraries(uniset2-test-logserver uniset2)

add_executable(uniset2-log-stdin log-stdin.cc)
target_link_libraries(uniset2-log-stdin uniset2)
