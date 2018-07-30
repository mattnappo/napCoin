SRC = list.cpp blockchain.cpp hasher.cpp
HEADERS = main.h argon2/argon2.h
CFLAGS = -g -Wall
CC = g++
STD = -std=c++11
THREADING = -lboost_thread-mt -lboost_system-mt -pthread
blockchain: $(SRC) $(HEADERS)
	$(CC) $(SRC) $(ARGON) $(CFLAGS) $(STD) $(TARGET)
node: node.cpp
	$(CC) node.cpp -03 $(STD) $(THREADING) -o $@
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