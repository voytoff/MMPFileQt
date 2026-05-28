cmake_minimum_required(VERSION 3.20)
project(MMPFile LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS
  Core
)

set(GLOBALLIBDIR "../../GlobalLibQt")
include_directories(${GLOBALLIBDIR})
if (NOT TARGET GlobalLib)
    add_subdirectory(${GLOBALLIBDIR} GlobalLib)
endif()

add_library(MMPFile SHARED
  MMPFile_global.h
  mmpfile.cpp
  mmpfile.h
  mmpobject.h mmpobject.cpp
  mfileitem.h mfileitem.cpp
  mchannelarray.h mchannelarray.cpp
  mchannelblock.h mchannelblock.cpp

  mlib.h mlib.cpp
  datablock.h datablock.cpp
)

target_link_libraries(MMPFile PRIVATE
  Qt6::Core
  GlobalLib
)
target_compile_definitions(MMPFile PRIVATE MMPFILE_LIBRARY)
