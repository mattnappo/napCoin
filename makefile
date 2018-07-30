SRC = block.cpp list.cpp blockchain.cpp hasher.cpp
HEADERS = main.h argon2/argon2.h
CFLAGS = -g -Wall
CC = g++
STD = -std=c++11
ifeq ($(OS),Windows_NT)
	ARGON = Argon2OptDll.lib
	TARGET = -o blockchain.exe
else
	ARGON = argon2/libargon2.a
	TARGET = -o blockchain.o
endif
blockchain: main.cpp $(SRC) $(HEADERS)
	$(CC) main.cpp $(SRC) $(ARGON) $(CFLAGS) $(STD) $(TARGET)
node: node.cpp
	$(CC) node.cpp $(STD) -o node.o
json: json/json.hpp
	$(CC) json/json.hpp $(CFLAGS) $(STD)
argon2: argon2/argon2.h
	gcc argon2/argon2.h $(CFLAGS)
clean:
	rm -f *.gch
	rm -f *.o
	rm -f *.exe
	rm -rf *.dSYM
	rm -f argon2/*.gch
	rm -f json/*.gch
all:
	make clean
	make json
	make argon2
	make blockchain
	make node