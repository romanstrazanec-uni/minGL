cmake_minimum_required(VERSION 3.12)
project(libgraphics)

set(CMAKE_CXX_STANDARD 14)

add_executable(libgraphics main.cpp include.h)
target_include_directories(libgraphics PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/gdiplus>
        $<INSTALL_INTERFACE:include/gdiplus>)
target_link_libraries(libgraphics gdiplus)

#target_link_libraries(libgraphics PUBLIC )
#target_include_directories(libgraphics PUBLIC "C:\\cygwin64\\usr\\include\\w32api\\gdiplus")
#target_link_libraries(libgraphics kernel32.lib)
#target_link_libraries(libgraphics user32.lib)
#target_link_libraries(libgraphics gdi32.lib)
#target_link_libraries(libgraphics winspool.lib)
#target_link_libraries(libgraphics comdlg32.lib)
#target_link_libraries(libgraphics advapi32.lib)
#target_link_libraries(libgraphics shell32.lib)
#target_link_libraries(libgraphics ole32.lib)
#target_link_libraries(libgraphics oleaut32.lib)
#target_link_libraries(libgraphics uuid.lib)
#target_link_libraries(libgraphics odbc32.lib)
#target_link_libraries(libgraphics odbccp32.lib)

