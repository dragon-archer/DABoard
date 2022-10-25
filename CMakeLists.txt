cmake_minimum_required(VERSION 3.16)
project(DABoard VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(fmt REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(spdlog REQUIRED)

message(STATUS "${Qt6_DIR}")
message(STATUS "${fmt_DIR}")
message(STATUS "${nlohmann_json_DIR}")
message(STATUS "${spdlog_DIR}")

set(DABOARD_SRC
	config.h
	datastore.h
	datastore.cpp
	jsonwrapper.h
	jsonwrapper.cpp
	main.cpp
	mainwindow.cpp
	mainwindow.h
	parser.cpp
	parser.h
)

set(DABOARD_PCH pch.h)

set(DABOARD_LIB
	Qt6::Widgets
	fmt::fmt
	nlohmann_json::nlohmann_json
	spdlog::spdlog
)

qt_add_executable(daboard
	MANUAL_FINALIZATION
	${DABOARD_SRC}
	${DABOARD_PCH}
)

target_precompile_headers(daboard PRIVATE ${DABOARD_PCH})
target_link_libraries(daboard PRIVATE ${DABOARD_LIB})

add_custom_command(
	TARGET daboard POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
			${CMAKE_SOURCE_DIR}/data
			${CMAKE_BINARY_DIR}/data
)

qt_finalize_executable(daboard)

if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
	set_target_properties(daboard PROPERTIES
		WIN32_EXECUTABLE TRUE
	)
endif()


if(STATIC_BUILD)
	if(MSVC)
		set_property(GLOBAL PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded")
	else() # Assume accept GCC-like options
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s -static -static-libgcc -static-libstdc++")
	endif()
endif()
