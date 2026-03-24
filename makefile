CC = g++
FLAGS = -Wall -std=c++17 
LINKS = -lsfml-graphics -lsfml-window -lsfml-system 

# juan = character model
# welcome = welcome screen
# game = game
# main = window and rendering 
# states = screens (quit, welcome, game, results) - only need .h file
# button = buttons 
# results = results 

game: objects/main.o objects/game.o objects/welcome.o objects/play.o objects/juan.o objects/button.o objects/results.o
	$(CC) $(FLAGS) $^ -o $@ $(LINKS)

objects/main.o: source/main.cpp header/game.h
	$(CC) $(FLAGS) -c $< -o objects/main.o

objects/game.o: source/game.cpp header/game.h header/states.h header/welcome.h header/play.h header/results.h
	$(CC) $(FLAGS) -c $< -o objects/game.o

objects/welcome.o: source/welcome.cpp header/welcome.h header/states.h header/button.h
	$(CC) $(FLAGS) -c $< -o objects/welcome.o

objects/play.o: source/play.cpp header/play.h header/states.h header/button.h header/juan.h
	$(CC) $(FLAGS) -c $< -o objects/play.o

objects/juan.o: source/juan.cpp header/juan.h 
	$(CC) $(FLAGS) -c $< -o objects/juan.o

objects/button.o: source/button.cpp header/button.h
	$(CC) $(FLAGS) -c $< -o objects/button.o

objects/results.o: source/results.cpp header/results.h header/states.h header/button.h
	$(CC) $(FLAGS) -c $< -o objects/results.o

clean:
	rm -f game objects/*.o