cmake_minimum_required(VERSION "3.5.1")
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

project("Example Project" CXX C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default to RelWithDebInfo
if(NOT CMAKE_BUILD_TYPE)
  message(WARNING "CMAKE_BUILD_TYPE not set; setting to RelWithDebInfo")
  set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()

# Setup Git submodules
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()

if(MSVC)
    add_definitions(-DUSE_SSE2=1)  # error C3861
    add_compile_options("$<$<CONFIG:DEBUG>:/MDd>")  # error LNK2038
endif()

# Disable CUDA for Marian by default
set(COMPILE_CUDA OFF CACHE BOOL "Compile GPU version")

# Project
message(STATUS "Project name: ${PROJECT_NAME}")

add_subdirectory(3rd_party)
add_subdirectory(src)


# Example executable
add_executable(example src/main.cpp)
target_link_libraries(example marian)
target_include_directories(example
    PUBLIC ${PROJECT_SOURCE_DIR}
           ${PROJECT_SOURCE_DIR}/src)
