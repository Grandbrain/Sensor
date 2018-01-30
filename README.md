[![GitHub release](https://img.shields.io/github/release/Grandbrain/Sensor.svg)](https://github.com/Grandbrain/Sensor/releases)
[![GitHub issues](https://img.shields.io/github/issues/Grandbrain/Sensor.svg)](https://github.com/Grandbrain/Sensor/issues)
[![GitHub forks](https://img.shields.io/github/forks/Grandbrain/Sensor.svg)](https://github.com/Grandbrain/Sensor/network/members)
[![GitHub stars](https://img.shields.io/github/stars/Grandbrain/Sensor.svg)](https://github.com/Grandbrain/Sensor/stargazers)
[![GitHub license](https://img.shields.io/github/license/Grandbrain/Sensor.svg)](https://github.com/Grandbrain/Sensor/blob/master/LICENSE)

# Welcome to Sensor project!

[Sensor](https://github.com/Grandbrain/Sensor) is a cross-platform application to use the LD-MRS scanners. The program uses Ethernet protocol and allows to obtain measurement data, change device settings, as well as track the status of the device and to detect errors and warnings. The program is based on the Qt Framework and can run on all platforms supported by this library.


## Contribute

There are several ways to contribute to Sensor project:
* [Submit bugs](https://github.com/Grandbrain/Sensor/issues) and help me verify fixes.
* Review the [source code changes](https://github.com/Grandbrain/Sensor/pulls).
* Read and update [documentation](https://github.com/Grandbrain/Sensor/tree/master/Docs) files.


## Documentation

*  [Protocol specification](https://github.com/Grandbrain/Sensor/blob/master/Docs/Protocol(en).pdf)


## Building

*  Download and extract the [latest release](https://github.com/Grandbrain/Sensor/releases) of the source code.
*  Download and install the latest version of [Qt Community](https://www.qt.io/ru/download-open-source).
*  Launch Qt Creator and open the project file "Sensor.pro".
*  Rebuild the project by clicking "Rebuild all" in the "Build" menu.
*  Launch the application by clicking "Run" in the "Build" menu.


## Usage

* Connect the LD-MRS scanner to the network.
* Launch the application and connect to the scanner by entering its address and clicking "Connect".
* Use the tabs "Chart" and "Settings" to see the scanner measurement and control its parameters.
