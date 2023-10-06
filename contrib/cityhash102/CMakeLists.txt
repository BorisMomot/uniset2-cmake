include(CMakePackageConfigHelpers)

set(city_hash_pub_headers 
  ${CMAKE_CURRENT_SOURCE_DIR}/include/city.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/citycrc.h
  )
# message("city_hash pub headers: ${city_hash_pub_headers}")
set(city_hash_sources
  ${city_hash_pub_headers}
  ${CMAKE_CURRENT_SOURCE_DIR}/src/city.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/src/config.h
  )
# message("city_hash sources: ${city_hash_sources}")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${city_hash_sources})

add_library(city_hash102 ${city_hash_sources})
target_include_directories(city_hash102
  PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
  )
