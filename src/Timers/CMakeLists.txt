set(uniset_timers_sources 
  ${CMAKE_CURRENT_SOURCE_DIR}/PassiveTimer.cc 
  ${CMAKE_CURRENT_SOURCE_DIR}/PassiveCondTimer.cc 
  ${CMAKE_CURRENT_SOURCE_DIR}/LT_Object.cc
  PARENT_SCOPE
  )
#-----------------------------------------------------
# set(uniset_timers_sources 
#   PassiveTimer.cc 
#   PassiveCondTimer.cc 
#   LT_Object.cc
#   )
#
# source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${uniset_timers_sources})
#
# add_library(uniset_timers OBJECT ${uniset_timers_sources})
# target_include_directories(uniset_timers 
#   PUBLIC 
#     ${PROJECT_SOURCE_DIR}/include
#     ${PROJECT_BINARY_DIR}/IDL/UniSetTypes
#     ${PROJECT_BINARY_DIR}/IDL/Processes
#     ${SIGC_INCLUDE_DIRS}
#   PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}
#     # ${CPP_UNISET_TYPES_DIR}
#   )
# target_link_libraries(uniset_timers 
#   # poco 
#   LibXml2::LibXml2
#   ${SIGC_LIBRARIES}
#   )
#
# #######
# # libTimers_la_SOURCES=PassiveTimer.cc PassiveCondTimer.cc LT_Object.cc
