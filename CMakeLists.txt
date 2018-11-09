cmake_minimum_required(VERSION 3.5.1)
project(file_safe)
add_definitions(-std=c++11)
#set(BOOST_ROOT $ENV{HOME}/opt/boost/)
#set(BOOST_COMPONENTS system thread program_options)
#set(BOOST_INCLUDEDIR $ENV{HOME}/opt/boost/include)
#find_package(Boost REQUIRED COMPONENTS ${BOOST_COMPONENTS})
#add_subdirectory(util)
#add_subdirectory(tcp-client)
#add_subdirectory(tcp-server)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)
#include_directories(${BOOST_INCLUDEDIR} ${PROJECT_SOURCE_DIR}/util/include )
include_directories( ${PROJECT_SOURCE_DIR}/include )
set( source_dir ${PROJECT_SOURCE_DIR}/src )
set( source_file ${source_dir}/block_content.cpp
                  ${source_dir}/block_header.cpp
                  ${source_dir}/block_tail.cpp
                  ${source_dir}/block.cpp
                  ${source_dir}/crypt.cpp
                  ${source_dir}/file_header.cpp
                  ${source_dir}/sha2.c  
                  )
add_executable(file_safe main.cpp ${source_file})
#target_link_libraries(tcp-client ${Boost_LIBRARIES})