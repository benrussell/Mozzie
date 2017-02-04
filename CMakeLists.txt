cmake_minimum_required(VERSION 3.6)
project(Mozzie)

set(CMAKE_CXX_STANDARD 11)


# Enable XP SDK 2.0 and 2.1
add_definitions( -DXPLM200=1 -DXPLM210=1 )

# Define Linux as target.
add_definitions( -DLIN=1 )


# X-Plane SDK Includes - TWEAK THIS TO YOUR OWN CONFIG! ************************************************
set( XPSDK_ROOT_FOLDER "/home/br/Dropbox/Dev/XP_SDK_213" )

include_directories( "${XPSDK_ROOT_FOLDER}/CHeaders/Widgets" )
include_directories( "${XPSDK_ROOT_FOLDER}/CHeaders/Wrappers" )
include_directories( "${XPSDK_ROOT_FOLDER}/CHeaders/XPLM" )


# Source files for this project.
set(SOURCE_FILES Mozzie.cpp Mozzie.h main.cpp main.h Options.cpp Options.h XPCmd.cpp XPCmd.h XPDref.cpp XPDref.h)


# Linker output tweaks..
SET( XPL_OUTPUT_FILENAME "Mozzie_Linux" )
add_library(${XPL_OUTPUT_FILENAME} SHARED ${SOURCE_FILES})

SET_TARGET_PROPERTIES(${XPL_OUTPUT_FILENAME} PROPERTIES PREFIX  "" )
SET_TARGET_PROPERTIES(${XPL_OUTPUT_FILENAME} PROPERTIES SUFFIX ".xpl")

target_link_libraries( ${XPL_OUTPUT_FILENAME} mosquittopp )

# eof
