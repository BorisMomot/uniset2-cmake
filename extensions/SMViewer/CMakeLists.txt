add_executable(uniset2-smviewer SMViewer.cc main.cc)
target_link_libraries(uniset2-smviewer uniset2extensions)

# Add installation
#---------------------------------------------------------------------------------------
install(TARGETS uniset2-smviewer
      RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
      COMPONENT uniset2-extensions-common
    )
