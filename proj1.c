// IZP Projekt 1
// Mario Harvan
// xharva03

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define STRLENGTH 101

int searchForNumber(char firstChar);

int searchForMatch(char *searchedString, int countSearchedString, char entries[STRLENGTH][STRLENGTH], int entryStringCount);

int printContact (int entryStringCount, char entries[STRLENGTH][STRLENGTH]);

int main(int argc, char *argv[]){   
    char entries[STRLENGTH][STRLENGTH];
    char searchedString[STRLENGTH];
    int countsearchedString = 0;
    int countMatchedContacts = 0;
    int correctInput = 0;
    int checkInput = 0;
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
        for(int i = 0; argv[1][i] != '\0';i++){
            checkInput = searchForNumber(argv[1][i]);
            // if argument is valid
            if (checkInput == 1 && countsearchedString < STRLENGTH){
                searchedString[i] = argv[1][i];
                countsearchedString++;
            }
            // if argument is invalid, break
            if (checkInput == 0 || countsearchedString >= STRLENGTH) {
                correctInput = -1;
            }
        }
    }
    int checkForEOF = 0;
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
    //bad states
    if(countMatchedContacts == 0 && correctInput != -1){
        fprintf(stdout, "Not found\n");     
    }
    if(correctInput == -1){
        fprintf(stderr, "Wrong Input\n");
    }
    return 0;
}

int searchForNumber(char firstChar){
    if (firstChar >= '0' && firstChar <= '9'){
        return 1; //number
    }
    else {
        return 0; //char
    }
}

int searchForMatch(char *searchedString, int countSearchedString, char entries[STRLENGTH][STRLENGTH], int entryStringCount){
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
        int strLength = strlen(entries[entryIndex]);
        for (int i = 0; i < strLength; i++){
            isNumber = searchForNumber(entries[entryIndex][i]);
            //if current char is character
            if (isNumber == 0){
                //find match for every char represented by searched number
                for (int j = 0; j < countLettersByNumbers; j++){
                    char lowerChar = tolower(entries[entryIndex][i]);
                    //convert char number to int
                    searchedNumber = searchedString[matchCount] - '0';
                    if (lettersByNumbers[searchedNumber][j] == lowerChar){
                        matchCount++;
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
            if (matchCount == countSearchedString){
            return 1;
            }
        }
    }
    return -1;
}

int printContact (int entryStringCount, char entries[STRLENGTH][STRLENGTH]){
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