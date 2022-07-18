#include "helpers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    //Iterate through each row
    for (int i = 0; i < height; i++)
    {
        //Iterate through each item in each row
        for (int j = 0; j < width; j++)
        {
            //Take each RGB value, calculate average, set each to average
            BYTE *blue = &image[i][j].rgbtBlue;
            BYTE *green = &image[i][j].rgbtGreen;
            BYTE *red = &image[i][j].rgbtRed;

            BYTE average = (BYTE) round((*blue + *green + *red) / 3.0);

            *blue = average;
            *green = average;
            *red = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // Loop through each pixel and calculate the sepia value according to the formula
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue));
            int sepiaGreen = round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));
            int sepiaBlue = round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue));

            // if value is greater than 255 then the value is set to the maximum of 255
            if (sepiaRed >= 255)
            {
                sepiaRed = 255;

            }
            if (sepiaGreen >= 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue >= 255)
            {
                sepiaBlue = 255;
            }

            //Set the pixels value to the calculated sepia value
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE *right, *left;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //If right and left point to the same, break
            if (j >= (width - 1) - j)
            {
                break;
            }

            left = &image[i][j];

            right = &image[i][(width - 1) - j];

            RGBTRIPLE helper;
            helper = *left;
            *left = *right;
            *right = helper;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Define data type containing each RGB value
    typedef struct
    {
        BYTE rgbtBlue;
        BYTE rgbtGreen;
        BYTE rgbtRed;
    }
    temp;
    temp tempimage[height][width];

    // Copies passed image values into tempimage (class)
    // In order to calculate blur effect
    // Loop through rows then columns
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempimage[i][j].rgbtRed = image[i][j].rgbtRed;
            tempimage[i][j].rgbtBlue = image[i][j].rgbtBlue;
            tempimage[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }

    //Loop through rows and columns
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // If pixel is the uppermost left one
            if (i == 0 && j == 0)
            {
                image[i][j].rgbtRed = round(((tempimage[i][j].rgbtRed + tempimage[i][j + 1].rgbtRed + tempimage[i + 1][j].rgbtRed +
                                              tempimage[i + 1][j + 1].rgbtRed) / 4.0));
                image[i][j].rgbtGreen = round(((tempimage[i][j].rgbtGreen + tempimage[i][j + 1].rgbtGreen + tempimage[i + 1][j].rgbtGreen +
                                                tempimage[i + 1][j + 1].rgbtGreen) / 4.0));
                image[i][j].rgbtBlue = round(((tempimage[i][j].rgbtBlue + tempimage[i][j + 1].rgbtBlue + tempimage[i + 1][j].rgbtBlue +
                                               tempimage[i + 1][j + 1].rgbtBlue) / 4.0));
            }
            // If pixel is uppermost right one
            else if (i == 0 && j == width - 1)
            {
                image[i][j].rgbtRed = round(((tempimage[i][j].rgbtRed + tempimage[i][j - 1].rgbtRed + tempimage[i + 1][j].rgbtRed +
                                              tempimage[i + 1][j - 1].rgbtRed) / 4.0));
                image[i][j].rgbtGreen = round(((tempimage[i][j].rgbtGreen + tempimage[i][j - 1].rgbtGreen + tempimage[i + 1][j].rgbtGreen +
                                                tempimage[i + 1][j - 1].rgbtGreen) / 4.0));
                image[i][j].rgbtBlue = round(((tempimage[i][j].rgbtBlue + tempimage[i][j - 1].rgbtBlue + tempimage[i + 1][j].rgbtBlue +
                                               tempimage[i + 1][j - 1].rgbtBlue) / 4.0));
            }
            // if pixel is lowermost left one
            else if (j == 0 && i == height - 1)
            {
                image[i][j].rgbtRed = round(((tempimage[i][j].rgbtRed + tempimage[i][j + 1].rgbtRed + tempimage[i - 1][j].rgbtRed +
                                              tempimage[i - 1][j + 1].rgbtRed) / 4.0));
                image[i][j].rgbtGreen = round(((tempimage[i][j].rgbtGreen + tempimage[i][j + 1].rgbtGreen + tempimage[i - 1][j].rgbtGreen +
                                                tempimage[i - 1][j + 1].rgbtGreen) / 4.0));
                image[i][j].rgbtBlue = round(((tempimage[i][j].rgbtBlue + tempimage[i][j + 1].rgbtBlue + tempimage[i - 1][j].rgbtBlue +
                                               tempimage[i - 1][j + 1].rgbtBlue) / 4.0));
            }
            // if the pixel lowermost right one
            else if (i == height - 1 && j == width - 1)
            {
                image[i][j].rgbtRed = round(((tempimage[i][j].rgbtRed + tempimage[i][j - 1].rgbtRed + tempimage[i - 1][j].rgbtRed +
                                              tempimage[i - 1][j - 1].rgbtRed) / 4.0));
                image[i][j].rgbtGreen = round(((tempimage[i][j].rgbtGreen + tempimage[i][j - 1].rgbtGreen + tempimage[i - 1][j].rgbtGreen +
                                                tempimage[i - 1][j - 1].rgbtGreen) / 4.0));
                image[i][j].rgbtBlue = round(((tempimage[i][j].rgbtBlue + tempimage[i][j - 1].rgbtBlue + tempimage[i - 1][j].rgbtBlue +
                                               tempimage[i - 1][j - 1].rgbtBlue) / 4.0));
            }
            // if the pixel is in first line
            else if (i == 0)
            {
                image[i][j].rgbtRed = round(((tempimage[i][j].rgbtRed + tempimage[i][j - 1].rgbtRed + tempimage[i][j + 1].rgbtRed + tempimage[i +
                                              1][j].rgbtRed +
                                              tempimage[i + 1][j - 1].rgbtRed  + tempimage[i + 1][j + 1].rgbtRed) / 6.0));
                image[i][j].rgbtGreen = round(((tempimage[i][j].rgbtGreen + tempimage[i][j - 1].rgbtGreen + tempimage[i][j + 1].rgbtGreen +
                                                tempimage[i + 1][j].rgbtGreen +
                                                tempimage[i + 1][j - 1].rgbtGreen  + tempimage[i + 1][j + 1].rgbtGreen) / 6.0));
                image[i][j].rgbtBlue = round(((tempimage[i][j].rgbtBlue + tempimage[i][j - 1].rgbtBlue + tempimage[i][j + 1].rgbtBlue + tempimage[i
                                               +
                                               1][j].rgbtBlue +
                                               tempimage[i + 1][j - 1].rgbtBlue  + tempimage[i + 1][j + 1].rgbtBlue) / 6.0));
            }
            // if the pixel is in last line
            else if (i == height - 1)
            {
                image[i][j].rgbtRed = round(((tempimage[i][j].rgbtRed + tempimage[i][j - 1].rgbtRed + tempimage[i][j + 1].rgbtRed + tempimage[i -
                                              1][j].rgbtRed +
                                              tempimage[i - 1][j - 1].rgbtRed  + tempimage[i - 1][j + 1].rgbtRed) / 6.0));
                image[i][j].rgbtGreen = round(((tempimage[i][j].rgbtGreen + tempimage[i][j - 1].rgbtGreen + tempimage[i][j + 1].rgbtGreen +
                                                tempimage[i -
                                                        1][j].rgbtGreen +
                                                tempimage[i - 1][j - 1].rgbtGreen  + tempimage[i - 1][j + 1].rgbtGreen) / 6.0));
                image[i][j].rgbtBlue = round(((tempimage[i][j].rgbtBlue + tempimage[i][j - 1].rgbtBlue + tempimage[i][j + 1].rgbtBlue + tempimage[i
                                               -
                                               1][j].rgbtBlue +
                                               tempimage[i - 1][j - 1].rgbtBlue  + tempimage[i - 1][j + 1].rgbtBlue) / 6.0));
            }
            // If the pixel is leftmost and edge
            else if (j == 0)
            {
                image[i][j].rgbtRed = round(((tempimage[i][j].rgbtRed + tempimage[i - 1][j].rgbtRed + tempimage[i + 1][j].rgbtRed + tempimage[i][j +
                                              1].rgbtRed +
                                              tempimage[i - 1][j + 1].rgbtRed  + tempimage[i + 1][j + 1].rgbtRed) / 6.0));
                image[i][j].rgbtGreen = round(((tempimage[i][j].rgbtGreen + tempimage[i - 1][j].rgbtGreen + tempimage[i + 1][j].rgbtGreen +
                                                tempimage[i][j + 1].rgbtGreen +
                                                tempimage[i - 1][j + 1].rgbtGreen  + tempimage[i + 1][j + 1].rgbtGreen) / 6.0));
                image[i][j].rgbtBlue = round(((tempimage[i][j].rgbtBlue + tempimage[i - 1][j].rgbtBlue + tempimage[i + 1][j].rgbtBlue +
                                               tempimage[i][j + 1].rgbtBlue +
                                               tempimage[i - 1][j + 1].rgbtBlue  + tempimage[i + 1][j + 1].rgbtBlue) / 6.0));
            }
            // if the pixel is rightmost and edge
            else if (j == width - 1)
            {
                image[i][j].rgbtRed = round(((tempimage[i][j].rgbtRed + tempimage[i - 1][j].rgbtRed + tempimage[i + 1][j].rgbtRed + tempimage[i][j -
                                              1].rgbtRed +
                                              tempimage[i - 1][j - 1].rgbtRed  + tempimage[i + 1][j - 1].rgbtRed) / 6.0));
                image[i][j].rgbtGreen = round(((tempimage[i][j].rgbtGreen + tempimage[i - 1][j].rgbtGreen + tempimage[i + 1][j].rgbtGreen +
                                                tempimage[i][j - 1].rgbtGreen +
                                                tempimage[i - 1][j - 1].rgbtGreen  + tempimage[i + 1][j - 1].rgbtGreen) / 6.0));
                image[i][j].rgbtBlue = round(((tempimage[i][j].rgbtBlue + tempimage[i - 1][j].rgbtBlue + tempimage[i + 1][j].rgbtBlue +
                                               tempimage[i][j - 1].rgbtBlue +
                                               tempimage[i - 1][j - 1].rgbtBlue  + tempimage[i + 1][j - 1].rgbtBlue) / 6.0));
            }
            // If neither of the above options, take a surrounding view of rgb values
            else
            {
                image[i][j].rgbtRed = round(((tempimage[i][j].rgbtRed + tempimage[i][j - 1].rgbtRed + tempimage[i][j + 1].rgbtRed + tempimage[i -
                                              1][j].rgbtRed +
                                              tempimage[i - 1][j - 1].rgbtRed  + tempimage[i - 1][j + 1].rgbtRed + tempimage[i + 1][j].rgbtRed
                                              + tempimage[i + 1][j + 1].rgbtRed + tempimage[i + 1][j - 1].rgbtRed) / 9.0));
                image[i][j].rgbtGreen = round(((tempimage[i][j].rgbtGreen + tempimage[i][j - 1].rgbtGreen + tempimage[i][j + 1].rgbtGreen +
                                                tempimage[i - 1][j].rgbtGreen +
                                                tempimage[i - 1][j - 1].rgbtGreen  + tempimage[i - 1][j + 1].rgbtGreen + tempimage[i + 1][j].rgbtGreen
                                                + tempimage[i + 1][j + 1].rgbtGreen + tempimage[i + 1][j - 1].rgbtGreen) / 9.0));
                image[i][j].rgbtBlue = round(((tempimage[i][j].rgbtBlue + tempimage[i][j - 1].rgbtBlue + tempimage[i][j + 1].rgbtBlue +
                                               tempimage[i - 1][j].rgbtBlue +
                                               tempimage[i - 1][j - 1].rgbtBlue  + tempimage[i - 1][j + 1].rgbtBlue + tempimage[i + 1][j].rgbtBlue
                                               + tempimage[i + 1][j + 1].rgbtBlue + tempimage[i + 1][j - 1].rgbtBlue) / 9.0));
            }
        }
    }
    return;
}