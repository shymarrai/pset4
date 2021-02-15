#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE grey_pixel;

    for (int h = 0 ; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            grey_pixel = round((float)(image[h][w].rgbtBlue + image[h][w].rgbtGreen + image[h][w].rgbtRed) / 3);
            image[h][w].rgbtBlue = grey_pixel;
            image[h][w].rgbtGreen = grey_pixel;
            image[h][w].rgbtRed = grey_pixel;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE sepiaRed;
    BYTE sepiaGreen;
    BYTE sepiaBlue;

    for (int h = 0 ; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {

            if (round(.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue) > 255)
            {
                sepiaRed = 255;
            }
            else
            {
                sepiaRed = round(.393 * image[h][w].rgbtRed + .769 * image[h][w].rgbtGreen + .189 * image[h][w].rgbtBlue);
            }



            if (round(.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue) > 255)
            {
                sepiaGreen = 255;
            }
            else
            {
                sepiaGreen =  round(.349 * image[h][w].rgbtRed + .686 * image[h][w].rgbtGreen + .168 * image[h][w].rgbtBlue);
            }



            if (round(.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue) > 255)
            {
                sepiaBlue = 255;
            }
            else
            {
                sepiaBlue = round(.272 * image[h][w].rgbtRed + .534 * image[h][w].rgbtGreen + .131 * image[h][w].rgbtBlue);
            }

            image[h][w].rgbtRed = sepiaRed;
            image[h][w].rgbtGreen = sepiaGreen;
            image[h][w].rgbtBlue = sepiaBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE reflet_img[height][width];
    int mid = width / 2;
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < mid; w++)
        {
            reflet_img[h][w] = image[h][width - w - 1];
            image[h][width - w - 1] = image[h][w];
            image[h][w] = reflet_img[h][w];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_img[height][width];

    for (int h = 0 ; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {



            int red = 0, green = 0, blue = 0, count = 0;

            for (int a = h - 1 ; a <= h + 1; a++)
            {
                if ((a < 0) || (a > height - 1))
                {
                    continue;
                }
                for (int l = w - 1; l <= w + 1; l++)
                {
                    if ((l < 0) || (l > width - 1))
                    {
                        continue;
                    }

                    red += image[a][l].rgbtRed;
                    blue += image[a][l].rgbtBlue;
                    green += image[a][l].rgbtGreen;
                    count++;
                }
            }
            new_img[h][w].rgbtRed = round((float)red / count) ;
            new_img[h][w].rgbtGreen = round((float)green / count) ;
            new_img[h][w].rgbtBlue = round((float)blue / count) ;
        }
    }

    for (int h = 0 ; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = new_img[h][w];
        }
    }
}

