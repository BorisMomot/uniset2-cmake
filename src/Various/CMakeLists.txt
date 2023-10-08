set(uniset_various_sources 
  UniXML.cc 
  MQMutex.cc 
  MQAtomic.cc 
	Mutex.cc 
	SViewer.cc 
	SMonitor.cc 
	WDTInterface.cc 
	VMonitor.cc 
	ujson.cc
  )

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${uniset_various_sources})

add_library(uniset_various OBJECT ${uniset_various_sources})
target_include_directories(uniset_various 
  PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}/IDL/UniSetTypes
    ${PROJECT_BINARY_DIR}/IDL/Processes
    ${SIGC_INCLUDE_DIRS}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CPP_UNISET_TYPES_DIR}
  )
target_link_libraries(uniset_various 
  poco 
  LibXml2::LibXml2
  ${SIGC_LIBRARIES}
  )
####
# noinst_LTLIBRARIES = libVarious.la
# libVarious_la_CPPFLAGS 	= $(SIGC_CFLAGS) $(POCO_CFLAGS)
# libVarious_la_LIBADD 	= $(SIGC_LIBS) $(POCO_LIBS)
# libVarious_la_SOURCES 	= UniXML.cc MQMutex.cc MQAtomic.cc \
# 	Mutex.cc SViewer.cc SMonitor.cc WDTInterface.cc VMonitor.cc \
# 	ujson.cc
