#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Please enter a valid value for k\n");
        return 1;
    }
    int k = atoi(argv[1]);
    
    if (k == 0)
    {
        printf("Please enter a valid value for k\n");
        return 1;
    }
    
    printf("Please enter some plain text:\n");
    string myString = GetString();
    printf("The encrypted text is:\n");
     
    for (int i = 0, n = strlen(myString); i <= n; i++)
    {
        if (isalpha(myString[i]) == 0)
        {
            printf("%c", myString[i]);
        }
        else if (isupper(myString[i]))
        {   
            int ascii = myString[i];
            int alpha = ascii - 65;
            char pre = (alpha + k) % 26;
            char post = pre + 65;
            printf("%c", post);
        }
        else
        {
            int ascii = myString[i];
            int alpha = ascii - 97;
            char pre = (alpha + k) % 26;
            char post = pre + 97;
            printf("%c", post);
        }
        
    }
    
    printf("\n");
    
    
   
    
        
}

