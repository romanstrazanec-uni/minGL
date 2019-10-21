add_library(minGLgui BaseWindow.hpp Message.hpp MessageHandler.hpp Window.hpp)

set_target_properties(minGLgui PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(minGLgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
