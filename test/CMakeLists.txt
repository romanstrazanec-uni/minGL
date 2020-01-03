# GDIPLUS test
add_executable(test_gdi_plus test_gdi_plus.cpp)
target_link_libraries(test_gdi_plus PRIVATE gdiplus)

# Simple Window test
add_executable(test_simple_window test_simple_window.cpp)
target_link_libraries(test_simple_window PRIVATE minGL)

# Regular command line test
add_executable(test test_cli.cpp)
target_link_libraries(test PRIVATE minGL)

# Windows apps with win32api
add_executable(test_windows_api test_windows_api.cpp)
add_executable(test_windows_api_app test_windows_api_app.cpp)
add_executable(test_windows_api_app_with_mingl test_windows_api_app_with_mingl.cpp)
target_link_libraries(test_windows_api_app_with_mingl PRIVATE minGL)

# Mouse interaction application test
add_executable(test_mouse_interaction test_mouse_interaction.cpp)
target_link_libraries(test_mouse_interaction PRIVATE minGL)
