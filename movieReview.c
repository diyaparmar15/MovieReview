
#include <stdbool.h>
#include "movieReview.h"


/*
Function 1: This function will take in a filename as a string and attempt to create a FILE pointer out 
of it. If the file opens successfully, a FILE pointer will be returned. Otherwise, NULL. You 
will only open the file for reading, not writing. 
*/
FILE *openFileForReading(char *fileName){
    
     //file pointer  
     FILE* file;
	 file = fopen(fileName, "r");

    //if the file is NULL is, display an error message 
    if(file == NULL)
    {
        printf("Error, file is unable to open");
    }
    //return the file pointer
    return file;
}

/*
Function 2: This function will read movie titles from a FILE pointer variable named file, line by line, 
into the movieNames 2D array. The function will either return 1 (to indicate successful 
operation) or 0 to represent abnormal exit, which can be:
*/
int readMovies(FILE *file, char movieNames[NUMBER_MOVIES][MAX_STR]){

    //variable for loop
    int i;
    i = 0;

    //error message if file is null
    if(file == NULL)
    {
        printf("Error, file is unable to open");
        return 0;
    }

    //loop through the file until the end of it to scan the movie names
    while (fscanf(file, "%[^\n] ", movieNames[i]) != EOF){
        i++;
    }
    //close the file
    fclose(file);


    //if i is equal to the number of movies expected return 1
    if(i == NUMBER_MOVIES) {
        return 1;
    }

    
    else {
        //error messages if the file is equal to 0, or less than oe greater than the expected value of NUMBER_MOVIES
        if(i == 0) {
            printf("Error, this file is empty.\n");
        }
        else if (i > NUMBER_MOVIES) {
            printf("Error, this file has more lines than expected .\n");
        }
        else if (i < NUMBER_MOVIES) {
            printf("Error, this file has less lines than expected.\n");
        }
		return 0;
    }
}


/*
Function 3: This function reads the movie reviews from the file pointer to the reviewStruct array
*/
int readReviews(FILE *file, struct reviewStruct reviews[NUMBER_REVIEWERS]){

    //if file pointer is NULL return 0
    if(file == NULL){
        printf("Error, file is unable to open");
        return 0;
    }


    //create a temp variable, checker and loop variables
    char temp[NUMBER_REVIEWERS][NUMBER_MOVIES];
    char check;
    int i = 0;
    int j = 0;


    //a while loop until the end of the file
    while(!feof(file)){


        //scan all the info from the file into the struct and increment the variable
        fscanf(file, "%s %c %c %c", reviews[i].reviewer, &temp[i][j], &temp[i][j+1], &temp[i][j+2]);
        i++;
    }


    //if number of lines read is over the expected value of NUMBER_REVIEWERS, return 0
    if(i - 1 > NUMBER_REVIEWERS ||  i - 1 < NUMBER_REVIEWERS){

        return 0;
    }

    //loop through reviewers
    for(int j = 0; j < NUMBER_REVIEWERS; j++){

        //loop through movies
        for(int k = 0; k < NUMBER_MOVIES; k++){

            //now the check is equal to the temp 
            check = temp[j][k];

            //if check equals to "Y" or "y" then add 1 to feedback
            if(check == 'y' || check == 'Y'){
                reviews[j].feedback[k] = 1;

            }

            //otherwise
            else{

                //give it a value of 0 (this means the check equals to "N" or "n")
                reviews[j].feedback[k] = 0;

            }
        }
    }
    return 1;
}


/*
Function 4: This function will find the most critical reviewers and sotre them in an array
*/
int getMostCriticalReviewers(struct reviewStruct reviews[NUMBER_REVIEWERS], char mostCriticalReviewers[NUMBER_MOVIES][MAX_STR]){

    //initialize the mnimum rating to a large value so we can find the rating
	int minimumRating = 999;

	for (int i = 0; i < NUMBER_REVIEWERS; i++) {
		int totalRating = 0;

		for (int j = 0; j < NUMBER_MOVIES; j++) {
			//total rating gets calculated by adding each rating
			totalRating = totalRating + reviews[i].feedback[j];
		}
		//if the total rating is less than the minimum rating, swap the two
		if (totalRating < minimumRating) {
			minimumRating = totalRating;
		}
	}

	int criticalReviewerNumber = 0;

	for (int i = 0; i < NUMBER_REVIEWERS; i++) {
		int totalRating = 0;

		for (int j = 0; j < NUMBER_MOVIES; j++) {
			//total rating gets calculated by adding each rating
			totalRating = totalRating + reviews[i].feedback[j];
		}

		//if the total rating equals the minimum rating, copy the found critical reviewer and increase the counter
		if (totalRating == minimumRating) {
		
			strcpy(mostCriticalReviewers[criticalReviewerNumber], reviews[i].reviewer);
			criticalReviewerNumber = criticalReviewerNumber + 1;
		}
	}
	return criticalReviewerNumber;
}

/*
Function 5: This function attains a list 
*/
int getMostRecommendedMovies(const char movieNames[NUMBER_MOVIES][MAX_STR], const struct reviewStruct reviews[NUMBER_REVIEWERS], char mostRecommendedMovies[NUMBER_MOVIES][MAX_STR]){

    int maximumRating = 0;

	for (int i = 0; i < NUMBER_MOVIES; i++) {
		// Initialize rating for individual movie title
		int totalRating = 0;
		for (int j = 0; j < NUMBER_REVIEWERS; j++) {
			totalRating = totalRating + reviews[i].feedback[j];
		}
		// Check for max rating 
		if (totalRating > maximumRating) {
			maximumRating = totalRating;
		}
	}
	//int maxRating = getRatingForMostRecommendedMovie(reviews);
	int counter = 0;
	for (int i = 0; i < NUMBER_MOVIES; i++) {
		//initialize the total rating varibale again for the movie title 
		int totalRating = 0;

		for (int j = 0; j < NUMBER_REVIEWERS; j++) {
			totalRating = totalRating + reviews[i].feedback[j];
		}

		//check if the total rating is equal to the maximum rating 
		if (totalRating == maximumRating) {
			strcpy(mostRecommendedMovies[counter], movieNames[i]);
			counter++;
		}
	}
	return counter;
}

/*
Function 6: This function predicts how well a movie will do in the future
*/
int predictMovie(const char movie[MAX_STR]){

	//variables for the word count, character count, final result and the length
    int countWords = 0;
    int countChars  = 0;
    int finalValue = 0;     
    int length = 0;               

    //counter to count the number of words
    int counter = 0;

    //loop until the null character
    for (int i = 0;movie[i] != '\0';i++){

        //if the character is equal to a space AND if it is not equal to a space, increment the counter
        if (movie[i] == ' ' && movie[i+1] != ' ')
            counter++;    
    }

    //increment the word count 
    countWords = counter + 1;

    //if word count is above 2, the final value is -1
    if(countWords > 2){
        finalValue = -1;  
    }

    //if the word count equals to 1, the final value is itself - 2
    if(countWords == 1){
        finalValue = finalValue - 2;
    }

    //loop through the length of the movie
    for(int i = 0; i < strlen(movie); i++){
      
        //if character does not equal to a space add 1 to counter
        if(movie[i] != ' '){
            countChars++;
        }
    }

    //if word count is greater than 1 with an even number of characters, add 1 to the final value
    if(countWords > 1 && (countChars%2 == 0)){
        finalValue = finalValue + 1;
    }

    //initialize word counter again
    countWords = 1;

    //counter for the first word of the movie title
    int firstWordCounter = 0;

    //character counter for each word of the movie title
    int charCounter = 0;

    //initialize the condition of the check assuming all words have the same length 
    bool sameChars = true;

    // total length including space newline and tab
     length = strlen(movie);

    
    //loop through the length of that string and calculate the number of chatacters
    for (int i = 0; i < length; i++) {

        //if movie at i is not equal to a space, newline or tab, a word has been found
        if (movie[i] == ' ' || movie[i] == '\t'|| movie[i] == '\n' ) {
            break;
        }

        else {
            firstWordCounter++;
        }
    }

    //same process occurs for the rest of the title
    for (int i = 0; i < length; i++) {
        
        //if movie at i is not equal to a space, newline or tab, a word has been found
        if (movie[i] == ' ' || movie[i] == '\t'|| movie[i] == '\n' ) {
            countWords++;

            //if the word does nit hae the same amount of characters in the first word, exit
            if (charCounter != firstWordCounter) {
                //means that at least one word from the title does not have the same amount of characters as the first
                sameChars = false;
                break;
            }
            // reset counter
            charCounter = 0;
        }
        else {
            // increment character counter
            charCounter = charCounter + 1;
        }
    }
    //if all words have the same character counter value
    if ((countWords >= 1) && sameChars) {
        return finalValue + 2;

	}
    return finalValue;
}


/*
Function 7: This function enumerates a movie title's words by counting the number of words in each title 
and count the number of letters in the word
*/
int enumerateMovie(const char movie[MAX_STR], int charCounts[MAX_WORDS]){

//variables to count the words, characters, counter and the length
    int countWords = 1;
	int charNumber = 0;
	int counter = 0;
	int length;

    //the length is equals to the length of the movie name 
    length = strlen(movie);

    //loop through the length of the movie name
	for (int i = 0; i < length; i++) {

		////if movie at i is not equal to a space, tab or newline, a word has been found
		if (movie[i] == ' ' || movie[i] == '\t'|| movie[i] == '\n' ) {

            //reset the charNumber counter so it can be used for the next word
			charCounts[counter] = charNumber;
			charNumber = 0;
            //increment the counters as the loop goes on
			countWords++;
			counter++;
		}
		else {
			charNumber = charNumber + 1;
		}
	}
	
    //if the word count and counter do not equal to each other, the char counter is equal to the number of chars which checks for a title with only 1 word
	if (countWords != counter) {
		charCounts[counter] = charNumber;
	}
	return countWords;

    }

