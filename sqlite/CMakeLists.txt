cmake_minimum_required(VERSION 3.25)
project(sqlite3)



add_library(${PROJECT_NAME} STATIC sqlite3.c)

target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRREN_SOURCE_DIR})

if(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
endif()