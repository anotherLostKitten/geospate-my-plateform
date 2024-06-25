all: client server

server: server.cpp
	clang++ server.cpp -o server -lsockpp

client: client.cpp
	clang++ client.cpp -o client -lsockpp

clean:
	rm -rf *~* server client *\#* *.o
