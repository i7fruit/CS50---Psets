/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * This function searches for the specified
 * value by using a divide and conquer approach.
 * It finds the mid-point of the given array
 * and compares the value of its element to the
 * sort-after value. If the value is found, the
 * function returns true, if not, it adjusts its
 * lowest and highest indices and calls itself
 * recursively until the value is found
 */
 
int binary(int Array[], int low, int high, int x)
{
    while (low <= high)
    {
        // Finds the middle index
        int mid = (low + high) / 2;
        
        // Returns true if the value is found        
        if (Array[mid] == x)
        {
            return true;
        }
        
        // Searches the left half
        else if (x < Array[mid])
        {
            // Changes highest index
            high = mid - 1;
            binary(Array, low, high, x);
        }
        
        // Searches the right half
        else if (x > Array[mid])
        {
            low = mid + 1;
            binary(Array, low, high, x);
        }
    }
    
    return false;
}

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    
    // Searches through the array using binary search
    if (n < 0)
    {
        return false;
    }
    
    // Calculates highest and lowest indices
    int low = 0, high = n - 1;
        
    if (binary(values, low, high, value))
    {
        return true;
    }
    
    else
    {
        return false;
    }
}

/**
 * Sorts array of n values using counting sort.
 */
void sort(int values[], int n)
{
     const int MAX = 65536;
     
    /**
      * Declares a counter array
      * to track the frequency of each number
      */
     int counter[MAX];
     
     for (int i = 0; i < MAX; i++)
     {
         counter[i] = 0;
     }
     
     /**
      * Calculates the frequency of
      * occurance of each integer
      */
     
     for (int i = 0; i < n; i++)
     {
          counter[values[i]]++;
     }
     
     /**
      * Makes each element of counter a cummulative of
      * itself and the previous element
      */
     
     for (int i = 0; i < MAX; i++)
     {
         if (i > 0)
             counter[i] = counter[i - 1] + counter[i];
     }
     
     // Shifts the indices of the counter array to the right ==>
     for (int i = (MAX - 1); i >= 0; i--)
     {
          if (i == 0)
          {
              counter[i] = i;
              break;
          }
          counter[i] = counter[i - 1];
     }
     
     // Declares a new array to hold the sorted list
     int sorted[n];
     
     for (int i = 0; i < n; i++)
     {
         sorted[i] = 0;
     }
     
     // Initializes the new array with a sorted list
     for (int k = n - 1; k >= 0 ; k--)
     {
         {
             sorted[counter[values[k]]] = values[k];
             counter[values[k]]++;
         }
     }
     
     // Copies values to original array
     for (int i = 0; i < n; i++)
     {
         values[i] = sorted[i];
     }
     
     printf("\n");
     
    return;
}