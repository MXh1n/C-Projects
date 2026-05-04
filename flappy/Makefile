CFLAGS = -Wall -Wextra -Iinclude 
RAY_FLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 
	
SRC = obj/main.o obj/init.o obj/movement.o obj/sound.o obj/render.o obj/state.o

# build rules
exe: $(SRC)
	@mkdir -p bin	
	gcc -o bin/game $(SRC) $(CFLAGS) $(RAY_FLAGS)

obj/%.o: src/%.c
	@mkdir -p obj
	gcc -c $< -o $@ $(CFLAGS)

run: exe
	./bin/game

# additional
clean:
	rm -rf bin obj
