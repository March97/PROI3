CXX = g++  -Wall -pedantic -std=c++11

sources=main.cpp md5.cpp
headers=md5.h

debug: $(sources) $(headers)
	$(CXX) -g -DDEBUG $(sources) -o $@

md5: $(sources) $(headers)
	$(CXX) $(sources) -o $@

clean:
	rm -rf debug
	rm -rf md5
