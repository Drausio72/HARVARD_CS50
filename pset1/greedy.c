#include <stdio.h>
#include <cs50.h>

int main(void)
{

    printf("O hai. How much change is owed?\n");
    float f = GetFloat();

    while (f < 0)
    {
        printf("O hai. How much change is owed?\n");
        f = GetFloat();
    }


    
    if (f == 0)
    {
        printf("0");
    }   


    if (f != 0)
    {
        int b = 0;
    
        while (f >= 0.249999)
        {   
            b++;
            f = f - 0.25;
        }
        


        while (f >= 0.09999)
        {
            b++;
            f = f - 0.1;
        }
        


        while (f >= 0.04999)
        {
            b++;
            f = f - 0.05;
        }

        while (f >= 0.009999)
        {
            b++;
            f = f - 0.01;
        }
    
        printf("%i\n", b);


    }


}
