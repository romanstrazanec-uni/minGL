# lib/CMakeLists.txt

set(fileglob *.*)
set(graphics "${CMAKE_CURRENT_SOURCE_DIR}/graphics")
set(gui "${CMAKE_CURRENT_SOURCE_DIR}/gui")
set(messages "${CMAKE_CURRENT_SOURCE_DIR}/messages")

# get all source files
file(GLOB graphics_sources "${graphics}/${fileglob}")
file(GLOB geometry_sources "${graphics}/geometry/${fileglob}")
file(GLOB colors_sources "${graphics}/colors/${fileglob}")
file(GLOB gui_sources "${gui}/${fileglob}")
file(GLOB messages_sources "${messages}/${fileglob}")

# add minGL library
add_library(${PROJECT_NAME} mingl main ${gui_sources} ${graphics_sources} ${geometry_sources} ${colors_sources} ${messages_sources})
target_link_libraries(${PROJECT_NAME} gdiplus)
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# remove unused variables
unset(graphics)
unset(gui)
unset(messages)

unset(graphics_sources)
unset(geometry_sources)
unset(colors_sources)
unset(gui_sources)
unset(messages_sources)
