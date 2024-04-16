set(uniset_core_sources 
  ${CMAKE_CURRENT_SOURCE_DIR}/UniSetTypes.cc 
	${CMAKE_CURRENT_SOURCE_DIR}/UniSetObject.cc 
	${CMAKE_CURRENT_SOURCE_DIR}/UniSetManager.cc 
	${CMAKE_CURRENT_SOURCE_DIR}/UniSetActivator.cc 
	${CMAKE_CURRENT_SOURCE_DIR}/Configuration.cc 
	${CMAKE_CURRENT_SOURCE_DIR}/MessageType.cc 
	${CMAKE_CURRENT_SOURCE_DIR}/UInterface.cc
	PARENT_SCOPE
  )
#-------------------------------------------------------------------------------
# include(CMakePackageConfigHelpers)
#
# set(uniset_core_headers 
#   ${PROJECT_SOURCE_DIR}/include
#   )
#
# set(uniset_core_sources 
#   UniSetTypes.cc 
# 	UniSetObject.cc 
# 	UniSetManager.cc 
# 	UniSetActivator.cc 
# 	Configuration.cc 
# 	MessageType.cc 
# 	UInterface.cc
#   )
#
# source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${uniset_core_headers})
#
# add_library(uniset_core OBJECT ${uniset_core_sources})
#
# target_include_directories(uniset_core 
#   PUBLIC 
#     ${PROJECT_SOURCE_DIR}/include
#     ${PROJECT_BINARY_DIR}/IDL/Processes
#     ${SIGC_INCLUDE_DIRS}
#   PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/src
#   )
#
# target_link_libraries(uniset_core 
#   PUBLIC
#     uniset_types
#     LibXml2::LibXml2
#     city_hash102
#     murmurhash
#   )
#
