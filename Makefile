CC = gcc




all:
	gcc ./src/Projsetup.c -o ./build/Projsetup


clean:
	rm -rf ./build/*
	touch ./build/.keep