add_subdirectory(graphics)

add_library(minGL mingl/mingl.h mingl/basewindow.hpp mingl/message.hpp mingl/messagehandler.hpp mingl/window.hpp)

target_link_libraries(minGL PRIVATE gdiplus)
set_target_properties(minGL PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(minGL PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
