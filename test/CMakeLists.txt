# GDIPLUS test
add_executable(test_gdi_plus test_gdi_plus.cpp)
target_link_libraries(test_gdi_plus PRIVATE gdiplus)

# Simple Window test
add_executable(test_simple_window test_simple_window.cpp)
target_link_libraries(test_simple_window PRIVATE minGL)
