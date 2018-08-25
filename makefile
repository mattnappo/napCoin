SRC = list.cpp blockchain.cpp hasher.cpp transaction_list.cpp
HEADERS = napcoin.h argon2/argon2.h
LIBS = argon2/libargon2.a
CFLAGS = -g -Wall
CC = g++
STD = -std=c++11
THREADING = -lboost_thread-mt -lboost_system-mt -pthread

blockchain.out: main.cpp $(SRC) $(HEADERS)
	$(CC) main.cpp $(SRC) $(LIBS) $(CFLAGS) $(STD) -o $@

miner.out: miner.cpp $(SRC) $(HEADERS)
	$(CC) miner.cpp $(SRC) $(THREADING) $(STD) -o $@

test.out: test.cpp transaction_list.cpp napcoin.h
	$(CC) test.cpp transaction_list.cpp $(STD) -o $@

json: json/json.hpp
	$(CC) json/json.hpp $(CFLAGS) $(STD)

argon2: argon2/argon2.h
	gcc argon2/argon2.h $(CFLAGS)

clean:
	rm -f *.gch
	rm -f *.out
	rm -f *.o
	rm -f *.exe
	rm -rf *.dSYM
	rm -f argon2/*.gch
	rm -f json/*.gch
