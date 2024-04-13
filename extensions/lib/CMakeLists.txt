include(CMakePackageConfigHelpers)

set(uniset2extensions_sources 
  Extensions.cc 
  SMInterface.cc 
  Calibration.cc  
  IOBase.cc 
  DigitalFilter.cc 
  PID.cc 
  MTR.cc 
  VTypes.cc 
  # TODO: make it generatable
  UObject_SK.cc
  )


source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${uniset2extensions_sources})

add_library(uniset2extensions  ${uniset2extensions_sources})
target_include_directories(uniset2extensions 
  PUBLIC 
    ${PROJECT_SOURCE_DIR}/extensions/include
    # ${PROJECT_BINARY_DIR}/IDL/Processes
    ${SIGC_INCLUDE_DIRS}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CPP_UNISET_TYPES_DIR}
  )
target_link_libraries(uniset2extensions 
  PUBLIC
  uniset_core
  LibXml2::LibXml2
  ${SIGC_LIBRARIES}
  # city_hash102
  # murmurhash
  )
    
############################################################################
##############################################################################
#
# UEXT_VER=@LIBVER@
#
# lib_LTLIBRARIES 			= libUniSet2Extensions.la
# libUniSet2Extensions_la_LDFLAGS  = -version-info $(UEXT_VER)
# libUniSet2Extensions_la_CPPFLAGS = $(SIGC_CFLAGS) $(POCO_CFLAGS) -I$(top_builddir)/extensions/include
# libUniSet2Extensions_la_LIBADD   = $(SIGC_LIBS) $(POCO_LIBS) $(top_builddir)/lib/libUniSet2.la
# libUniSet2Extensions_la_SOURCES  = Extensions.cc SMInterface.cc Calibration.cc  IOBase.cc DigitalFilter.cc PID.cc MTR.cc VTypes.cc UObject_SK.cc
#
# UObject_SK.cc: $(top_builddir)/Utilities/codegen/*.xsl
# 	$(SHEL) $(top_builddir)/Utilities/codegen/uniset2-codegen -l $(top_builddir)/Utilities/codegen -n UObject --no-main $(top_builddir)/Utilities/codegen/tests/uobject.src.xml
# 	mv -f UObject_SK.h ../include/
