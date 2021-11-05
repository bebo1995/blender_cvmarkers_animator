cmake_minimum_required(VERSION 3.0.0)
project(cvmarkers_detection VERSION 0.1.0)

find_package( OpenCV REQUIRED )

include(CTest)
enable_testing()

add_executable(cvmarkers_detection cvmarkers_detection/main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

include_directories( ${OpenCV_INCLUDE_DIRS} )

target_link_libraries( cvmarkers_detection ${OpenCV_LIBS} )

