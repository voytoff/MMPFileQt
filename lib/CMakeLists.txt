cmake_minimum_required(VERSION 3.20)

project(MMPFile LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_library(MMPFile SHARED
  MMPFile_global.h
  mmpfile.cpp
  mmpfile.h
  mmpobject.h mmpobject.cpp
  fileitem.h fileitem.cpp
  channelarray.h channelarray.cpp
  channelblock.h channelblock.cpp
  file.h file.cpp
  datablock.h datablock.cpp
  datablockarray.h datablockarray.cpp
  parameter.h parameter.cpp
  lib.h lib.cpp
)

target_link_libraries(MMPFile PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_compile_definitions(MMPFile PRIVATE MMPFILE_LIBRARY)
