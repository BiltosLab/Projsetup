CC = gcc




all:
	$(CC) ./src/Projsetup.c -o ./build/Projsetup


clean:
	rm -rf ./build/*
	touch ./build/.keep