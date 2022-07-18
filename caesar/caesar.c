#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int confirmation(string arg);

int main(int argc, string argv[])
{
    // Handle the error if user does not pass a key or if passing more than 1 argument
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Handle the error when key is not a number
    string key = argv[1];
    int validation = confirmation(key);

    if (!validation)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    /*
    Program logic
    dislocator will always be a number between 0 and 25
    */
    int dislocator = atoi(key);
    string plainText = get_string("plaintext:  ");

    // ASCII index for a and A
    const int lower_a = 97;
    const int upper_A = 65;

    // Encrypting the plaintext
    for (int i = 0, length = strlen(plainText); i < length; i++)
    {
        //  When char is alpahbetical
        if (isalpha(plainText[i]))
        {
            // If letter is capitalized
            if ((int) plainText[i] <= 90)
            {
                plainText[i] = (char)(((int) plainText[i] - upper_A + dislocator) % 26) + upper_A;
            }

            // Otherwise, if it is lowercase
            else
            {
                plainText[i] = (char)(((int) plainText[i] - lower_a + dislocator) % 26) + lower_a;
            }
        }
    }

    printf("ciphertext: %s\n", plainText);

    return 0;
}

// Confrim that the characters in the key are indeed numbers
int confirmation(string arg)
{
    for (int i = 0, n = strlen(arg); i < n; i++)
    {
        if (!isdigit(arg[i]))
        {
            return 0;
        }
    }

    return 1;
}