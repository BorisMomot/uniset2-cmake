#include <UniSetTypes.h>
#include <iostream>
#include <modbus/ModbusTCPMaster.h>
#include <unistd.h>

int main(int argc, char **argv) {
  uniset::ModbusTCPMaster mbclient;
  uniset::ThresholdId thr{0};
  std::cout << "Test string uniset " << std::endl;
  return 0;
}
