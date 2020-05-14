all: main

main: main.o ToleranceCheck.o ToleranceCheckDatabase.o ToleranceCheckHash.o Validation.o logger.o
	g++ -o main main.o ToleranceCheck.o ToleranceCheckDatabase.o ToleranceCheckHash.o Validation.o logger.o 

main.o: main.cpp logger.hpp ToleranceCheck.hpp ToleranceCheckDatabase.hpp
	g++ -c main.cpp

ToleranceCheck.o: ToleranceCheck.cpp ToleranceCheck.hpp ToleranceCheckDatabase.hpp
	g++ -c ToleranceCheck.cpp

ToleranceCheckDatabase.o: ToleranceCheckDatabase.cpp ToleranceCheckDatabase.hpp ToleranceCheckHash.hpp Validation.hpp
	g++ -c ToleranceCheckDatabase.cpp

ToleranceCheckHash.o: ToleranceCheckHash.cpp ToleranceCheckHash.hpp Validation.hpp
	g++ -c ToleranceCheckHash.cpp

Validation.o: Validation.cpp Validation.hpp
	g++ -c Validation.cpp	

logger.o: logger.cpp logger.hpp
	g++ -c logger.cpp

clean:
	rm main.o ToleranceCheck.o ToleranceCheckDatabase.o ToleranceCheckHash.o validation.o logger.o