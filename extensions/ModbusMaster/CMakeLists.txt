# TODO build only if ENABLE_IO is activated
# TODO add tests directory
set(mbmaster_source 
  MBExchange.cc 
  MBConfig.cc 
  RTUStorage.cc
  )
add_library(MBMaster ${mbmaster_source})
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
add_library(UniSet2MBTCPMaster ${mbtcpmaster_source})
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
add_library(UniSet2RTU RTUExchange.cc)
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
