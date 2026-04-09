CXX     = g++
SRCS    = frogger.cpp frog.cpp obstacle.cpp
TARGET  = frogger

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
    LIBS = -framework OpenGL -framework GLUT
else
    LIBS = -lGL -lGLU -lglut
endif

$(TARGET): $(SRCS)
	$(CXX) -o $(TARGET) $(SRCS) $(LIBS)

clean:
	rm -f $(TARGET)
