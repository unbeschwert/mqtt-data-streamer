cmake_minimum_required(VERSION 3.12)
project(MqttKameraStreamer VERSION 1.0 DESCRIPTION "publish images in OpenCV Mat format using MQTT protocol")

set(CMAKE_INSTALL_PREFIX "/usr/local")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -pedantic -Werror)

set(LIBRARY_NAME mqtt_kamera_streamer)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

configure_package_config_file("Config.cmake.in" 
      "${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake"
      INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${CMAKE_PROJECT_NAME}")

set(MQTT_KAMERA_STREAMER_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

find_package(PahoMqttCpp COMPONENTS PahoMqttC REQUIRED)

set(PahoMqttCpp_LIBS PahoMqttCpp::paho-mqttpp3)

add_library(${LIBRARY_NAME} SHARED src/MQTTKameraStreamer.cc)
set_target_properties(${LIBRARY_NAME} 
    PROPERTIES 
        SOVERSION 1 
        PUBLIC_HEADER "include/MQTTKameraStreamer.hh;include/HelperClasses.hh")

target_link_libraries(${LIBRARY_NAME} ${PahoMqttCpp_LIBS})

target_include_directories(${LIBRARY_NAME} 
    PRIVATE ${PahoMqttCpp_INCLUDE_DIRS}
    PRIVATE ${PahoMqttC_INCLUDE_DIRS}
    PRIVATE ${MQTT_KAMERA_STREAMER_INCLUDE_DIR})

install(TARGETS ${LIBRARY_NAME} 
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} 
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES "${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}Config.cmake"
      DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${CMAKE_PROJECT_NAME}")
