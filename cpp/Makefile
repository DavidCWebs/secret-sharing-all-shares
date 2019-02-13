split: split.cpp Secret.cpp Secret.h utility.cpp utility.hpp
	g++ -std=c++11 -o bin/split split.cpp Secret.cpp utility.cpp `libgcrypt-config --cflags --libs`

combine: combine.cpp Shares.cpp Shares.h
	g++ -std=c++11 -o bin/combine combine.cpp Shares.cpp utility.cpp
