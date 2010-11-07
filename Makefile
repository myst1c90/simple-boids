TARGET = test
LIBS = -lglut -lGLU -lGL -lXext -lX11 -lm
FLAGS = -Wall
CC = gcc
CPP = g++

all: test.o color.o vector.h color.o vector.h image_DXT.o image_helper.o SOIL.o stb_image_aug.o glTexture.o
	$(CPP) test.o color.o image_DXT.o image_helper.o SOIL.o stb_image_aug.o glTexture.o $(FLAGS) $(LIBS) -o $(TARGET)


test.o: test.h test.cpp vector.h
	$(CPP) $(FLAGS) test.cpp -c
	
color.o: color.h color.cpp
	$(CPP) $(FLAGS) color.cpp -c
	
		
# 	SOIL - texture

glTexture.o: glTexture.cpp
	$(CPP) -c $(FLAGS) glTexture.cpp -o glTexture.o

SOIL.o: soil/SOIL.c
	$(CC) -c $(FLAGS) soil/SOIL.c 

image_DXT.o: soil/image_DXT.c 
	$(CC) -c $(FLAGS) soil/image_DXT.c 

image_helper.o: soil/image_helper.c 
	$(CC) -c $(FLAGS) soil/image_helper.c 

stb_image_aug.o: soil/stb_image_aug.c
	$(CC) -c $(FLAGS) soil/stb_image_aug.c
	

clean:
	-rm -f *.o $(TARGET) *~ .*.swp
