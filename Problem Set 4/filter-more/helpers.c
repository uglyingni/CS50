#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            average = average / 3;
            image[i][j].rgbtRed = roundf(average);
            image[i][j].rgbtGreen = roundf(average);
            image[i][j].rgbtBlue = roundf(average);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE swap = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = swap;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image2[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float averageR = image[i][j].rgbtRed;
            float averageG = image[i][j].rgbtGreen;
            float averageB = image[i][j].rgbtBlue;
            int counter = 1;

            if (i != 0)
            {
                averageR += image[i - 1][j].rgbtRed;
                averageG += image[i - 1][j].rgbtGreen;
                averageB += image[i - 1][j].rgbtBlue;
                counter++;
            }

            if (j != 0)
            {
                averageR += image[i][j - 1].rgbtRed;
                averageG += image[i][j - 1].rgbtGreen;
                averageB += image[i][j - 1].rgbtBlue;
                counter++;
            }

            if (i != (height - 1))
            {
                averageR += image[i + 1][j].rgbtRed;
                averageG += image[i + 1][j].rgbtGreen;
                averageB += image[i + 1][j].rgbtBlue;
                counter++;
            }

            if (j != (width - 1))
            {
                averageR += image[i][j + 1].rgbtRed;
                averageG += image[i][j + 1].rgbtGreen;
                averageB += image[i][j + 1].rgbtBlue;
                counter++;
            }

            if ((i != 0) && (j != 0))
            {
                averageR += image[i - 1][j - 1].rgbtRed;
                averageG += image[i - 1][j - 1].rgbtGreen;
                averageB += image[i - 1][j - 1].rgbtBlue;
                counter++;
            }

            if ((i != 0) && (j != (width - 1)))
            {
                averageR += image[i - 1][j + 1].rgbtRed;
                averageG += image[i - 1][j + 1].rgbtGreen;
                averageB += image[i - 1][j + 1].rgbtBlue;
                counter++;
            }

            if ((i != (height - 1)) && (j != 0))
            {
                averageR += image[i + 1][j - 1].rgbtRed;
                averageG += image[i + 1][j - 1].rgbtGreen;
                averageB += image[i + 1][j - 1].rgbtBlue;
                counter++;
            }

            if ((i != (height - 1)) && (j != (width - 1)))
            {
                averageR += image[i + 1][j + 1].rgbtRed;
                averageG += image[i + 1][j + 1].rgbtGreen;
                averageB += image[i + 1][j + 1].rgbtBlue;
                counter++;
            }

            averageR = averageR / counter;
            averageG = averageG / counter;
            averageB = averageB / counter;
            image2[i][j].rgbtRed = roundf(averageR);
            image2[i][j].rgbtGreen = roundf(averageG);
            image2[i][j].rgbtBlue = roundf(averageB);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image2[i][j].rgbtRed;
            image[i][j].rgbtGreen = image2[i][j].rgbtGreen;
            image[i][j].rgbtBlue = image2[i][j].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image2[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float GxR = 0;
            float GyR = 0;
            float GxG = 0;
            float GyG = 0;
            float GxB = 0;
            float GyB = 0;

            if (i != 0)
            {
                GyR += (-2 * image[i - 1][j].rgbtRed);
                GyG += (-2 * image[i - 1][j].rgbtGreen);
                GyB += (-2 * image[i - 1][j].rgbtBlue);
            }

            if (j != 0)
            {
                GxR += (-2 * image[i][j - 1].rgbtRed);
                GxG += (-2 * image[i][j - 1].rgbtGreen);
                GxB += (-2 * image[i][j - 1].rgbtBlue);
            }

            if (i != (height - 1))
            {
                GyR += (2 * image[i + 1][j].rgbtRed);
                GyG += (2 * image[i + 1][j].rgbtGreen);
                GyB += (2 * image[i + 1][j].rgbtBlue);
            }

            if (j != (width - 1))
            {
                GxR += (2 * image[i][j + 1].rgbtRed);
                GxG += (2 * image[i][j + 1].rgbtGreen);
                GxB += (2 * image[i][j + 1].rgbtBlue);
            }

            if ((i != 0) && (j != 0))
            {
                GxR += (-1 * image[i - 1][j - 1].rgbtRed);
                GxG += (-1 * image[i - 1][j - 1].rgbtGreen);
                GxB += (-1 * image[i - 1][j - 1].rgbtBlue);
                GyR += (-1 * image[i - 1][j - 1].rgbtRed);
                GyG += (-1 * image[i - 1][j - 1].rgbtGreen);
                GyB += (-1 * image[i - 1][j - 1].rgbtBlue);
            }

            if ((i != 0) && (j != (width - 1)))
            {
                GxR += image[i - 1][j + 1].rgbtRed;
                GxG += image[i - 1][j + 1].rgbtGreen;
                GxB += image[i - 1][j + 1].rgbtBlue;
                GyR += (-1 * image[i - 1][j + 1].rgbtRed);
                GyG += (-1 * image[i - 1][j + 1].rgbtGreen);
                GyB += (-1 * image[i - 1][j + 1].rgbtBlue);
            }

            if ((i != (height - 1)) && (j != 0))
            {
                GxR += (-1 * image[i + 1][j - 1].rgbtRed);
                GxG += (-1 * image[i + 1][j - 1].rgbtGreen);
                GxB += (-1 * image[i + 1][j - 1].rgbtBlue);
                GyR += image[i + 1][j - 1].rgbtRed;
                GyG += image[i + 1][j - 1].rgbtGreen;
                GyB += image[i + 1][j - 1].rgbtBlue;
            }

            if ((i != (height - 1)) && (j != (width - 1)))
            {
                GxR += image[i + 1][j + 1].rgbtRed;
                GxG += image[i + 1][j + 1].rgbtGreen;
                GxB += image[i + 1][j + 1].rgbtBlue;
                GyR += image[i + 1][j + 1].rgbtRed;
                GyG += image[i + 1][j + 1].rgbtGreen;
                GyB += image[i + 1][j + 1].rgbtBlue;
            }
            float SobelR = sqrt((GxR * GxR) + (GyR * GyR));
            float SobelG = sqrt((GxG * GxG) + (GyG * GyG));
            float SobelB = sqrt((GxB * GxB) + (GyB * GyB));
            if (SobelR > 255.0)
            {
                SobelR = 255.0;
            }
            if (SobelG > 255.0)
            {
                SobelG = 255.0;
            }
            if (SobelB > 255.0)
            {
                SobelB = 255.0;
            }
            image2[i][j].rgbtRed = roundf(SobelR);
            image2[i][j].rgbtGreen = roundf(SobelG);
            image2[i][j].rgbtBlue = roundf(SobelB);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image2[i][j].rgbtRed;
            image[i][j].rgbtGreen = image2[i][j].rgbtGreen;
            image[i][j].rgbtBlue = image2[i][j].rgbtBlue;
        }
    }
    return;
}
