/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // implement a searching algorithm
    

    int end = n - 1;
    int start = 0;
    int mid = (start + end) / 2;
    int m = 0;

    
    while (start <= end)
    {
        if (values[mid] < value)
        {
            start = mid + 1;
        }
        else if (values[mid] == value)
        {
            m = 1;
            break;
        }
        else if (values[mid] > value)
        {
            end = mid - 1;
        }
        
        mid = (start + end) / 2;
    }   
    
    
    
    printf("%d\n", m);
    return m;

}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int tmp = 0;
    //implement an O(n^2) sorting algorithm
    for (int i = 0; i < n; i++)
    {   
        for (int j = 0; j < n - 1; j++)
        {
            if (values[j] > values[j+1])
            {   
                tmp = values[j];
                values[j] = values[j+1];
                values[j+1] = tmp;
            }
        }
    }


/*    for (int i = 0; i < n; i++)*/
/*    {*/
/*        printf("%d\n", values[i]);*/
/*    }*/
    return;
}
