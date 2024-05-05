# TODO build only if ENABLE_MYSQL
set(uniset_mysql_source 
  MySQLInterface.cc 
  DBServer_MySQL.cc
  )
add_library(UniSet2-mysql ${uniset_mysql_source})
target_link_libraries(UniSet2-mysql
  uniset2extensions
  UnisetSharedMemory
  ${MYSQL_LIBRARIES}
  )
# Add executable
add_executable(uniset2-mysql-dbserver main.cc) 
target_link_libraries(uniset2-mysql-dbserver UniSet2-mysql)

add_executable(mysql-test test.cc)
target_link_libraries(mysql-test UniSet2-mysql)
