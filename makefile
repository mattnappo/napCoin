SRC = block.cpp list.cpp blockchain.cpp blockchain.h
CFLAGS = -g -Wall -g
ARGON = argon2/libargon2.a
CC = g++
B_TARGET = blockchain.o
ISCPP = -std=c++11
blockchain: main.cpp $(SRC_FILES) argon2/argon2.h
	$(CC) main.cpp $(SRC) $(ARGON) $(CFLAGS) $(ISCPP)
	mv a.out $(B_TARGET)
argon2: argon2/argon2.h
	$(CC) argon2/argon2.h $(CFLAGS)
json: json/json.hpp
	$(CC) json/json.hpp $(CFLAGS) $(ISCPP)
clean:
	rm -f *.gch
	rm -f *.o
	rm -rf a.out.dSYM
	rm -f argon2/*.gch
	rm -f json/*.gch
