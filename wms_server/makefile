all: client server

server: server.o cbor.o wms.o
	clang++ server.o cbor.o wms.o -o server -lsockpp -ltinycbor
client: client.o cbor.o wms.o
	clang++ client.o cbor.o wms.o -o client -lsockpp -ltinycbor

server.o: server.cpp
	clang++ server.cpp -c
client.o: client.cpp
	clang++ client.cpp -c
cbor.o: cbor.cpp
	clang++ cbor.cpp -c
wms.o: wms.cpp
	clang++ wms.cpp -c

clean:
	rm -rf *~* server client *\#* *.o
