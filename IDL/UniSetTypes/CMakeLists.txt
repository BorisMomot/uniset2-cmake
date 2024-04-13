# TODO: make configuratble size of uniset word
set(IDL_UNISET_TYPES_LIST UniSetBaseConstants.idl UniSetManager_i.idl 
  UniSetObject_i.idl UniSetTypes_i.idl)

set(IDL_UNISET_TYPES_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(CPP_UNISET_TYPES_DIR ${CMAKE_CURRENT_BINARY_DIR})

foreach(IDL_FILE ${IDL_UNISET_TYPES_LIST})
  execute_process(
    COMMAND omniidl -bcxx ${IDL_UNISET_TYPES_DIR}/${IDL_FILE} 
    WORKING_DIRECTORY ${CPP_UNISET_TYPES_DIR}
    )
endforeach()

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${CPP_UNISET_TYPES_DIR})

# add dependency on file generation
add_custom_target(generate_files DEPENDS ${CPP_UNISET_TYPES_DIR}/UniSetBaseConstantsSK.cc)

# build library from them
add_library(uniset_types STATIC 
  ${CPP_UNISET_TYPES_DIR}/UniSetBaseConstantsSK.cc
  )
target_include_directories(uniset_types PUBLIC ${CPP_UNISET_TYPES_DIR})
add_dependencies(uniset_types generate_files)
