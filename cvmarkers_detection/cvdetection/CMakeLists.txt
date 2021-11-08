find_package( OpenCV REQUIRED )

set(CAMERA_SOURCES
    src/camera.cpp
    src/marker.cpp
)

add_library(cvdetection STATIC ${CAMERA_SOURCES})

include_directories( ${OpenCV_INCLUDE_DIRS} )

target_include_directories(cvdetection PUBLIC include)
target_link_libraries(cvdetection ${OpenCV_LIBS})