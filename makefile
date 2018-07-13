SRC = block.cpp list.cpp blockchain.cpp blockchain.h
CFLAGS = -g -Wall
ARGON = argon2/libargon2.a
CC = g++
TARGET = blockchain.o
STD = -std=c++11
blockchain: main.cpp $(SRC) argon2/argon2.h
	$(CC) main.cpp $(SRC) $(ARGON) $(CFLAGS) $(STD)
	mv a.out $(TARGET)
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
	rm -rf a.out.dSYM
	rm -f argon2/*.gch
	rm -f json/*.gch
