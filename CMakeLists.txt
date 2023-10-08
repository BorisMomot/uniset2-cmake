cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(uniset2 VERSION 3.32.1 DESCRIPTION "Library for automation" LANGUAGES CXX)

# add_library(uniset2)
# add_library(uniset2::uniset2 ALIAS uniset2)

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_DIR}" is_top_level)
#-----------------------------------------------------------------------------------
include(cmake/utils.cmake)
include(GNUInstallDirs)
#-----------------------------------------------------------------------------------
# Project options
include(CMakeDependentOption)
option(UNISET2_CHECK_LIBEV "Check for libev" ON)
option(UNISET2_CHECK_EXT "Build uniset with extencions" ON)
option(UNISET2_BUILD_API "Build uniset with api" ON)
option(UNISET2_BUILD_CLICKHOUSE "Build uniset with clickhouse" ON)
option(UNISET2_BUILD_COM485F "Build uniset with com485f" ON)
option(UNISET2_BUILD_IO "Build uniset with io" ON)
option(UNISET2_BUILD_LOGDB "Build uniset with logDB" ON)
option(UNISET2_BUILD_LPROC "Build uniset with lproc" ON)
option(UNISET2_BUILD_MQTT "Build uniset with MQTT" ON)
option(UNISET2_BUILD_MYSQL "Build uniset with MySQL" ON)
option(UNISET2_BUILD_OPCUA "Build uniset with OPCUA" OFF)
option(UNISET2_BUILD_PGSQL "Build uniset with PGSQL" ON)
option(UNISET2_BUILD_RRD "Build uniset with RRD" ON)
option(UNISET2_BUILD_SQLITE "Build uniset with SQLite" ON)
option(UNISET2_BUILD_TSDB "Build uniset with TSDB" ON)
option(UNISET2_BUILD_UWEBSOCKET "Build uniset with websocket" ON)
option(UNISET2_BUILD_PYTHON "Build uniset with python connection" ON)
cmake_dependent_option(UNISET2_BUILD_NETDATA "Build uniset with netdata" ON "UNISET2_BUILD_PYTHON" ON)

option(UNISET2_BUILD_DOCS "Build uniset with docs" OFF)
option(UNISET2_BUILD_TEST "Build uniset with test" ON)
cmake_dependent_option(UNISET2_BUILD_GCOV "Build uniset with gcov" OFF "UNISET2_BUILD_TEST" ON)

set_if_undefined(UNISET@_INSTALL_CMAKEDIR 
  "${CMAKE_INSTALL_LIBDIR}/cmake/uniset2-${PROJECT_VERSION}" CACHE STRING
  "Install path for mylib package-related CMake files")

# Define for all libraries be shared in case we need them
if (DEFINED UNISET2_SHARED_LIBS)
  set(BUILD_SHARED_LIBS ${UNISET@_SHARED_LIBS})
endif()

#-----------------------------------------------------------------------------------
# Check dependencies
find_package(Poco REQUIRED Net JSON)
find_package(LibXml2 REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(OMNI REQUIRED omniORB4)
pkg_check_modules(SIGC REQUIRED sigc++-2.0)
pkg_check_modules(EV REQUIRED libevent)

find_package(LibXslt REQUIRED)
# TODO check IDL

# Dependent libs
if(UNISET2_BUILD_SQLITE)
  pkg_check_modules(SQLITE3 REQUIRED sqlite3)
endif()
if(UNISET2_BUILD_PGSQL)
	pkg_check_modules(PGSQL REQUIRED libpqxx)
endif()
if(UNISET2_BUILD_RRD)
	pkg_check_modules(RRD REQUIRED librrd)
endif()
if(UNISET2_BUILD_OPCUA)
	pkg_check_modules(OPEN62541PP REQUIRED  open62541pp)
	pkg_check_modules(OPEN62541 REQUIRED  open62541)
endif()
if(UNISET2_BUILD_IO)
	pkg_check_modules(COMEDI REQUIRED comedilib)
endif()
if(UNISET2_BUILD_PYTHON)
  find_package(Python3 REQUIRED)
endif()
	

add_subdirectory(IDL)
add_subdirectory(contrib)
add_subdirectory(src)
add_subdirectory(lib)
add_subdirectory(Utilities)
