#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int ascii(char letter);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    //  Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }

    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }

    else
    {
        printf("Tie\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    //Change each letter in string to lowercase
    int len = strlen(word);

    for (int i = 0; i < len; i++)
    {
        word[i] = tolower(word[i]);
    }

    /*loop in order to sum the value of each char letter.
    if char is not a letter, it is ignored
    */
    int k = 0;
    int sum = 0;
    int helper = 0;

    while (k < len)
    {
        helper = ascii(word[k]);

        // if the value is greater than 0, then it is a letter
        if (helper)
        {
            /* Get the ascii value representation of each char.
               Go into POINTS array and return the corresponding index value
               a is at index 0...
               b index 1...
               c index 2..
               And so on..
               Each ascii value is one greater than the previous,
               So the code below takes the ascii value, subtracts from a,
               then indexes into the corresponding int result.
            */
           sum += POINTS[helper - 97];
        }

        k++;
    }
    return sum;
}

int ascii(char letter)
{
    // Return the ASCII value of each input letter. 0 if its not a letter.
    if ((int) letter >= 97 && (int) letter <= 122)
    {
        // Return the ascii value in int
        return (int) letter;
    }
    return 0;

}
