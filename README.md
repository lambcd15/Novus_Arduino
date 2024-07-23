![image](https://github.com/user-attachments/assets/d78b6014-d9f3-4dcd-98c5-bf98b761f9fa)# Novus_Arduino
Documentation for Arduino control of Novus 1020 temperature controllers

Due to the lack of finding other documentation for this process and also for something to refer back to, Ihave compiled the steps required to interface an arduino through SoftwareSerial to a Novus 1020 temperature controller
https://www.novusautomation.com/en/product/controllers/n1020

## Table of Contents

* [NOVUS1020 setup](#novus1020-setup)
* [Arduino IDE Setup](#arduino-ide-setup)



## NOVUS1020 setup
A configuration file is included that can be used with QuickTune to setup the controller for MODBUS

First download and install Quicktune from the novus automation webpage under software.

Next downalod and extract the files from this repository

Once installed select open configuration navigate to the location of the repository files and open the configuration

![image](https://github.com/user-attachments/assets/49187015-a5a9-4231-8f79-d0ec28ccafe8)
![image](https://github.com/user-attachments/assets/b38bc379-963a-4b59-a88b-2394a5c61622)


Once opened connect the temperature controller and click send to device (bottom right). Select the COM port for the controller and wait for it to upload.

If an error message appears go back to the config and enter a set point between 20 and 250°C and repeat the send to device steps

![image](https://github.com/user-attachments/assets/03741bbc-e648-480e-94a9-725edd910326)


## Arduino IDE Setup

First make sure to download and install the following library into Arduino IDE
https://github.com/CMB27/ModbusRTUMaster

Once installed you can open and run the attached script for a simple interface for setting and reading the setpoint

The register tables can be found under the downloads section on the Novus Automation webpage (listed above)

![image](https://github.com/user-attachments/assets/989fefac-3807-455c-b840-319f5a6162d7)

Credit:
CMB27
Novus automation
