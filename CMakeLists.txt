cmake_minimum_required(VERSION 3.16)

set(CMAKE_GENERATOR_PLATFORM win32)

project(tb_plugin_utils)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(NOT(CMAKE_SIZEOF_VOID_P EQUAL 4))
    message(FATAL_ERROR "You are configuring a non 32-bit build, this is not supported. Run cmake with `-A Win32`")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/")

add_compile_options(/MP /permissive-)
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(minhook CONFIG REQUIRED)
find_package(ctre CONFIG REQUIRED)

add_compile_definitions(WOLFSSL_NO_OPTIONS_H)
include(gwtoolboxpp)

add_library(tb_plugin_utils STATIC)

file(GLOB_RECURSE SOURCES
    "include/*.h"
	"src/*.h"
	"src/*.cpp"
	)

target_include_directories(tb_plugin_utils PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
	)
target_include_directories(tb_plugin_utils PRIVATE
	${gwtoolboxpp_SOURCE_DIR}/Dependencies/GWCA/include
	)
target_link_libraries(tb_plugin_utils PRIVATE
	gwca
	minhook::minhook
	ctre::ctre
	)
target_link_options(tb_plugin_utils PRIVATE
	"$<$<CONFIG:DEBUG>:/NODEFAULTLIB:LIBCMT>"
	)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})
target_sources(tb_plugin_utils PRIVATE ${SOURCES})
target_compile_definitions(tb_plugin_utils PRIVATE
	"NOMINMAX"
	"_WIN32_WINNT=_WIN32_WINNT_WIN7"
	"WIN32_LEAN_AND_MEAN"
	"VC_EXTRALEAN"
	)
set_target_properties(tb_plugin_utils PROPERTIES DEBUG_POSTFIX "d")