cmake_minimum_required(VERSION 3.10)

project(tempest
	VERSION 0.1.0
)

find_package(Notcurses REQUIRED)

if ( NOT CMAKE_BUILD_TYPE )
	message("Build type not set, defaulting to Debug...")
	set(CMAKE_BUILD_TYPE Debug)
endif()

set(SANITIZER_FLAGS
    -fsanitize=leak,undefined,float-divide-by-zero,float-cast-overflow
)

string(TOLOWER ${CMAKE_BUILD_TYPE} build_type)

# LSP support
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} 
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_link_libraries(${PROJECT_NAME} PRIVATE notcurses-core)

target_compile_options(${PROJECT_NAME} PRIVATE
	$<$<CONFIG:Debug>:-DTEMPEST_DEBUG -Wshadow -Wall -g -fsignaling-nans -fnon-call-exceptions -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC>
	$<$<CONFIG:Debug>:${SANITIZER_FLAGS}>
	$<$<CONFIG:Release>:-O3>
)

target_link_options(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:${SANITIZER_FLAGS}>
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
	TEMPEST_VERSION="${PROJECT_VERSION}"
)
