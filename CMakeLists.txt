cmake_minimum_required(VERSION 3.12)
project(minGL)

set(CMAKE_CXX_STANDARD 14)

add_executable(libgraphics main.cpp include.h)

add_subdirectory(Graphics)

target_include_directories(libgraphics PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/gdiplus>
        $<INSTALL_INTERFACE:include/gdiplus>)
target_link_libraries(libgraphics gdiplus)

#target_link_libraries(minGL PUBLIC )
#target_include_directories(minGL PUBLIC "C:\\cygwin64\\usr\\include\\w32api\\gdiplus")
#target_link_libraries(minGL kernel32.lib)
#target_link_libraries(minGL user32.lib)
#target_link_libraries(minGL gdi32.lib)
#target_link_libraries(minGL winspool.lib)
#target_link_libraries(minGL comdlg32.lib)
#target_link_libraries(minGL advapi32.lib)
#target_link_libraries(minGL shell32.lib)
#target_link_libraries(minGL ole32.lib)
#target_link_libraries(minGL oleaut32.lib)
#target_link_libraries(minGL uuid.lib)
#target_link_libraries(minGL odbc32.lib)
#target_link_libraries(minGL odbccp32.lib)

