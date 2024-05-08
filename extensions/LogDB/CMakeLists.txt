# TODO add option to disable build
add_executable(uniset2-logdb
  LogDB.cc 
  main.cc
  )
target_link_libraries(uniset2-logdb
  uniset2
  UniSet2-sqlite
  )

add_executable(uniset2-logdb-conv logdb-conv.cc)
target_link_libraries(uniset2-logdb-conv
  uniset2
  UniSet2-sqlite
  )
