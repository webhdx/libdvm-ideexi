cmake_minimum_required(VERSION 3.13)

project(dvm_ideexi LANGUAGES C)

if(NOT (NINTENDO_GAMECUBE OR NINTENDO_WII))
	message(FATAL_ERROR "Unknown platform")
endif()

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set(CMAKE_INSTALL_PREFIX "${OGC_ROOT}" CACHE PATH "" FORCE)
	set(CMAKE_INSTALL_LIBDIR "lib/${OGC_SUBDIR}" CACHE PATH "" FORCE)
endif()

add_library(dvm_ideexi STATIC)

target_compile_options(dvm_ideexi PRIVATE -Wall)

target_include_directories(dvm_ideexi
	PUBLIC
		include
)

target_sources(dvm_ideexi PRIVATE
	source/ideexi.c
	source/dvm_ideexi.c
)

include(GNUInstallDirs)

# Install the library
install(
	TARGETS dvm_ideexi
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Install the header
install(
	FILES include/dvm_ideexi.h include/ideexi.h
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
