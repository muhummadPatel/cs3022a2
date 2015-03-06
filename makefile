CPP=g++
CPPFLAGS=-std=c++11
EXE_NAME=volimage

$(EXE_NAME): volImage.o driver.o 
	$(CPP) -o $(EXE_NAME) driver.o volImage.o $(CPPFLAGS)

volImage.o: volImage.cpp volImage.h
	$(CPP) -c -o volImage.o volImage.cpp $(CPPFLAGS)

driver.o: driver.cpp
	$(CPP) -c -o driver.o driver.cpp $(CPPFLAGS)

clean:
	rm -f *.o $(EXE_NAME)
