# this is the top level project
cmake_minimum_required (VERSION 2.8.9)

project (Calc)

add_definitions (-DUNICODE -D_UNICODE)

add_subdirectory (guitk)

include_directories (
	${GUITK_INCLUDE}
)

add_executable (calc calc/main.cpp)
target_link_libraries (calc guitk)
