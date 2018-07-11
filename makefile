blockchain: blockchain.cpp argon2/libargon2.a argon2/argon2.h
	g++ -o blockchain blockchain.cpp argon2/libargon2.a -Isrc -Wall -g -std=c++11
