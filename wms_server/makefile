CC = clang++ -std=c++20

LINKER_FLAGS = -lsockpp -ltinycbor -lcpr

SERVER_DEPS = server.o cbor.o wms.o osm_api.o

CLIENT_DEPS = client.o cbor.o wms.o

all: client server

server: $(SERVER_DEPS)
	$(CC) $(SERVER_DEPS) -o server $(LINKER_FLAGS)
client: $(CLIENT_DEPS)
	$(CC) $(CLIENT_DEPS) -o client $(LINKER_FLAGS)

.cpp.o:
	$(CC) -c $< -o $@

clean:
	rm -rf *~* server client *\#* *.o
