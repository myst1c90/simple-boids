TARGET = test
LIBS = -lglut -lGLU -lGL -lXext -lX11 -lm
FLAGS = -Wall
CC = gcc
CPP = g++

all: test.o color.o vector.h color.o vector.h image_DXT.o image_helper.o SOIL.o stb_image_aug.o glTexture.o
	$(CPP) frontend/stb_image_aug.o frontend/image_helper.o frontend/image_DXT.o frontend/SOIL.o frontend/glTexture.o \
		backend/color.o \
		frontend/test.o \
		$(FLAGS) $(LIBS) -o $(TARGET)


#	MAIN

test.o: frontend/test.h frontend/test.cpp
	$(CPP) -c $(FLAGS) frontend/test.cpp -o frontend/test.o


# 	BACKEND

vector.h: backend/vector.h
	
color.o: backend/color.h backend/color.cpp
	$(CPP) -c $(FLAGS) backend/color.cpp -o backend/color.o
	
		
# 	FRONTEND

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
		backend/*.o backend/*~ backend/*.swp 


