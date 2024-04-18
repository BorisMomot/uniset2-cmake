add_executable(uniset2-mbrtutest mbrtutester.cc)
target_link_libraries(uniset2-mbrtutest uniset2)

# TODO verify binary names
add_executable(uniset2-mbrtuslave-echo mbtcptester.cc)
target_link_libraries(uniset2-mbrtuslave-echo uniset2)

add_executable(uniset2-mbtcpserver-echo MBSlave.cc mbrtuslave.cc)
target_link_libraries(uniset2-mbtcpserver-echo uniset2)

add_executable(uniset2-mbtcptest MBTCPServer.cc mbtcpserver.cc)
target_link_libraries(uniset2-mbtcptest uniset2)

# Test program to check connection
add_executable(mbtcp-test-connection mbtcpconnection.cc)
target_link_libraries(mbtcp-test-connection uniset2)
