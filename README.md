# MQTT Data Streamer Library
This library makes use of MQTT easier. It is mainly designed using examples from the paho.mqtt.cpp library

## Installation
The following instructions must be followed:
```
// install mqtt c library
git clone https://github.com/eclipse/paho.mqtt.c.git
cd paho.mqtt.c
cmake -Bbuild -H. -DPAHO_ENABLE_TESTING=OFF -DPAHO_BUILD_STATIC=ON \
        -DPAHO_WITH_SSL=ON -DPAHO_HIGH_PERFORMANCE=ON
cmake --build build/ --target install

// install mqtt c++ library
git clone https://github.com/eclipse/paho.mqtt.cpp
cd paho.mqtt.cpp
cmake -Bbuild -H. -DPAHO_BUILD_STATIC=ON \
        -DPAHO_BUILD_DOCUMENTATION=TRUE -DPAHO_BUILD_SAMPLES=TRUE
cmake --build build/ --target install

// install 
git clone https://github.com/unbeschwert/mqtt-data-streamer.git mqtt-data-streamer
cd mqtt-data-streamer
mkdir build && cd build
cmake -DPahoMqttC_INCLUDE_DIRS="/path/to/include_dir" -DPahoMqttCpp_INCLUDE_DIRS="/path/to/include_dir" ..
make
sudo make install
```
## Issues and Pull Requests
If you have any ideas about improvements or changes that might make this library better, please first create an issue so that we can discuss first. 
