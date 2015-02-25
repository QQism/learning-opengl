cmake_minimum_required(VERSION 3.1)
project("OpenGL Demo")

SET(GCC_COVERAGE_LINK_FLAGS    "-lsdl2 -lsdl2_image -framework OpenGL -framework CoreFoundation")

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}" )
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH})

include_directories(
    ${CMAKE_INSTALL_PREFIX}/include
    ${CMAKE_SOURCE_DIR}/src
    )

MESSAGE(ENV{LIBRARY_PATH})

set(GAME_SRC
    src/main.cpp
    src/exercises.h
    src/exercise01.cpp
    src/exercise02.cpp
    src/exercise03.cpp
    src/exercise04.cpp
    src/exercise05.cpp
    src/exercise06.cpp
    src/exercise07.cpp
    src/exercise08.cpp
    src/exercise09.cpp
    src/exercise10.cpp
    src/exercise11.cpp

    src/helper.h
    src/helper.cpp


    src/soil/SOIL.h
    src/soil/SOIL.c

    src/soil/image_DXT.h
    src/soil/image_DXT.c

    src/soil/image_helper.h
    src/soil/image_helper.c

    src/soil/stb_image_aug.h
    src/soil/stb_image_aug.c

    src/soil/stbi_DDS_aug_c.h
    src/soil/stbi_DDS_aug.h
    )

add_executable(opengldemo ${GAME_SRC})
