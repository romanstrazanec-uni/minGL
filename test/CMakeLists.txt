# GDIPLUS test
add_executable(test_gdi_plus test_gdi_plus.cpp)
target_link_libraries(test_gdi_plus gdiplus)

# GDIPLUS with minGL test
add_executable(test_gdi_plus_mingl test_gdi_plus_mingl.cpp)
target_link_libraries(test_gdi_plus_mingl "${PROJECT_NAME}")

# Simple Window test
add_executable(test_simple_window test_simple_window.cpp)
target_link_libraries(test_simple_window "${PROJECT_NAME}")

# Regular command line test
add_executable(test test_cli.cpp)
target_link_libraries(test "${PROJECT_NAME}")

# Windows apps with win32api
add_executable(test_windows_api test_windows_api.cpp)
add_executable(test_winapi_components test_winapi_objects.cpp)
add_executable(test_windows_api_app test_windows_api_app.cpp)

# Mouse interaction application test
add_executable(test_mouse_interaction test_mouse_interaction.cpp)
target_link_libraries(test_mouse_interaction "${PROJECT_NAME}")
