include(CMakePackageConfigHelpers)

set(mur_pub_headers 
  ${CMAKE_CURRENT_SOURCE_DIR}/include/MurmurHash2.h 
  ${CMAKE_CURRENT_SOURCE_DIR}/include/MurmurHash3.h
  )
# message("mur pub headers: ${mur_pub_headers}")
set(mur_sources
  ${mur_pub_headers}
  ${CMAKE_CURRENT_SOURCE_DIR}/src/MurmurHash2.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/MurmurHash3.cpp
  )
# message("mur sources: ${mur_sources}")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${mur_sources})

add_library(murmurhash ${mur_sources})

target_include_directories(murmurhash 
  PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
  )
