cmake_minimum_required(VERSION 3.10)
project(CSC204Final)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

set(SRCS 
    src/main.cpp 
    src/frog.cpp
    src/car-manager.cpp
    src/log-manager.cpp
    src/tree-manager.cpp
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
