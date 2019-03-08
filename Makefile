$(shell mkdir -p PGM_OUT)
$(shell mkdir -p bin)
bin/convert.out: src/main.cpp src/RAW2PGM.cpp src/RAW2PGM.h
	g++ -o bin/convert.out src/main.cpp src/RAW2PGM.cpp src/RAW2PGM.h -pedantic -Wall

clean: 
	rm -rf -f PGM_OUT
	rm -rf -f bin