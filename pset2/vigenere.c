#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{

   
    if (argc != 2)
    {
        printf("Please enter a valid value as keyword\n");
        return 1;
    }
    
    char keyword[strlen(argv[1])];
    
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        
        if (isalpha(argv[1][i]))
        {
            keyword[i] = tolower(argv[1][i]); 
        }
        else
        {
            printf("Please enter a keyword containing only letters!\n");
            return 1; 
        }
   
    }
        

    printf("Please enter some plain text to be encrypted:\n");
    string text = GetString();
    printf("The encrypted text is:\n");
    
    for (int i = 0, j = 0; i <= strlen(text); i++, j++)
    {
        if (j % strlen(argv[1]) == 0)
        {
            j = 0;
        }
        if (isalpha(text[i]) == 0)
        {
            printf("%c", text[i]);
            j--;
        }
        else if (islower(text[i]))
        {
            int asciiKeyword = keyword[j];
            int alphaKeyword = asciiKeyword - 97;
            int ascii = text[i];
            int alpha = ascii - 97;
            char pre = (alpha + alphaKeyword) % 26;
            char post = pre + 97;
            printf("%c", post);
        }
        else
        {
            int asciiKeyword = keyword[j];
            int alphaKeyword = asciiKeyword - 97;
            int ascii = text[i];
            int alpha = ascii - 65;
            char pre = (alpha + alphaKeyword) % 26;
            char post = pre + 65;
            printf("%c", post);
        }
    }
    
    printf("\n");
    
}
