cmake_minimum_required(VERSION 3.16)
project(c-mindustry)
SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++") # 填写绝对路径
set(CMAKE_CXX_STANDARD 20)
set(BUILD_DIR "./build/.")
add_compile_options(-std=c++2a)
file(GLOB_RECURSE DIR_SRCS 
	"${PROJECT_SOURCE_DIR}/src/*.h"
	"${PROJECT_SOURCE_DIR}/src/*.cpp"
	"${PROJECT_SOURCE_DIR}/src/*.hpp"
	"${PROJECT_SOURCE_DIR}/src/*.cc"
)
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/")
add_executable(${CMAKE_PROJECT_NAME} ${DIR_SRCS})

add_custom_command(
	TARGET ${CMAKE_PROJECT_NAME}
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${PROJECT_SOURCE_DIR}/src/assets"
		"$<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>/assets"
)
