CXX = g++
CXXFLAGS = -g -std=c++11 -pedantic

server: server.cpp
	$(CXX) $(CXXFLAGS) server.cpp -o server

client: client.cpp
	$(CXX) $(CXXFLAGS) client.cpp -o client

clean:
	rm client server

.PHONY: clean
