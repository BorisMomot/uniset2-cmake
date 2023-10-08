set(uniset_services_sources 
  DBServer.cc 
  DBInterface.cc
  )

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${uniset_services_sources})

add_library(uniset_services OBJECT ${uniset_services_sources})
target_include_directories(uniset_services 
  PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/IDL/UniSetTypes
    ${PROJECT_BINARY_DIR}/IDL/Processes
    ${SIGC_INCLUDE_DIRS}
    # ${EV_INCLUDE_DIRS}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CPP_UNISET_TYPES_DIR}
  )
target_link_libraries(uniset_services 
  # poco 
  LibXml2::LibXml2
  ${SIGC_LIBRARIES}
  # ${EV_LIBRARIES}
  )


# noinst_LTLIBRARIES 		= libServices.la
# libServices_la_CPPFLAGS	= $(SIGC_CFLAGS)
# libServices_la_LIBADD 	= $(SIGC_LIBS)
# libServices_la_SOURCES 	= DBServer.cc DBInterface.cc
