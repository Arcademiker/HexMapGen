cmake_minimum_required(VERSION 3.9)
project(DisplayImage)

set(CMAKE_CXX_STANDARD 11)


#set(OpenCV_DIR "~/opencv_tmp/release") #path to your opencv directory if path variable not set globaly
find_package(OpenCV REQUIRED core imgproc imgcodecs highgui)

set( 	DisplayImage_SRC
        src/main.cpp
        src/hex.cpp
        src/edge.cpp

        )

set( 	DisplayImage_HEADERS
        include/hex.h
        include/edge.h
        )

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include )
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable( DisplayImage ${DisplayImage_SRC} ${DisplayImage_HEADERS} )

target_link_libraries(DisplayImage ${OpenCV_LIBS})


