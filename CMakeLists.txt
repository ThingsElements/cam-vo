cmake_minimum_required(VERSION 2.8)
project( cam-vo )
find_package( OpenCV 3.0 REQUIRED )

include_directories( ${OpenCV_INCLUDE_DIRS} )

file(GLOB viso
        "src/*.cpp"
        )
add_executable( vo ${viso} src/common.h src/mono-vo.h src/odometer.cpp src/odometer.hpp src/camera.cpp src/camera.hpp src/playback.cpp src/playback.hpp)
target_link_libraries( vo ${OpenCV_LIBS} )