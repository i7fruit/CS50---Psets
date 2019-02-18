/*
 * initials.c (more comfortable)
 * Nzefili Macaulay
 *
 * This program prints the initials of a name
 * entered by the user.
 */
 
 #include <stdio.h>
 #include <cs50.h>
 #include <string.h>
 #include <ctype.h> // For the character functions
 
 int main(void)
 {
     
     // Gets input from the user
     string name = get_string();
     
     // Ensures get_string gets a string
     if (name != NULL)
     {
          /*
           * Prints the first initial by checking
           * for prior non-alphabets
           */
           
          int j = 0;
          
          while (!(isalpha(name[j])))
          {
              j++;
          }
          printf("%c", toupper(name[j]));
          
          // Iterates over the remaining characters
          for (int i = j, n = strlen(name); i < n; i++)
          {
              // Capitalizes the alphabet immediately after the non-alphabet
              if ((!(isalpha(name[i]))) && (isalpha(name[i + 1])))
              {
                  printf("%c", toupper(name[i + 1]));
              }
          }
     }
     printf("\n");
     
     return 0;
 }