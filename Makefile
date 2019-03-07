bin/convert.out: src/main.cpp src/RAW2PGM.cpp src/RAW2PGM.h
	g++ -o bin/convert.out src/main.cpp src/RAW2PGM.cpp src/RAW2PGM.h -pedantic -Wall

clean: 
	rm bin/convert.out