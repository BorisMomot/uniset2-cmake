set(uniset_unetudp_source 
  UDPPacket.cc 
  UDPTransport.cc 
  MulticastTransport.cc 
  UNetReceiver.cc 
  UNetSender.cc 
  UNetExchange.cc
  )
add_library(UniSet2UNetUDP ${uniset_unetudp_source})
target_link_libraries(UniSet2UNetUDP
  uniset2extensions
  UnisetSharedMemory
  )
# Add executable
add_executable(uniset2-unetexchange unetexchange.cc)
target_link_libraries(uniset2-unetexchange UniSet2UNetUDP)

add_executable(uniset2-unet-udp-tester UDPPacket.cc unet-udp-tester.cc)
target_link_libraries(uniset2-unet-udp-tester UniSet2UNetUDP)

add_executable(uniset2-unet-multicast-tester UDPPacket.cc MulticastTransport.cc unet-multicast-tester.cc)
target_link_libraries(uniset2-unet-multicast-tester UniSet2UNetUDP)
