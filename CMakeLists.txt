CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)
project(TimebasedJobapp)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenSSL REQUIRED)

#
# Paho MQTT libraries
#
# Settings for the Paho C and C++ libraries
set(PAHO_WITH_SSL ON)
set(PAHO_BUILD_STATIC ON)
set(PAHO_BUILD_SHARED OFF)
set(PAHO_ENABLE_TESTING OFF)
# The Paho C library insists on being installable, but we don't.
set(CMAKE_INSTALL_LIBDIR something)
set(CMAKE_INSTALL_BINDIR something)
set(CMAKE_INSTALL_INCLUDEDIR something)

include_directories(paho.mqtt.c/src paho.mqtt.cpp/src)
add_subdirectory(paho.mqtt.c/src paho.mqtt.c)
# The Paho C++ build expects the Paho C library to be _installed_.
# The following settings get it to use the library in this build.
set(PAHO_MQTT_C_LIBRARIES ${PROJECT_SOURCE_DIR}/build/paho.mqtt.c/src)
set(PAHO_MQTT_C_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/paho.mqtt.c/src)

list(APPEND CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_SOURCE_DIR}/paho.mqtt.cpp/cmake)
add_subdirectory(paho.mqtt.cpp/src paho.mqtt.cpp)
# Now associate the right include path to the C++ library and
# the right dependency on the just-built C libraries.
# Sledgehammer:  overwrite the requisite properties.
set_target_properties(paho-mqttpp3-static PROPERTIES
  INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/paho.mqtt.cpp/src
  INTERFACE_INCLUDE_DIRECTORIES
    "${CMAKE_CURRENT_SOURCE_DIR}/paho.mqtt.cpp/src;${PAHO_MQTT_C_INCLUDE_DIRS}"
  LINK_LIBRARIES
    paho-mqtt3as-static
  INTERFACE_LINK_LIBRARIES
    paho-mqtt3as-static
)

#
# Paho MQTT libraries
#
# Settings for the Paho C and C++ libraries
include_directories(project)
add_subdirectory(project)

add_executable(TimebasedJobapp ${PROJECT_SOURCE_DIR}/app/multithreadClient.cpp)

target_link_libraries(TimebasedJobapp paho-mqtt3as-static paho-mqttpp3-static UCM_Project)