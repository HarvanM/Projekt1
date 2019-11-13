// IZP Projekt 1
// Mario Harvan
// xharva03

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define STRLENGTH 101

int copyArgString(char *argv[], int *countsearchedString, char *searchedString);

int searchForNumber(char firstChar);

int scanAndPrintContacts(int correctInput, char *searchedString, int *countsearchedString);

int searchForMatch(char *searchedString, int *countSearchedString, char entries[STRLENGTH][STRLENGTH], int entryStringCount);

int printContact (int entryStringCount, char entries[STRLENGTH][STRLENGTH]);

int main(int argc, char *argv[]){
    char searchedString[STRLENGTH];
    int countsearchedString = 0;
    int countMatchedContacts = 0;
    int correctInput = 0;
    //Checks for correct input
    if (argc == 1){
        correctInput = 0; //no valid arguments, print everything
    }
    else if (argc == 2){
        correctInput = 1; //one valid argument, continue
    }
    else {
        correctInput = -1; //too many arguments, break
    }
    //copy argument for search
    if (correctInput == 1){
        correctInput = copyArgString(argv, &countsearchedString, searchedString);
    }
    //call for main function
    countMatchedContacts = scanAndPrintContacts(correctInput, searchedString, &countsearchedString);
    
    //bad states
    if(countMatchedContacts == 0 && correctInput != -1){
        fprintf(stdout, "Not found\n");
    }
    if(correctInput == -1){
        fprintf(stderr, "Wrong Input\n");
    }
    return 0;
}
int copyArgString(char *argv[], int *countsearchedString, char *searchedString){
    //check if input argumment is correct, if yes, copy it to string
    //argv = input argument
    //countsearchedString = number of chars in searches string
    //searchedString = string to store input argument
    //returns 1 when argument is valid and its stored into searchedString
    //returns -1 when argument is invalid

    for(int i = 0; argv[1][i] != '\0';i++){
        int checkInput = searchForNumber(argv[1][i]);
        // if argument is valid
        if (checkInput == 1 && *countsearchedString < STRLENGTH){
            searchedString[i] = argv[1][i];
            *countsearchedString += 1;
        }
        // if argument is invalid, break
        if (checkInput == 0 || *countsearchedString >= STRLENGTH) {
            return -1;
        }
    }
    return 1;
}

int scanAndPrintContacts(int correctInput, char *searchedString, int *countsearchedString){
    //scan contacts from stdin, search for matching contacts and print them
    //correctInput = states of correct input, if == 1, function work normaly, if == 0, function will print everything from stdin formated
    //searchedString = string which we want to compare
    //countsearchedString = count of chars in searchedString
    //returns number of matched and printed contacts

    char entries[STRLENGTH][STRLENGTH];
    int checkForEOF = 0;
    int countMatchedContacts = 0;
    while(checkForEOF != 1 && correctInput != -1){
        int contactWasFound = 0;
        int entryStringCount = 0;
        //scan contact to entry
        for (int i = 0; entryStringCount != 2 && checkForEOF != 1; i++){
            if (fgets(entries[i], STRLENGTH - 1, stdin) != NULL){
                entryStringCount++;
            }
            else {
                checkForEOF = 1;
            }
        }
        //if there is correct input 
        if (correctInput != -1 && checkForEOF != 1){
            //search for match
            if (correctInput == 1){
                contactWasFound = searchForMatch(searchedString, countsearchedString, entries, entryStringCount);
            }
            //print matched contact
            if (contactWasFound == 1 || correctInput == 0){
                printContact(entryStringCount, entries);
                countMatchedContacts++;
            }
        }
    }
    return countMatchedContacts;
}

int searchForNumber(char firstChar){
    //search for number
    //firstChar = char that we want to check
    //returns 1 if its number
    //returns 0 if its char
    if (firstChar >= '0' && firstChar <= '9'){
        return 1; //number
    }
    else {
        return 0; //char
    }
}

int searchForMatch(char *searchedString, int *countSearchedString, char entries[STRLENGTH][STRLENGTH], int entryStringCount){
    //check if contact is matching input parameter
    //searchedString = input parameter
    //countSearchedString = count of chars in searchedString
    //entries = array of entries from stdin
    //entryStringCount = count of entries in entries
    // returns 1 when match was found
    // returns -1 when no match was found
    const int countLettersByNumbers = 4;
    char lettersByNumbers[10][4] = {
        {'+'}, //0
        {'\0'}, //1
        {'a','b','c'}, //2
        {'d','e','f'}, //3
        {'g','h','i'}, //4
        {'j','k','l'}, //5
        {'m','n','o'}, //6
        {'p','q','r','s'}, //7
        {'t','u','v'}, //8
        {'w', 'x', 'y', 'z'} //9
    };
    int searchedNumber = 0;
    int isNumber = 0;
    for (int entryIndex = 0; entryIndex < entryStringCount; entryIndex++){
        int matchCount = 0;
        int entryLength = strlen(entries[entryIndex]);
        if (entryStringCount <= entryLength){
            for (int i = 0; i < entryLength; i++){
                isNumber = searchForNumber(entries[entryIndex][i]);
                //if current char is character
                if (isNumber == 0){
                    char lowerChar = tolower(entries[entryIndex][i]);
                    //convert char number to int
                    searchedNumber = searchedString[matchCount] - '0';
                    //find match for every char represented by searched number
                    for (int j = 0; j < countLettersByNumbers; j++){
                        if (lettersByNumbers[searchedNumber][j] == lowerChar){
                            matchCount++;
                            break;
                        }
                    }
                }
                //if current char is number
                if(isNumber == 1){
                    if (searchedString[matchCount] == entries[entryIndex][i]){
                        matchCount++;
                    }
                }
                //if there is valid match
                if (matchCount == *countSearchedString){
                return 1;
                }
            }
        }
    }
    return -1;
}

int printContact (int entryStringCount, char entries[STRLENGTH][STRLENGTH]){
    //prints contact
    //entries = array of entries from stdin
    //entryStringCount = count of entries in entries
    //returns 0 when its done
    for(int i = 0; i < entryStringCount; i++){
        int entryLength = strlen(entries[i]);
        //delete end of line chars
        for(int j = 0; j <= entryLength; j++){
            if (entries[i][j] == '\n'){
                entries[i][j] = '\0';
            }
        }
    }
    //print contact
    printf("%s",entries[0]);
    printf(", %s\n",entries[1]);
    return 0;
}