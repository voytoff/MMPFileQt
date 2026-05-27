cmake_minimum_required(VERSION 3.17)
project(tst_MMPFile VERSION 0.1 LANGUAGES CXX)
enable_testing()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Test)
qt_standard_project_setup(REQUIRES 6.5)

include_directories(../lib)

set(CMAKE_AUTOMOC ON)

qt_add_executable(tst_MMPFile
    tst_mmptest.cpp
)

#set_target_properties(tst_ACD2File PROPERTIES
#    MACOSX_BUNDLE FALSE
#    WIN32_EXECUTABLE FALSE
#)

target_link_libraries(tst_MMPFile PRIVATE Qt6::Test MMPTest)

add_test(NAME MMPTest COMMAND MMPTest)
