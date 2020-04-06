# lib/CMakeLists.txt

set(fileglob *.*)
set(Dmingl "${CMAKE_CURRENT_SOURCE_DIR}/minglib")
set(Dgraphics "${Dmingl}/graphics")
set(Dgui "${Dmingl}/gui")
set(Dmessages "${Dmingl}/messages")

# get all source files
file(GLOB DCgraphics "${Dgraphics}/${fileglob}")
file(GLOB DCgeometry "${Dgraphics}/geometry/${fileglob}")
file(GLOB DCcolors "${Dgraphics}/colors/${fileglob}")
file(GLOB DCgui "${Dgui}/${fileglob}")
file(GLOB DCmessages "${Dmessages}/${fileglob}")

# add minGL library
add_library(${PROJECT_NAME} mingl ${DCgui} ${DCgraphics} ${DCgeometry} ${DCcolors} ${DCmessages})
target_link_libraries(${PROJECT_NAME} PRIVATE gdiplus)
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# remove unused variables
unset(Dmingl)
unset(Dgraphics)
unset(Dgui)
unset(Dmessages)

unset(DCgraphics)
unset(DCgeometry)
unset(DCcolors)
unset(DCgui)
unset(DCmessages)
