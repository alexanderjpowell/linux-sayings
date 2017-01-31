/*****************************/
/***  Alexander Powell     ***/
/***  Systems Programming  ***/
/***  PA #2                ***/
/***  Due: 2.28.2016       ***/
/*****************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool isValueInArray(int val, int *arr, int size);
int findAllIndexes(char const *str, char const *str2);

int main(int argc, char **argv)
{
    // Parse the command line arguments
    bool bannerFlag = false;
    bool highlightFlag = false;
    int index_of_pattern;
    // commands should be formatted like: ./sayings -b(opt) -h(opt) pattern(req)
    if (argc > 4 || argc < 2)
    {
        printf("Usage: ./sayings -b -h [pattern]\n");
        printf("Note: the '-b' and '-h' flags are optional. \n");
        exit(1); // Quit the program if there are more than 4 arguments or less than 2
    }
    if (argc == 2)
    { // ./sayings pattern
        if ((strcmp(argv[1], "-b") == 0) || (strcmp(argv[1], "-h") == 0))
        {
            printf("Usage: ./sayings -b -h [pattern]\n");
            printf("Note: the '-b' and '-h' flags are optional. \n");
            exit(1);
        }
    }
    if (argc == 3)
    { // ./sayings -b pattern  OR  ./sayings -h pattern
        if (!((strcmp(argv[1], "-b") == 0) || (strcmp(argv[1], "-h") == 0)))
        {
            printf("Usage: ./sayings -b -h [pattern]\n");
            printf("Note: the '-b' and '-h' flags are optional. \n");
            exit(1);
        }
        if ((strcmp(argv[2], "-b") == 0) || (strcmp(argv[2], "-h") == 0))
        {
            printf("Usage: ./sayings -b -h [pattern]\n");
            printf("Note: the '-b' and '-h' flags are optional. \n");
            exit(1);
        }
        if (strcmp(argv[1], "-b") == 0) { bannerFlag = true; }
        if (strcmp(argv[1], "-h") == 0) { highlightFlag = true; }
    }
    if (argc == 4)
    { // ./sayings -b -h pattern  OR  ./sayings -h -b pattern
        if (strcmp(argv[1], "-b") == 0 || strcmp(argv[2], "-b") == 0) { bannerFlag = true; }
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[2], "-h") == 0) { highlightFlag = true; }
        if ((bannerFlag && highlightFlag) && (argc != 4))
        {
            printf("Usage: ./sayings -b -h [pattern]\n");
            printf("Note: the '-b' and '-h' flags are optional. \n");
            exit(1); // Something's not right with the command line arguments
        }
        if (argc == 4 && !(bannerFlag && highlightFlag))
        {
            printf("Usage: ./sayings -b -h [pattern]\n");
            printf("Note: the '-b' and '-h' flags are optional. \n");
            exit(1); // Something's not right with the command line arguments
        }
        if ((strcmp(argv[3], "-b") == 0) || (strcmp(argv[3], "-h") == 0))
        {
            printf("Usage: ./sayings -b -h [pattern]\n");
            printf("Note: the '-b' and '-h' flags are optional. \n");
            exit(1);
        }
    }
    if (argc == 2) { index_of_pattern = 1; }
    if (argc == 3) { index_of_pattern = 2; }
    if (argc == 4) { index_of_pattern = 3; }
    // finished parsing

    int i;
    int MAX_LINE_LENGTH = 4096;

    // Code for linked list taken from Kearns's notes
    char tmpstring[MAX_LINE_LENGTH];
    struct snode {
        char *str;
        struct snode *next;
    };

    struct snode *listhead = NULL;
    struct snode *listtail = NULL;
    struct snode *newnode, *ptr;

    struct snodeSayings {
        char *str;
        struct snodeSayings *next;
    };
    struct snodeSayings *listheadSayings = NULL;
    struct snodeSayings *listtailSayings = NULL;
    struct snodeSayings *newnodeSayings, *ptrSayings;

    
    int count;
    int numberOfLinesInGREP = 0;
    int numberOfFurtuneFiles = 0;

    count = 0;
    while (fgets(tmpstring, MAX_LINE_LENGTH, stdin) == tmpstring)
    {
        if ((newnode = (struct snode *)malloc(sizeof(struct snode))) == NULL)
        {
            fprintf(stderr,"mklist: malloc failure for newnode\n");
            exit(1);
        }
        if ((newnode -> str = malloc(strlen(tmpstring) + 1)) == NULL)
        {
            fprintf(stderr,"mklist: malloc failure for newnode -> str\n");
            exit(1);
        }
        if (strncpy(newnode -> str, tmpstring, strlen(tmpstring) + 1) != newnode -> str)
        {
            fprintf(stderr,"mklist: string copy problem\n");
            exit(1);
        }
        newnode -> next = NULL;
        if (listtail == NULL) { listhead = listtail = newnode; }
        else
        {
            listtail -> next = newnode;
            listtail = newnode;
        }
        numberOfLinesInGREP++;
        count++;
    }
    int lineNumberArray[numberOfLinesInGREP];
    // Get the number of fortune files
    char *name;
    char *pattern;
    pattern = (char *)malloc(sizeof(char) * (strlen(argv[index_of_pattern]) + 1));
    //printf("argv: %s\n", argv[1]);
    strcpy(pattern, argv[index_of_pattern]);
    //printf("pattern: %s\n", pattern);
    int fileIterator = 0;
    char *orig;
    //char *orig2;
    for (ptr = listhead; ptr != NULL; ptr = ptr->next)
    {
        orig = malloc(strlen(ptr->str) + 1);
        //orig2 = malloc(strlen(ptr->str) + 1);
        strcpy(orig, ptr->str);
        strtok(orig, ":");
        lineNumberArray[fileIterator] = atoi(strtok(NULL, ":"));
        if (!(strcmp(name, strtok(ptr->str, ":")) == 0)) { numberOfFurtuneFiles++; }
        name = (char *)malloc(sizeof(char) * (strlen(ptr->str) + 1));
        strcpy(name, strtok(ptr->str, ":"));
        fileIterator++;
    }

    // Create array of fortune file names
    char *fileNamesArray[numberOfFurtuneFiles];
    char *auxiliary;
    i = 0;
    for (ptr = listhead; ptr != NULL; ptr = ptr->next)
    {
        auxiliary = (char *)malloc(sizeof(char) * (strlen(ptr->str) + 1));
        strcpy(auxiliary, ptr->str);
        if (i == 0)
        {
            fileNamesArray[i] = auxiliary;
            i++;
        }
        else
        {
            if (strcmp(fileNamesArray[i - 1], auxiliary) == 0)
            {
                continue;
            }
            else
            {
                fileNamesArray[i] = auxiliary;
                i++;
            }
        }
    }

    /*
    printf("-------------------\n");
    for (i = 0; i < sizeof(fileNamesArray)/sizeof(fileNamesArray[0]); i++)
    {
        printf("fileNamesArray[%d] = %s\n", i, fileNamesArray[i]);
    }
    printf("-------------------\n");
    for (i = 0; i < sizeof(lineNumberArray)/sizeof(lineNumberArray[0]); i++)
    {
        printf("lineNumberArray[%d] = %d\n", i, lineNumberArray[i]);
    }
    printf("-------------------\n");
    printf("numberOfFurtuneFiles: %d\n", numberOfFurtuneFiles);
    printf("numberOfLinesInGREP : %d\n", numberOfLinesInGREP);
    printf("-------------------\n");
    printf("bannerFlag   : %s\n", bannerFlag ? "true" : "false");
    printf("highlightFlag: %s\n", highlightFlag ? "true" : "false");
    printf("-------------------\n");
    */

    // Now open the fortune files and print appropriate quotes
    FILE* sourceFile;
    int curLineNumber;
    char tmp[4096];
    char line[4096];
    bool matchFound;
    int numberOfMatches = 0;
    for (i = 0; i < numberOfFurtuneFiles; i++)
    {
        // If the user wants to search through more than one fortune file
        sourceFile = fopen(fileNamesArray[i], "r");
        curLineNumber = 0;
        while (fgets(line, sizeof(line), sourceFile))
        {
            if (strcmp(line, "%\n") == 0)
            { // print out the current saying and clear tmp array
                if ((isValueInArray(curLineNumber,lineNumberArray,sizeof(lineNumberArray)/sizeof(lineNumberArray[0]))||matchFound))
                {
                    
                    if (strstr(tmp, pattern) != NULL)
                    {
                        if ((newnodeSayings = (struct snodeSayings *)malloc(sizeof(struct snodeSayings))) == NULL)
                        {
                            fprintf(stderr,"mklist: malloc failure for newnode\n");
                            exit(1);
                        }
                        if ((newnodeSayings -> str = malloc(strlen(tmp) + 1)) == NULL)
                        {
                            fprintf(stderr,"mklist: malloc failure for newnode -> str\n");
                            exit(1);
                        }
                        if (strncpy(newnodeSayings -> str, tmp, strlen(tmp) + 1) != newnodeSayings -> str)
                        {
                            fprintf(stderr,"mklist: string copy problem\n");
                            exit(1);
                        }
                        newnodeSayings -> next = NULL;
                        if (listtailSayings == NULL) { listheadSayings = listtailSayings = newnodeSayings; }
                        else
                        {
                            listtailSayings -> next = newnodeSayings;
                            listtailSayings = newnodeSayings;
                        }
                        numberOfMatches++;
                        matchFound = false;
                    }
                    matchFound = false;
                }
                tmp[0] = '\0'; // Clears the tmp string
            }
            else
            {   // add the line to tmp saying
                if (isValueInArray(curLineNumber, lineNumberArray, sizeof(lineNumberArray)/sizeof(lineNumberArray[0])))
                {
                    matchFound = true;
                }
                strcat(tmp, line);
            }
            curLineNumber++;
        }
        fclose(sourceFile);
    }

    // Banner output
    if (bannerFlag)
    {
        if (numberOfMatches == 1)
        {
            printf("%d witty saying contains the string %s\n", numberOfMatches, argv[index_of_pattern]);
            printf("\n");
        }
        else
        {
            printf("%d witty sayings contain the string %s\n", numberOfMatches, argv[index_of_pattern]);
            printf("\n");
        }
    }

    if (highlightFlag) // Use inverse video to highlight the search string
    {

        i = 0;
        int k;
        for (ptrSayings = listheadSayings; ptrSayings != NULL; ptrSayings = ptrSayings->next)
        {
            if (i > 0)
            {
                printf("-----------------------------------------\n");
            }

            int numberToHighlight = findAllIndexes(ptrSayings->str, argv[index_of_pattern]);

            int indexesToHighlight[numberToHighlight];
            char const *p_ = ptrSayings->str;
            int count;
            int iter = 0;
            for (count = 0; ; ++count)
            {
                p_ = strstr(p_, argv[index_of_pattern]);
                if (!p_)
                    break;
                //printf("diff: %d\n", (int)(p - str));
                indexesToHighlight[iter] = (int)(p_ - ptrSayings->str);
                p_++;
                iter++;
            }

            char *finalString = (char *)malloc(sizeof(char) * (strlen(ptrSayings->str) + 1 + (numberToHighlight * 20)));
            for (k = 0; k < strlen(ptrSayings->str) + 1; k++)
            {
                if (isValueInArray(k, indexesToHighlight, numberToHighlight))
                {
                    strcat(finalString, "\e[7m");
                    strcat(finalString, argv[index_of_pattern]);
                    strcat(finalString, "\e[0m");
                    k = k + strlen(argv[index_of_pattern]) - 1;
                }
                else
                {
                    strncat(finalString, &ptrSayings->str[k], 1);
                }
            }
            printf("%s\n", finalString);

            /*
            char *result = strstr(ptrSayings->str, argv[index_of_pattern]);
            int position = result - ptrSayings->str;
            for (i = 0; i < position; i++)
            {
                printf("%c", ptrSayings->str[i]);
            }
            printf("\e[7m%s\e[0m", argv[index_of_pattern]);
            for (i = position + strlen(argv[index_of_pattern]); i < strlen(ptrSayings->str); i++)
            {
                printf("%c", ptrSayings->str[i]);
            }
            //printf("\n");
            */
            i++;
        }
    }
    else
    {
        i = 0;
        for (ptrSayings = listheadSayings; ptrSayings != NULL; ptrSayings = ptrSayings->next)
        {
            if (i > 0)
            {
                printf("-----------------------------------------\n");
            }
            //printf("%s\n", ptrSayings->str);
            printf("%s", ptrSayings->str);  // To print without the newline
            i++;
        }
    }

    



    exit(0); // return 0;


}


// Taken from http://stackoverflow.com/questions/15094834/check-if-a-value-exist-in-a-array
bool isValueInArray(int val, int *arr, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (arr[i] == val)
        {
            return true;
        }
    }
    return false;
}

// Taken from http://stackoverflow.com/questions/2180404/is-there-a-c-function-to-find-the-second-occurrence-of-substring-in-string
int findAllIndexes(char const *str, char const *str2)
{
    int iter = 0;
    char const *p = str;
    int count;
    for (count = 0; ; ++count)
    {
        p = strstr(p, str2);
        if (!p)
            break;
        //printf("diff: %d\n", (int)(p - str));
        iter++;
        p++;
    }
    return iter;
}




