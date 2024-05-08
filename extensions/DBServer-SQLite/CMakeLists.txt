# TODO build only if ENABLE_SQLITE
set(uniset_sqlite_source 
  SQLiteInterface.cc 
  DBServer_SQLite.cc
  )
add_library(UniSet2-sqlite ${uniset_sqlite_source})
target_include_directories(UniSet2-sqlite PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(UniSet2-sqlite
  uniset2extensions
  UnisetSharedMemory
  ${SQLITE3_LIBRARIES}
  )

# Add executable
add_executable(uniset2-sqlite-dbserver main.cc) 
target_link_libraries(uniset2-sqlite-dbserver UniSet2-sqlite)

add_executable(sqlite-test test.cc)
target_link_libraries(sqlite-test UniSet2-sqlite)
