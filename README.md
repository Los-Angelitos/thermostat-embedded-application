# ThermostatDevice SweetManager IoT (C++)

**Version**: 1.0.0
**Author**: SweetManager Team
**Date**: June 15, 2025

## Overview
This C++ code implements a thermostat device for the SweetManager IoT platform. It allows users to control and monitor the temperature settings of their room hotel environment. The device can be configured to operate in different modes, such as heating or cooling, and can be controlled via a web interface.

The framework used is based on the SweetManager IoT platform, which provides a robust set of features for IoT devices, including device management, data storage, and user interface components.

# Prerequisites
- **Hardware**: ESP32 development board, DHT22 temperature and humidity sensor, relay module for heating/cooling control.
- **Software**: Arduino IDE with ESP32 support, or Wokwi for simulation.
- **Dependency**: Modest IoT Nano-framework (C++ Edition) v0.1.

# Installation
1. **Download Framework** Clone or download [`Modest IoT Nano-framework`]()
2. **Directory Structure**: Combine files

```planetext
Thermostat-Embedded-Application/
├── sketch.ino
├── ThermostatDevice.h
├── ThermostatDevice.cpp
├── diagram.json
├── README.md
└── (copied from Modest IoT Nano-framework)
    ├── ModestIoT.h
    ├── ModestIoT.cpp
    ├── ModestIoTDevice.h
    └── ModestIoTDevice.cpp
```

## Credits
- **Modest IoT Nano-framework**: Provides the core functionality for device management and communication. Author: Angel Velasquez [@angelvelasquez](https://github.com/upc-pre-202510-1asi0572-2971/toggable-led-device-cpp-2971/tree/master)