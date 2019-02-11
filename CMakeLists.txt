cmake_minimum_required (VERSION 3.12)
project (ili9341)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED true)

include_directories (include include/impl)

add_library(ili9341
        include/BackBuffer.h
        src/BackBuffer.cc
        include/Color.h
        include/ili9341.h
        src/ili9341.cc
        include/Rect.h
        src/Rect.cc include/impl/utils.hpp include/impl/span)

target_link_libraries(ili9341
        wiringPi)

add_executable(test_driver
        main.cc)

target_link_libraries(test_driver
        ili9341)