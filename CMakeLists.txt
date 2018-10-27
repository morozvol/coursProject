cmake_minimum_required(VERSION 3.12)
project(coursProject)

set(CMAKE_CXX_STANDARD 14)
set(TagLib_INCLUDE_DIR "C:/Clion/coursProject/taglib/include")
set(TagLib_LIBRARY_DIR "C:/Clion/coursProject/taglib/lib")
set(TagLib_DIR "C:/Clion/coursProject/taglib")
set(PROJECT_DIR "C:/Clion/coursProject")
include_directories(${PROJECT_DIR}/Headers)
include_directories(${PROJECT_DIR}/Resours)
include_directories(${PROJECT_DIR}/Sourses)

add_executable(coursProject Sourses/main.cpp Sourses/ReadTag.cpp)

include_directories(${TagLib_INCLUDE_DIR})
include_directories(${TagLib_INCLUDE_DIR}/taglib)
include_directories(${Taglib_DIR})

target_link_libraries(coursProject -L${TagLib_LIBRARY_DIR} -ltag -lz -liconv)