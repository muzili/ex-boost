cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
project(02_Embed_GetList)
set(TARGET main02)
set(SOURCE_CPP main.cpp)
set(SOURCE_HPP)
set(SOURCE_UIC)
set(SOURCE_QRC)
set(SOURCE_PYT main.py)
set(SOURCE_ALL ${SOURCE_CPP} ${SOURCE_HPP} ${SOURCE_QRC} ${SOURCE_UIC} ${SOURCE_PYT})
add_executable(${TARGET} ${SOURCE_ALL})
include(useQt5)
include(useBoost)
include(usePython)
include(addTest)