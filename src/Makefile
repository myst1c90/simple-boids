TARGET = test
LIBS = -lglut -lGLU -lGL -lXext -lX11 -lm
FLAGS = -Wall
CC = gcc
CPP = g++

all: quat.o vector.h color.o entity.o bird.o boids.o color.o vector.h image_DXT.o image_helper.o SOIL.o stb_image_aug.o glTexture.o glEntities.o main.o
	$(CPP) backend/quat/quat.o backend/color.o backend/entity.o backend/bird.o backend/boids.o \
		frontend/stb_image_aug.o frontend/image_helper.o frontend/image_DXT.o frontend/SOIL.o frontend/glTexture.o frontend/glEntities.o \
		frontend/main.o \
		$(FLAGS) $(LIBS) -o $(TARGET)


#	MAIN

main.o: frontend/main.h frontend/main.cpp
	$(CPP) -c $(FLAGS) frontend/main.cpp -o frontend/main.o


# 	BACKEND

quat.o: backend/quat/quat.h backend/quat/quat.cpp
	$(CPP) -c $(FLAGS) backend/quat/quat.cpp -o backend/quat/quat.o

vector.h: backend/vector.h
	
color.o: backend/color.h backend/color.cpp
	$(CPP) -c $(FLAGS) backend/color.cpp -o backend/color.o

entity.o: backend/entity.h backend/entity.cpp
	$(CPP) -c $(FLAGS) backend/entity.cpp -o backend/entity.o

bird.o: backend/bird.h backend/bird.cpp
	$(CPP) -c $(FLAGS) backend/bird.cpp -o backend/bird.o

boids.o: backend/boids.h backend/boids.cpp
	$(CPP) -c $(FLAGS) backend/boids.cpp -o backend/boids.o
	
		
# 	FRONTEND

glEntities.o: frontend/glEntities.cpp
	$(CPP) -c $(FLAGS) frontend/glEntities.cpp -o frontend/glEntities.o

glTexture.o: frontend/glTexture.cpp
	$(CPP) -c $(FLAGS) frontend/glTexture.cpp -o frontend/glTexture.o

SOIL.o: frontend/soil/SOIL.c
	$(CC) -c $(FLAGS) frontend/soil/SOIL.c -o frontend/SOIL.o

image_DXT.o: frontend/soil/image_DXT.c 
	$(CC) -c $(FLAGS) frontend/soil/image_DXT.c -o frontend/image_DXT.o 

image_helper.o: frontend/soil/image_helper.c 
	$(CC) -c $(FLAGS) frontend/soil/image_helper.c -o frontend/image_helper.o

stb_image_aug.o: frontend/soil/stb_image_aug.c
	$(CC) -c $(FLAGS) frontend/soil/stb_image_aug.c -o frontend/stb_image_aug.o
	


clean:
	rm -f *.o $(TARGET) *~ .*.swp \
		frontend/*.o frontend/*~ frontend/*.swp \
		backend/*.o backend/*~ backend/*.swp \
		backend/quat/*.o backend/quat/*~ backend/quat/*.swp


