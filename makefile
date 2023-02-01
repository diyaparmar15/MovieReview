movieReview: movieReview.o main.o
	gcc -Wall -std=c99 movieReview.o main.o -o movieReview
movieReview.o: movieReview.c movieReview.h
	gcc -Wall -std=c99 -c movieReview.c
main.o: main.c movieReview.h
	gcc -Wall -std=c99 -c main.c
clean:
	rm *.o movieReview