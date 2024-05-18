# TODO build only if ENABLE_IO is activated
# TODO add tests directory
set(mbmaster_source 
  MBExchange.cc 
  MBConfig.cc 
  RTUStorage.cc
  )
# TODO setup shared or static
add_library(MBMaster SHARED ${mbmaster_source})
set_target_properties(MBMaster PROPERTIES
  VERSION ${CMAKE_PROJECT_VERSION}
  SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
  )
target_include_directories(MBMaster
  PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${SIGC_INCLUDE_DIRS}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CPP_UNISET_TYPES_DIR}
  )
target_link_libraries(MBMaster
  uniset2
  uniset2extensions
  UnisetSharedMemory
  ${SIGC_LIBRARIES}
  )
# -------------------- Mobus TCP -------------------
set(mbtcpmaster_source 
  MBTCPMaster.cc 
  MBTCPMultiMaster.cc
  )
# TODO setup static or shared
add_library(UniSet2MBTCPMaster SHARED ${mbtcpmaster_source})
set_target_properties(UniSet2MBTCPMaster PROPERTIES
  VERSION ${CMAKE_PROJECT_VERSION}
  SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
  )
set_target_properties(UniSet2MBTCPMaster PROPERTIES
  VERSION ${CMAKE_PROJECT_VERSION}
  SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
  )
target_link_libraries(UniSet2MBTCPMaster
  uniset2
  uniset2extensions
  UnisetSharedMemory
  ${SIGC_LIBRARIES}
  MBMaster
  )

add_executable(uniset2_mbtcpmaster main.cc)
target_link_libraries(uniset2_mbtcpmaster 
  uniset2
  uniset2extensions
  UnisetSharedMemory
  UniSet2MBTCPMaster
  )

add_executable(uniset2_mbtcpmultimaster multi-main.cc)
target_link_libraries(uniset2_mbtcpmultimaster 
  uniset2
  uniset2extensions
  UnisetSharedMemory
  UniSet2MBTCPMaster
  )
# -------------------- Mobus RTU -------------------
# TODO setup static or shared
add_library(UniSet2RTU SHARED RTUExchange.cc)
set_target_properties(UniSet2RTU PROPERTIES
  VERSION ${CMAKE_PROJECT_VERSION}
  SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
  )
target_link_libraries(UniSet2RTU
  uniset2
  uniset2extensions
  UnisetSharedMemory
  ${SIGC_LIBRARIES}
  MBMaster
  )

add_executable(uniset2_rtuexchange rtuexchange.cc)
target_link_libraries(uniset2_rtuexchange UniSet2RTU)
add_executable(uniset2_mtr-conv mtr-conv.cc)
target_link_libraries(uniset2_mtr-conv UniSet2RTU)
add_executable(uniset2_mtr-setup mtr-setup.cc)
target_link_libraries(uniset2_mtr-setup UniSet2RTU)
add_executable(uniset2_mtr-read mtr-read.cc)
target_link_libraries(uniset2_mtr-read UniSet2RTU)
add_executable(uniset2_vtconv vtconv.cc)
target_link_libraries(uniset2_vtconv UniSet2RTU)
add_executable(uniset2_rtustate rtustate.cc)
target_link_libraries(uniset2_rtustate UniSet2RTU)
