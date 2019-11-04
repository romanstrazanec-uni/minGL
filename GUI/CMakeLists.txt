add_library(minGLgui BaseWindow.hpp Message.hpp MessageHandler.hpp Window.hpp)

target_link_libraries(minGLgui PRIVATE gdiplus)

set_target_properties(minGLgui PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(minGLgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
