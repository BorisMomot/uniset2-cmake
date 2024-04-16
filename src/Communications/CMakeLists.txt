add_subdirectory(Http)
add_subdirectory(Modbus)
add_subdirectory(TCP)

set(uniset_communications_sources
  ${uniset_http_source}
  ${uniset_modbus_sources}
  ${uniset_tcp_sources}
  ${CMAKE_CURRENT_SOURCE_DIR}/ComPort.cc 
  ${CMAKE_CURRENT_SOURCE_DIR}/ComPort485F.cc
  PARENT_SCOPE
  )

#-----------------------------------------------------------------
# set(uniset_communications_sources
#   ComPort.cc 
#   ComPort485F.cc
#   )
#
# source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${uniset_communications_sources})
#
# add_library(uniset_communications OBJECT ${uniset_communications_sources})
# target_include_directories(uniset_communications 
#   PUBLIC 
#     ${PROJECT_SOURCE_DIR}/include
#   PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}
#     ${CPP_UNISET_TYPES_DIR}
#   )
# target_link_libraries(uniset_communications 
#   poco 
#   )
