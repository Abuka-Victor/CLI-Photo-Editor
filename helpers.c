#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float average;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            image[i][j].rgbtBlue = (int) round(average);
            image[i][j].rgbtGreen = (int) round(average);
            image[i][j].rgbtRed = (int) round(average);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round((.393 * image[i][j].rgbtRed) + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue));
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            sepiaGreen = round((.349 * image[i][j].rgbtRed) + (.686 * image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue));
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            sepiaBlue = round((.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue));
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = (int) sepiaRed;
            image[i][j].rgbtGreen = (int) sepiaGreen;
            image[i][j].rgbtBlue = (int) sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE swap_keep;
    for (int i = 0; i < height; i++)
    {
        int last_item = width - 1;
        for (int j = 0; j < width; j++)
        {
            swap_keep = image[i][last_item];
            image[i][last_item] = image[i][j];
            image[i][j] = swap_keep;
            last_item--;
            if (width % 2 == 0)
            {
                if (last_item == ((width / 2) - 1))
                {
                    break;
                }
            }
            else
            {
                if (last_item == (width / 2))
                {
                    break;
                }
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Make up new image
    RGBTRIPLE blurImage[height][width];
    // Assign them values;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Edges
            if (i == 0 || i == (height - 1))
            {
                // Corners
                // Top Left
                if (i == 0 && j == 0)
                {
                    blurImage[i][j].rgbtRed = round(((image[i][j].rgbtRed) + (image[i][j + 1].rgbtRed) + (image[i + 1][j].rgbtRed) +
                                                     (image[i + 1][j + 1].rgbtRed)) / 4.0);
                    blurImage[i][j].rgbtGreen = round(((image[i][j].rgbtGreen) + (image[i][j + 1].rgbtGreen) + (image[i + 1][j].rgbtGreen) +
                                                       (image[i + 1][j + 1].rgbtGreen)) / 4.0);
                    blurImage[i][j].rgbtBlue = round(((image[i][j].rgbtBlue) + (image[i][j + 1].rgbtBlue) + (image[i + 1][j].rgbtBlue) +
                                                      (image[i + 1][j + 1].rgbtBlue)) / 4.0);
                }
                else if (i == 0 && j == (width - 1))
                {
                    // Top Right
                    blurImage[i][j].rgbtRed = round(((image[i][j].rgbtRed) + (image[i][j - 1].rgbtRed) + (image[i + 1][j].rgbtRed) +
                                                     (image[i + 1][j - 1].rgbtRed)) / 4.0);
                    blurImage[i][j].rgbtGreen = round(((image[i][j].rgbtGreen) + (image[i][j - 1].rgbtGreen) + (image[i + 1][j].rgbtGreen) +
                                                       (image[i + 1][j - 1].rgbtGreen)) / 4.0);
                    blurImage[i][j].rgbtBlue = round(((image[i][j].rgbtBlue) + (image[i][j - 1].rgbtBlue) + (image[i + 1][j].rgbtBlue) +
                                                      (image[i + 1][j - 1].rgbtBlue)) / 4.0);
                }
                else if (i == (height - 1) && j == 0)
                {
                    // Bottom Left
                    blurImage[i][j].rgbtRed = round(((image[i][j].rgbtRed) + (image[i][j + 1].rgbtRed) + (image[i - 1][j].rgbtRed) +
                                                     (image[i - 1][j + 1].rgbtRed)) / 4.0);
                    blurImage[i][j].rgbtGreen = round(((image[i][j].rgbtGreen) + (image[i][j + 1].rgbtGreen) + (image[i - 1][j].rgbtGreen) +
                                                       (image[i - 1][j + 1].rgbtGreen)) / 4.0);
                    blurImage[i][j].rgbtBlue = round(((image[i][j].rgbtBlue) + (image[i][j + 1].rgbtBlue) + (image[i - 1][j].rgbtBlue) +
                                                      (image[i - 1][j + 1].rgbtBlue)) / 4.0);
                }
                else if (i == (height - 1) && j == (width - 1))
                {
                    // Bottom Right
                    blurImage[i][j].rgbtRed = round(((image[i][j].rgbtRed) + (image[i][j - 1].rgbtRed) + (image[i - 1][j].rgbtRed) +
                                                     (image[i - 1][j - 1].rgbtRed)) / 4.0);
                    blurImage[i][j].rgbtGreen = round(((image[i][j].rgbtGreen) + (image[i][j - 1].rgbtGreen) + (image[i - 1][j].rgbtGreen) +
                                                       (image[i - 1][j - 1].rgbtGreen)) / 4.0);
                    blurImage[i][j].rgbtBlue = round(((image[i][j].rgbtBlue) + (image[i][j - 1].rgbtBlue) + (image[i - 1][j].rgbtBlue) +
                                                      (image[i - 1][j - 1].rgbtBlue)) / 4.0);
                }
                // Non Corners
                // Top Edge
                if (i == 0 && j != 0 && j != (width - 1))
                {
                    blurImage[i][j].rgbtRed = round(((image[i][j].rgbtRed) + (image[i][j - 1].rgbtRed) + (image[i][j + 1].rgbtRed) +
                                                     (image[i + 1][j - 1].rgbtRed) + (image[i + 1][j].rgbtRed) + (image[i + 1][j + 1].rgbtRed)) / 6.0);
                    blurImage[i][j].rgbtGreen = round(((image[i][j].rgbtGreen) + (image[i][j - 1].rgbtGreen) + (image[i][j + 1].rgbtGreen) +
                                                       (image[i + 1][j - 1].rgbtGreen) + (image[i + 1][j].rgbtGreen) + (image[i + 1][j + 1].rgbtGreen)) / 6.0);
                    blurImage[i][j].rgbtBlue = round(((image[i][j].rgbtBlue) + (image[i][j - 1].rgbtBlue) + (image[i][j + 1].rgbtBlue) +
                                                      (image[i + 1][j - 1].rgbtBlue) + (image[i + 1][j].rgbtBlue) + (image[i + 1][j + 1].rgbtBlue)) / 6.0);
                }
                // Bottom Edge
                if (i == (height - 1) && j != 0 && j != (width - 1))
                {
                    blurImage[i][j].rgbtRed = round(((image[i][j].rgbtRed) + (image[i][j - 1].rgbtRed) + (image[i][j + 1].rgbtRed) +
                                                     (image[i - 1][j - 1].rgbtRed) + (image[i - 1][j].rgbtRed) + (image[i - 1][j + 1].rgbtRed)) / 6.0);
                    blurImage[i][j].rgbtGreen = round(((image[i][j].rgbtGreen) + (image[i][j - 1].rgbtGreen) + (image[i][j + 1].rgbtGreen) +
                                                       (image[i - 1][j - 1].rgbtGreen) + (image[i - 1][j].rgbtGreen) + (image[i - 1][j + 1].rgbtGreen)) / 6.0);
                    blurImage[i][j].rgbtBlue = round(((image[i][j].rgbtBlue) + (image[i][j - 1].rgbtBlue) + (image[i][j + 1].rgbtBlue) +
                                                      (image[i - 1][j - 1].rgbtBlue) + (image[i - 1][j].rgbtBlue) + (image[i - 1][j + 1].rgbtBlue)) / 6.0);
                }

            }
            else if (j == 0 || j == (width - 1))
            {
                // Right Edge
                if ((j == 0 && i > 0) || (j == 0 && i < (height - 1) && i != 0))
                {
                    blurImage[i][j].rgbtRed = round(((image[i][j].rgbtRed) + (image[i - 1][j].rgbtRed) + (image[i + 1][j].rgbtRed) +
                                                     (image[i][j + 1].rgbtRed) + (image[i - 1][j + 1].rgbtRed) + (image[i + 1][j + 1].rgbtRed)) / 6.0);
                    blurImage[i][j].rgbtGreen = round(((image[i][j].rgbtGreen) + (image[i - 1][j].rgbtGreen) + (image[i + 1][j].rgbtGreen) +
                                                       (image[i][j + 1].rgbtGreen) + (image[i - 1][j + 1].rgbtGreen) + (image[i + 1][j + 1].rgbtGreen)) / 6.0);
                    blurImage[i][j].rgbtBlue = round(((image[i][j].rgbtBlue) + (image[i - 1][j].rgbtBlue) + (image[i + 1][j].rgbtBlue) +
                                                      (image[i][j + 1].rgbtBlue) + (image[i - 1][j + 1].rgbtBlue) + (image[i + 1][j + 1].rgbtBlue)) / 6.0);
                }
                // Left Edge
                if ((j == (width - 1) && i > 0) || (j == (width - 1) && i < (height - 1) && i != 0))
                {
                    blurImage[i][j].rgbtRed = round(((image[i][j].rgbtRed) + (image[i - 1][j].rgbtRed) + (image[i + 1][j].rgbtRed) +
                                                     (image[i][j - 1].rgbtRed) + (image[i - 1][j - 1].rgbtRed) + (image[i + 1][j - 1].rgbtRed)) / 6.0);
                    blurImage[i][j].rgbtGreen = round(((image[i][j].rgbtGreen) + (image[i - 1][j].rgbtGreen) + (image[i + 1][j].rgbtGreen) +
                                                       (image[i][j - 1].rgbtGreen) + (image[i - 1][j - 1].rgbtGreen) + (image[i + 1][j - 1].rgbtGreen)) / 6.0);
                    blurImage[i][j].rgbtBlue = round(((image[i][j].rgbtBlue) + (image[i - 1][j].rgbtBlue) + (image[i + 1][j].rgbtBlue) +
                                                      (image[i][j - 1].rgbtBlue) + (image[i - 1][j - 1].rgbtBlue) + (image[i + 1][j - 1].rgbtBlue)) / 6.0);
                }
            }
            else
            {
                // Non Edges
                blurImage[i][j].rgbtRed = round(((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed) +
                                                 (image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed) +
                                                 (image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed)) / 9.0);
                blurImage[i][j].rgbtGreen = round(((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen) +
                                                   (image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen) +
                                                   (image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen)) / 9.0);
                blurImage[i][j].rgbtBlue = round(((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue) +
                                                  (image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue) +
                                                  (image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue)) / 9.0);
            }
        }
    }
    // Copy new image into old one
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blurImage[i][j];
        }
    }
    return;
}
