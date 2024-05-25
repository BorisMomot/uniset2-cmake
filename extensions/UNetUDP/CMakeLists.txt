set(uniset_unetudp_source 
  UDPPacket.cc 
  UDPTransport.cc 
  MulticastTransport.cc 
  UNetReceiver.cc 
  UNetSender.cc 
  UNetExchange.cc
  )
# TODO setup shared or static
add_library(UniSet2UNetUDP SHARED ${uniset_unetudp_source})
set_target_properties(UniSet2UNetUDP PROPERTIES
  VERSION ${CMAKE_PROJECT_VERSION}
  SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
  )
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

# Add installation
#---------------------------------------------------------------------------------------
install(TARGETS UniSet2UNetUDP uniset2-unetexchange uniset2-unet-udp-tester uniset2-unet-multicast-tester 
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
      COMPONENT uniset2-extensions-common
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT uniset2-extensions-common
      ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT uniset2-extensions-common
    )
endif()
