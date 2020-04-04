# Number or string input - button - computation - single-line-output
add_executable(cube_computation cube_computation.cpp)
target_link_libraries(cube_computation PRIVATE minGL)

# Number or string input - button - computation - multi-line-output
add_executable(dividers dividers.cpp)
target_link_libraries(dividers PRIVATE minGL)

# Generate 2D shaped graphic output depending on some input in edit boxes, define or random choice of color
add_executable(random_circles random_circles.cpp)
target_link_libraries(random_circles PRIVATE minGL)

# Left or right mouse click on canvas - handle information of the click - draw some 2D shape
add_executable(canvas canvas.cpp)
target_link_libraries(canvas PRIVATE minGL)
