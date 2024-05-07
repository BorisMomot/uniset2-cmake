# TODO maybe more elegant way exist
# This variables should be defined
set(prefix "")
set(exec_prefix "")
set(bindir ${CMAKE_INSTALL_BINDIR})
set(datarootdir ${CMAKE_INSTALL_DATAROOTDIR})
set(datadir ${CMAKE_INSTALL_DATADIR})
set(sysconfdir ${CMAKE_INSTALL_SYSCONFDIR})
set(datadir ${CMAKE_INSTALL_DATADIR})
set(top_builddir ${PROJECT_SOURCE_DIR})
set(PACKAGE ${PROJECT_NAME})
set(DISABLE_REST_API "") # TODO add rest api to options

configure_file(uniset2-codegen.in uniset2-codegen 
  FILE_PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ 
  @ONLY
  )
