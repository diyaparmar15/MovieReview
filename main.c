
#include "movieReview.h"

char movieNames[NUMBER_MOVIES][MAX_STR];
struct reviewStruct reviews[NUMBER_REVIEWERS];
char mostCriticalReviewers[NUMBER_REVIEWERS][MAX_STR];
char mostRecommendedMovies[NUMBER_MOVIES][MAX_STR];
int charCounts[MAX_WORDS];

int main(int argc, char* argv[]) {

    FILE* fptr;
    fptr = openFileForReading("movies.txt");
    int var = readMovies(fptr, movieNames);
    if (var == 0) {
        exit(1);
    }

    fptr = openFileForReading("reviews.txt");
    int var1 = readReviews(fptr, reviews);
    if (var1 == 0) {
       exit(1);
    }

    int numberOfCriticalReviewer = getMostCriticalReviewers(reviews, mostCriticalReviewers);

    printf("\n");
    printf("Number of critical reviewer is %d\n", numberOfCriticalReviewer);
    for (int i = 0; i < numberOfCriticalReviewer; i++) {
        printf("%s\n", mostCriticalReviewers[i]);
    }

    int count = getMostRecommendedMovies(movieNames, reviews, mostRecommendedMovies);
    printf("Number of most recommeded movie title %d\n", count);

    int predictMovieResult = predictMovie("Star Wars");
    predictMovieResult = predictMovie("Incredibles");
    predictMovieResult = predictMovie("Gone with the wind");

    char* name = "Mean Girls";
    int n = enumerateMovie(name, charCounts);
    printf("Title: %s has %d words \n", name, n);
    for (int i = 0; i < n; i++) {
        printf("character count: %d \n", charCounts[i]);
    }

    name = "Despicable";
    n = enumerateMovie(name, charCounts);
    printf("Title: %s has %d words \n", name, n);
    for (int i = 0; i < n; i++) {
        printf("word %d count: %d \n", i, charCounts[i]);
    }

    return 0;
};