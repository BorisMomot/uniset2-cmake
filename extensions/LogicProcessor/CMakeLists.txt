# TODO if ENABLE_LOGICPROC
# TODO add tests
set(uniset_lprocessor 
  Element.cc 
  TOR.cc 
  TAND.cc 
  TDelay.cc 
  TNOT.cc 
  TA2D.cc 
  TSEL_R.cc 
  TRS.cc 
  Schema.cc 
  SchemaXML.cc 
  LProcessor.cc 
  PassiveLProcessor.cc
  )
# TODO setup shared or static
add_library(UniSet2LProcessor SHARED ${uniset_lprocessor})
set_target_properties(UniSet2LProcessor PROPERTIES
  VERSION ${CMAKE_PROJECT_VERSION}
  SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR}
  )
target_include_directories(UniSet2LProcessor
  PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
    ${SIGC_INCLUDE_DIRS}
    ${COMEDI_INCLUDE_DIRS}
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CPP_UNISET_TYPES_DIR}
  )
target_link_libraries(UniSet2LProcessor
  uniset2extensions
  uniset2
  UnisetSharedMemory
  ${SIGC_LIBRARIES}
  ${COMEDI_LIBRARIES}
  )

add_executable(logicproc logicproc.cc)
target_link_libraries(logicproc
  uniset2
  uniset2extensions
  UniSet2LProcessor
  )
add_executable(plogicproc plogicproc.cc)
target_link_libraries(plogicproc 
  uniset2
  uniset2extensions
  UniSet2LProcessor
  )
