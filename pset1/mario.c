#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Height: ");
    int n = GetInt();
    
    while (n < 0 || n > 23)
    {
        printf("Height: ");
        n = GetInt();
    }
        
    int ver = 1;
    int space = n - 2;
    while (ver <= n)
    {

        while (space >= 0)
        {
            printf(" ");
            space--; 
        }
        
        int hor = ver;

        while (hor >= 0)
        {
            printf("#");
            hor--;
            
        }
                
        printf("\n");
        ver++;
        space = (n - 1) - ver;
    
    }
    
        
}
