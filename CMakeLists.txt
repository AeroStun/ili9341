cmake_minimum_required (VERSION 3.12)
project (ili9341)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED true)

set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)

find_package (WiringPi REQUIRED)

include_directories (${wiringPi_INCLUDES} include include/impl)

add_library(ili9341
        include/BackBuffer.h
        src/BackBuffer.cc
        include/Color.h
        include/ili9341.h
        src/ili9341.cc
        include/Rect.h
        src/Rect.cc include/impl/utils.hpp include/impl/span)

target_link_libraries(ili9341
        ${wiringPi_LIBRARIES})

target_compile_definitions (ili9341
        PUBLIC ${wiringPi_DEFINITIONS})

add_executable(test_driver
        main.cc)

target_link_libraries(test_driver
        ili9341)