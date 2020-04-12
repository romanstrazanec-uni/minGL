# Number or string input - button - computation - single-line-output
add_executable(cube_computation WIN32 cube_computation.cpp)
target_link_libraries(cube_computation PRIVATE ${PROJECT_NAME})

# Number or string input - button - computation - multi-line-output
add_executable(dividers WIN32 dividers.cpp)
target_link_libraries(dividers PRIVATE ${PROJECT_NAME})

# Generate 2D shaped graphic output depending on some input in edit boxes, define or random choice of color
add_executable(random_circles WIN32 random_circles.cpp)
target_link_libraries(random_circles PRIVATE ${PROJECT_NAME})

# Left or right mouse click on canvas - handle information of the click - draw some 2D shape
add_executable(canvas WIN32 canvas.cpp)
target_link_libraries(canvas PRIVATE ${PROJECT_NAME})
