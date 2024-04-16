set(uniset_obj_repo_sources 
  ${CMAKE_CURRENT_SOURCE_DIR}/ObjectIndex.cc 
  ${CMAKE_CURRENT_SOURCE_DIR}/ObjectIndex_Array.cc 
  ${CMAKE_CURRENT_SOURCE_DIR}/ObjectIndex_XML.cc 
  ${CMAKE_CURRENT_SOURCE_DIR}/ObjectIndex_idXML.cc 
	${CMAKE_CURRENT_SOURCE_DIR}/ORepHelpers.cc  
	${CMAKE_CURRENT_SOURCE_DIR}/ObjectRepository.cc 
	${CMAKE_CURRENT_SOURCE_DIR}/IORFile.cc 
	${CMAKE_CURRENT_SOURCE_DIR}/ObjectIndex_hashXML.cc
	PARENT_SCOPE
  )
#--------------------------------------------------------------------------------
# set(uniset_obj_repo_sources 
#   ObjectIndex.cc 
#   ObjectIndex_Array.cc 
#   ObjectIndex_XML.cc 
#   ObjectIndex_idXML.cc 
# 	ORepHelpers.cc  
# 	ObjectRepository.cc 
# 	IORFile.cc 
# 	ObjectIndex_hashXML.cc
#   )
#
# source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${uniset_obj_repo_sources})
#
# add_library(uniset_obj_repo OBJECT ${uniset_obj_repo_sources})
# target_include_directories(uniset_obj_repo 
#   PUBLIC 
#     ${PROJECT_SOURCE_DIR}/include
#     ${PROJECT_BINARY_DIR}/IDL/UniSetTypes
#     ${PROJECT_BINARY_DIR}/IDL/Processes
#     ${SIGC_INCLUDE_DIRS}
#   PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}
#     ${CPP_UNISET_TYPES_DIR}
#   )
# target_link_libraries(uniset_obj_repo 
#   poco 
#   LibXml2::LibXml2
#   ${SIGC_LIBRARIES}
#   )
#
# #######
# # noinst_LTLIBRARIES = libObjectsRepository.la
# # libObjectsRepository_la_SOURCES = ObjectIndex.cc ObjectIndex_Array.cc ObjectIndex_XML.cc ObjectIndex_idXML.cc \
# # 	ORepHelpers.cc  ObjectRepository.cc IORFile.cc ObjectIndex_hashXML.cc
