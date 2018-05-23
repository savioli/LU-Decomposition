SRC=main.cpp
PROGRAM_NAME = main

${PROGRAM_NAME}: LUDecomposition.o main.o
	g++ -o ${PROGRAM_NAME} LUDecomposition.o main.o

LUDecomposition.o: LUDecomposition.cpp
	g++ -o LUDecomposition.o -c LUDecomposition.cpp

main.o: main.cpp LUDecomposition.h
	g++ -o main.o -c main.cpp

clean:
	rm -rf *.o

mrproper: clean
	rm -rf main

run:
	@$(MAKE) && ./$(PROGRAM_NAME) $(ARGS)
