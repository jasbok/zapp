cmake_minimum_required(VERSION 3.5)
project(QtZapp)

if(${UNIX})
add_definitions(-D_UNIX)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")

# c++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
        message("c++11 Support: TRUE")
elseif(COMPILER_SUPPORTS_CXX0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
        message("c++11 Support: TRUE")
else()
        message(STATUS "${CMAKE_CXX_COMPILER} does not have C++11 support.")
endif()

# LibArchive
find_package(LibArchive REQUIRED)
message("Found LibArchive: " ${LibArchive_FOUND})
list (APPEND INCLUDE_DIRS ${LibArchive_INCLUDE_DIRS})
list (APPEND TARGET_LINK_LIBS ${LibArchive_LIBRARIES})

# Unrar
find_package(LibUnrar REQUIRED)
message("Found LibUnrar: " ${LIBUNRAR_FOUND})
list (APPEND INCLUDE_DIRS ${LIBUNRAR_INCLUDE})
list (APPEND TARGET_LINK_LIBS ${LIBUNRAR_LIBRARY})

# Qt5
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Core)
list (APPEND INCLUDE_DIRS ${Qt5Core_INCLUDE_DIRS})
list (APPEND TARGET_LINK_LIBS ${Qt5Core_LIBRARIES})

list(APPEND INCLUDE_DIRS "src")
include_directories(${INCLUDE_DIRS})

add_subdirectory(src)
