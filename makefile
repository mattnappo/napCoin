SRC = block.cpp list.cpp blockchain.cpp hasher.cpp blockchain.h
CFLAGS = -g -Wall
CC = g++
STD = -std=c++11
ifeq ($(OS),Windows_NT)
	ARGON = Argon2RefDll.dll
	TARGET = -o blockchain.exe
else
	ARGON = argon2/libargon2.a
	TARGET = -o blockchain.o
endif
blockchain: main.cpp $(SRC) argon2/argon2.h
	$(CC) main.cpp $(SRC) $(ARGON) $(CFLAGS) $(STD) $(TARGET)
json: json/json.hpp
	$(CC) json/json.hpp $(CFLAGS) $(STD)
argon2: argon2/argon2.h
	gcc argon2/argon2.h $(CFLAGS)
all:
	make json
	make argon2
	make blockchain
clean:
	rm -f *.gch
	rm -f *.o
	rm -f *.exe
	rm -rf a.out.dSYM
	rm -f argon2/*.gch
	rm -f json/*.gch
