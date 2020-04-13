# Number or string input - button - computation - single-line-output
add_executable(cube WIN32 cube.cpp)
target_link_libraries(cube ${PROJECT_NAME})

# Number or string input - button - computation - multi-line-output
add_executable(dividers WIN32 dividers.cpp)
target_link_libraries(dividers ${PROJECT_NAME})

# Generate 2D shaped graphic output depending on some input in edit boxes, define or random choice of color
add_executable(circles WIN32 circles.cpp)
target_link_libraries(circles ${PROJECT_NAME})

# Left or right mouse click on canvas - handle information of the click - draw some 2D shape
add_executable(canvas WIN32 canvas.cpp)
target_link_libraries(canvas ${PROJECT_NAME})
