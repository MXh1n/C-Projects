main: obj/main.o obj/random.o
	gcc obj/main.o obj/random.o -o main

obj/main.o: main.c random.h
	gcc -c main.c -o obj/main.o
	

obj/random.o: random.c random.h
	gcc -c random.c -o obj/random.o

dir: 
	mkdir -v obj

clear:
	rm -rfv obj

	
