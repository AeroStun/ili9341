# wiringPi_FOUND - System has wiringPi
# wiringPi_INCLUDES - The wiringPi include directories
# wiringPi_LIBRARIES - The libraries needed to use wiringPi
# wiringPi_DEFINITIONS - Compiler switches required for using wiringPi

find_package(PkgConfig)
pkg_check_modules(PC_wiringPi QUIET wiringPi)
set(wiringPi_DEFINITIONS ${PC_wiringPi_CFLAGS_OTHER})

find_path(wiringPi_INCLUDE_DIR
        NAMES wiringPi.h wiringPiSPI.h
        HINTS ${PC_LibVirt_INCLUDEDIR} ${PC_LibVirt_INCLUDE_DIRS}
        PATH_SUFFIXES libvirt)

find_library(wiringPi_LIBRARY
        NAMES wiringPi
        HINTS ${PC_wiringPi_LIBDIR} ${PC_wiringPi_LIBRARY_DIRS})

set(wiringPi_LIBRARIES ${wiringPi_LIBRARY})
set(wiringPi_INCLUDE_DIRS ${wiringPi_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(wiringPi DEFAULT_MSG
        wiringPi_LIBRARY wiringPi_INCLUDE_DIR)

mark_as_advanced(wiringPi_INCLUDE_DIR wiringPi_LIBRARY)
