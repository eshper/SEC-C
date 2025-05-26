#add all the files that you need to the files makefile variable below as a space seperated list
files = Shader.cpp VBO.cpp VAO.cpp EBO.cpp Texture.cpp Camera.cpp Mesh.cpp Model.cpp

main: main.cpp glad.c 
	g++ -g $(files) main.cpp glad.c stb.cpp -lglfw -pthread -lGLEW -ldl -lGL -lassimp -o main 

clean:
	rm -f *.o main

run:
	./main ${recsLength} ${recsWidth}

all:
	make clean
	make
	make run

for_chris:
	mkdir -p build
	cd build && cmake .. && make && ./Assignment 

clean_for_chris:
	rm -rf build
