set(MY_EXECUTABLE_SOURCES
    main.cpp
)
add_executable(my_executable ${MY_EXECUTABLE_SOURCES})

target_link_libraries(my_executable PRIVATE cvdetection)