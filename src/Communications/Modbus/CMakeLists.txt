set(uniset_modbus_sources 
  ${CMAKE_CURRENT_SOURCE_DIR}/ModbusTypes.cc 
  ${CMAKE_CURRENT_SOURCE_DIR}/ModbusHelpers.cc 
  ${CMAKE_CURRENT_SOURCE_DIR}/ModbusTCPSession.cc 
	${CMAKE_CURRENT_SOURCE_DIR}/ModbusClient.cc 
	${CMAKE_CURRENT_SOURCE_DIR}/ModbusServer.cc 
	${CMAKE_CURRENT_SOURCE_DIR}/ModbusServerSlot.cc 
	${CMAKE_CURRENT_SOURCE_DIR}/ModbusRTUSlave.cc 
	${CMAKE_CURRENT_SOURCE_DIR}/ModbusRTUSlaveSlot.cc 
	${CMAKE_CURRENT_SOURCE_DIR}/ModbusRTUMaster.cc 
	${CMAKE_CURRENT_SOURCE_DIR}/ModbusTCPCore.cc 
	${CMAKE_CURRENT_SOURCE_DIR}/ModbusTCPServer.cc 
	${CMAKE_CURRENT_SOURCE_DIR}/ModbusTCPServerSlot.cc 
	${CMAKE_CURRENT_SOURCE_DIR}/ModbusTCPMaster.cc
	PARENT_SCOPE
  )
#----------------------------------------------------------------------------------------
# set(uniset_modbus_sources 
#   ModbusTypes.cc 
#   ModbusHelpers.cc 
#   ModbusTCPSession.cc 
# 	ModbusClient.cc 
# 	ModbusServer.cc 
# 	ModbusServerSlot.cc 
# 	ModbusRTUSlave.cc 
# 	ModbusRTUSlaveSlot.cc 
# 	ModbusRTUMaster.cc 
# 	ModbusTCPCore.cc 
# 	ModbusTCPServer.cc 
# 	ModbusTCPServerSlot.cc 
# 	ModbusTCPMaster.cc
#   )
#
# source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${uniset_modbus_sources})
#
# add_library(uniset_modbus OBJECT ${uniset_modbus_sources})
# target_include_directories(uniset_modbus
#   PUBLIC 
#     ${PROJECT_BINARY_DIR}/IDL/UniSetTypes
#     ${PROJECT_BINARY_DIR}/IDL/Processes
#     ${PROJECT_SOURCE_DIR}/include
#     ${SIGC_INCLUDE_DIRS}
#     ${EV_INCLUDE_DIRS}
#   PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/src
#     ${CPP_UNISET_TYPES_DIR}
#   )
# target_link_libraries(uniset_modbus 
#   poco 
#   LibXml2::LibXml2
#   ${EV_LIBRARIES}
#   ${SIGC_LIBRARIES}
#   )
# ####################################################
# # noinst_LTLIBRARIES 		= libModbus.la
# # libModbus_la_SOURCES	= ModbusTypes.cc ModbusHelpers.cc ModbusTCPSession.cc \
# # 	ModbusClient.cc ModbusServer.cc ModbusServerSlot.cc \
# # 	ModbusRTUSlave.cc ModbusRTUSlaveSlot.cc ModbusRTUMaster.cc \
# # 	ModbusTCPCore.cc ModbusTCPServer.cc ModbusTCPServerSlot.cc ModbusTCPMaster.cc
# # 	
# # libModbus_la_CXXFLAGS	= -I$(top_builddir)/include/Communications/modbus $(SIGC_CFLAGS) $(POCO_CFLAGS) $(EV_CFLAGS)
# # #libModbus_la_LIBADD		= $(top_builddir)/src/Communications/TCP/libTCP.la $(SIGC_LIBS) $(POCO_LIBS)
# # libModbus_la_LIBADD		= $(SIGC_LIBS) $(POCO_LIBS) $(EV_LIBS)
# #
