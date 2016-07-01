HEADERS = Board.h debug.h utility.h types.h

types.h: types.nw
	notangle types.nw > types.h

Board.h: Board.nw
	notangle Board.nw > Board.h

Board.tex: Board.nw
	noweave -delay Board.nw > Board.tex

utility.h: utility.nw
	notangle utility.nw > utility.h

utility.o: $(HEADERS) utility.c
	gcc -c utility.c

utility_test: $(HEADERS) utility.o utility_test.c
	gcc -o utility_test utility.o utility_test.c 

Board.o: $(HEADERS) Board.c
	gcc -c Board.c

search.o: $(HEADERS) search.c
	gcc -c search.c	
