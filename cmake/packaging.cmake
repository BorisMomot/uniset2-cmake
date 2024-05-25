set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_CONTACT "Pavel Vainerman"})
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_COMPONENTS_GROUPING ONE_PER_GROUP)
set(CPACK_RPM_COMPONENT_INSTALL 1)
include(CPack)
# setup packages
# All pacakges from the spec file
# uniset2
# uniset2-devel
# uniset2-utils
# uniset2-netdata-plugin
# uniset2-extension-common
# uniset2-extension-clickhouse
# uniset2-extension-io
# uniset2-extension-logdb
# uniset2-extension-logicproc
# uniset2-extension-mqtt
# uniset2-extension-mysql
# uniset2-extension-opcua
# uniset2-extension-opentsdb
# uniset2-extension-pgsql
# uniset2-extension-rrd
# uniset2-extension-sqlite
# uniset2-extension-uresolver
# uniset2-extension-wsgate
# uniset2-python3-module
# uniset2-docs
# uniset2-extension-common-devel
# uniset2-extension-clickhouse-devel
# uniset2-extension-io-devel
# uniset2-extension-logicproc-devel
# uniset2-extension-mqtt-devel
# uniset2-extension-mysql-devel
# uniset2-extension-opcua-devel
# uniset2-extension-opentsdb-devel
# uniset2-extension-pgsql-devel
# uniset2-extension-rrd-devel
# uniset2-extension-sqlite-devel
# uniset2-extension-wsgate-devel

# Descision: we don't need word extension
# uniset2-docs
# uniset2-devel
# uniset2-extension-common-devel
# uniset2-clickhouse-devel
# uniset2-io-devel
# uniset2-logicproc-devel
# uniset2-mqtt-devel
# uniset2-mysql-devel
# uniset2-opcua-devel
# uniset2-opentsdb-devel
# uniset2-pgsql-devel
# uniset2-rrd-devel
# uniset2-sqlite-devel
# uniset2-wsgate-devel

cpack_add_component(uniset2 DESCRIPTION "UniSet is a library for distributed control systems.")
cpack_add_component(uniset2-extensions-common DESCRIPTION "Common components for all extensions")
cpack_add_component(uniset2-utils DESCRIPTION "Utils for uniset2")
if(UNISET2_BUILD_CLICKHOUSE)
  cpack_add_component(uniset2-clickhouse DESCRIPTION "Backend for Clickhouse DB")
endif()
if(UNISET2_BUILD_TSDB)
  cpack_add_component(uniset2-opentsdb DESCRIPTION "Backend for TS DB")
endif()
if(UNISET2_BUILD_MYSQL)
  cpack_add_component(uniset2-mysql DESCRIPTION "Backend for mysql DB")
endif()
if(UNISET2_BUILD_SQLITE)
  cpack_add_component(uniset2-sqlite DESCRIPTION "Backend for sqlite DB")
endif()
if(ENABLE_REST_API)
  cpack_add_component(uniset2-uresolver DESCRIPTION "HTTP Resolver")
endif()
if(UNISET2_BUILD_IO)
  cpack_add_component(uniset2-io DESCRIPTION "Backend for Clickhouse DB")
endif()
if(UNISET2_BUILD_LOGDB)
  cpack_add_component(uniset2-logdb DESCRIPTION "Backend for logdb")
endif()
if(UNISET2_BUILD_LPROC)
  cpack_add_component(uniset2-logicproc DESCRIPTION "Logic processor")
endif()
if(UNISET2_BUILD_MQTT)
  cpack_add_component(uniset2-mqtt DESCRIPTION "Backend for Clickhouse DB")
endif()
if(UNISET2_BUILD_OPCUA)
  cpack_add_component(uniset2-opcua DESCRIPTION "OPC UA support for the uniset2")
endif()
if(UNISET2_BUILD_PGSQL)
  cpack_add_component(uniset2-pgsql DESCRIPTION "PostgreSQL dbserver for the uniset2")
endif()
if(UNISET2_BUILD_RRD)
  cpack_add_component(uniset2-rrd DESCRIPTION "RRD extensions for the uniset2")
endif()
if(UNISET2_BUILD_UWEBSOCKET)
  cpack_add_component(uniset2-wsgate DESCRIPTION "Websocket gate for the uniset2")
endif()
if(UNISET2_BUILD_PYTHON)
  cpack_add_component(uniset2-python3-module DESCRIPTION "Python interface for the uniset2")
endif()
if(UNISET2_BUILD_NETDATA)
  cpack_add_component(uniset2-netdata-plugin DESCRIPTION "Python plugin for the netdata")
endif()
