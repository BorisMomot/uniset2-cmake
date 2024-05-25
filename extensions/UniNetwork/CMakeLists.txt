# TODO setup static or shared
add_library(UniSet2Network SHARED UniExchange.cc)
set_target_properties(UniSet2Network PROPERTIES
  VERSION ${CMAKE_PROJECT_VERSION}
  SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
  )
target_link_libraries(UniSet2Network
  uniset2extensions
  UnisetSharedMemory
  )
# Add executable
add_executable(uniset2-network uninet.cc)
target_link_libraries(uniset2-network UniSet2Network)

# Add installation
#---------------------------------------------------------------------------------------
install(TARGETS UniSet2Network uniset2-network
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
      COMPONENT uniset2-extensions-common
      LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT uniset2-extensions-common
      ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT uniset2-extensions-common
    )
