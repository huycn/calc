# this is the top level project
cmake_minimum_required (VERSION 2.8.9)

project (Calc)

add_definitions (-DUNICODE -D_UNICODE)

add_subdirectory (guitk)

include_directories (
	${GUITK_INCLUDE}
)

set (RESOURCE_FILES res/resource.rc res/resource.h)

source_group ("Resource Files" FILES ${RESOURCE_FILES})

if (WIN32)
    set (CMAKE_SHARED_LINKER_FLAGS /MANIFEST:NO)
endif()

add_executable (calc WIN32 calc/main.cpp ${RESOURCE_FILES})
target_link_libraries (calc guitk comctl32.lib)

if (WIN32)
	add_custom_command (
		TARGET calc
		POST_BUILD
		COMMAND "mt.exe" -manifest \"${CMAKE_SOURCE_DIR}/calc.manifest\" -outputresource:"$(TargetPath)"\;\#1
		COMMENT "Adding manifest..." 
	)
endif()