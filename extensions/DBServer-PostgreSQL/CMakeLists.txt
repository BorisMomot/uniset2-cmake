# TODO should be at least PGSQL 7 version (my is 6.4)
# TODO build only if UNISET2_BUILD_PGSQL
# TODO add test directory
# set(uniset_pgsql_source 
#   PostgreSQLInterface.cc 
#   DBServer_PostgreSQL.cc
#   )
# add_library(UniSet2-pgsql ${uniset_pgsql_source})
# target_compile_features(UniSet2-pgsql PUBLIC cxx_std_17)
# target_include_directories(UniSet2-pgsql PUBLIC ${PGSQL_INDLUDE_DIRS})
# target_link_libraries(UniSet2-pgsql
#   uniset2extensions
#   UnisetSharedMemory
#   ${PGSQL_LIBRARIES}
#   )
# # Add executable
# add_executable(uniset2-pgsql-dbserver main.cc) 
# target_link_libraries(uniset2-pgsql-dbserver UniSet2-pgsql)
#
# add_executable(pgsql-test test.cc)
# target_link_libraries(pgsql-test UniSet2-pgsql)
