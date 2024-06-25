CC = clang++ -std=c++20

LINKER_FLAGS = -lsockpp -ltinycbor -lcpr

all: client server

server: server.o cbor.o wms.o osm_api.o
	$(CC) server.o cbor.o wms.o osm_api.o -o server $(LINKER_FLAGS)
client: client.o cbor.o wms.o
	$(CC) client.o cbor.o wms.o -o client $(LINKER_FLAGS)

server.o: server.cpp
	$(CC) server.cpp -c
client.o: client.cpp
	$(CC) client.cpp -c
cbor.o: cbor.cpp
	$(CC) cbor.cpp -c
wms.o: wms.cpp
	$(CC) wms.cpp -c
osm_api.o: osm_api.cpp
	$(CC) osm_api.cpp -c

clean:
	rm -rf *~* server client *\#* *.o
