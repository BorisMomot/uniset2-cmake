# add_subdirectory(Test)
add_subdirectory(Core)
add_subdirectory(Communications)
add_subdirectory(Log)
add_subdirectory(ObjectRepository)
add_subdirectory(Processes)
add_subdirectory(Services)
add_subdirectory(Timers)
add_subdirectory(Various)
#

set(uniset_sources 
  ${uniset_core_sources}
  ${uniset_log_sources}
  ${uniset_processes_sources}
  ${uniset_obj_repo_sources}
  ${uniset_services_sources}
  ${uniset_timers_sources}
  ${uniset_various_sources} 
  ${uniset_communications_sources}
  PARENT_SCOPE
  )
