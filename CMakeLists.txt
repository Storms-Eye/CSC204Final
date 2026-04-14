cmake_minimum_required(VERSION 3.10)
project(FroggerProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(SRCS 
    frogger.cpp 
    frog.cpp 
)

# Create the executable target
add_executable(frogger ${SRCS})

if(APPLE)
    target_link_libraries(frogger PRIVATE
        OpenGL::GL
        GLUT::GLUT
        "-framework OpenGL"
        "-framework GLUT"
    )
else()
    target_link_libraries(frogger PRIVATE
        OpenGL::GL
        OpenGL::GLU
        GLUT::GLUT
    )
endif()
