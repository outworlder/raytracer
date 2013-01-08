CC=g++
FLAGS=-g

raytracer : tracer.o phong.o GLScreen.o GLPreview.o sphere.o quad.o plane.o main.o
	$(CC) tracer.o phong.o GLScreen.o GLPreview.o sphere.o quad.o plane.o main.o $(FLAGS) -Wall -lm -lglut -lGL -lGLU -lstdc++ -o tracer

tracer.o : tracer.cc tracer.hpp
	$(CC) $(FLAGS) -c tracer.cc
phong.o : phong.cc phong.hpp
	$(CC) $(FLAGS) -c phong.cc
GLScreen.o : GLScreen.cc GLScreen.hpp
	$(CC) $(FLAGS) -c GLScreen.cc
sphere.o : sphere.cc sphere.hpp
	$(CC) $(FLAGS) -c sphere.cc
plane.o : plane.cc plane.hpp
	$(CC) $(FLAGS) -c plane.cc
quad.o : plane.cc quad.cc quad.hpp
	$(CC) $(FLAGS) -c quad.cc
GLPreview.o : GLPreview.cc GLPreview.hpp
	$(CC) $(FLAGS) -c GLPreview.cc
main.o : main.cc
	$(CC) $(FLAGS) -g -c main.cc

clean:
	rm *.o

