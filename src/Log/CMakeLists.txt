set(uniset_log_sources 
  ${CMAKE_CURRENT_SOURCE_DIR}/DebugStream.cc 
  ${CMAKE_CURRENT_SOURCE_DIR}/Debug.cc 
  ${CMAKE_CURRENT_SOURCE_DIR}/LogServerTypes.cc 
  ${CMAKE_CURRENT_SOURCE_DIR}/LogServer.cc 
  ${CMAKE_CURRENT_SOURCE_DIR}/LogSession.cc 
  ${CMAKE_CURRENT_SOURCE_DIR}/LogReader.cc 
  ${CMAKE_CURRENT_SOURCE_DIR}/LogAgregator.cc
  PARENT_SCOPE
  )
#-------------------------------------------------------------
# set(uniset_log_sources 
#   DebugStream.cc 
#   Debug.cc 
#   LogServerTypes.cc 
#   LogServer.cc 
#   LogSession.cc 
#   LogReader.cc 
#   LogAgregator.cc
#   )
#
# source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${uniset_log_sources})
#
# add_library(uniset_log OBJECT ${uniset_log_sources})
# target_include_directories(uniset_log 
#   PUBLIC 
#     ${PROJECT_SOURCE_DIR}/include
#     ${PROJECT_BINARY_DIR}/IDL/UniSetTypes
#     ${PROJECT_BINARY_DIR}/IDL/Processes
#     ${SIGC_INCLUDE_DIRS}
#   PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}
#     ${CPP_UNISET_TYPES_DIR}
#   )
# target_link_libraries(uniset_log 
#   poco 
#   LibXml2::LibXml2
#   ${SIGC_LIBRARIES}
#   # city_hash102
#   # murmurhash
#   )
# #####################################################################
# # noinst_LTLIBRARIES = libLog.la
# # libLog_la_CPPFLAGS = $(SIGC_CFLAGS) $(POCO_CFLAGS)
# # libLog_la_LIBADD 	=  $(SIGC_LIBS) $(POCO_LIBS)
# # libLog_la_SOURCES = DebugStream.cc Debug.cc LogServerTypes.cc LogServer.cc LogSession.cc LogReader.cc LogAgregator.cc
