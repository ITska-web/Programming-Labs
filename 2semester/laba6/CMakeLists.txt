cmake_minimum_required(VERSION 3.10)
project(SortLib C)

option(BUILD_STATIC "Build static library" ON)
option(BUILD_DYNAMIC "Build dynamic library" OFF)

set(SOURCE_FILES bubblesort.c quicksort.c)

if(BUILD_STATIC)
   add_library(sortstatic STATIC ${SOURCE_FILES})
endif()

if(BUILD_DYNAMIC)
   add_library(sortdynamic SHARED ${SOURCE_FILES})
endif()

add_executable(main main.c)

if(BUILD_STATIC)
   target_link_libraries(main sortstatic)
endif()

if(BUILD_DYNAMIC)
   target_link_libraries(main sortdynamic)
endif()