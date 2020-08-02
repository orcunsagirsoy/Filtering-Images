#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float rgbtGray;

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            rgbtGray = round(image[j][i].rgbtBlue + image[j][i].rgbtGreen + image[j][i].rgbtRed) / 3;

            image[j][i].rgbtBlue = rgbtGray;
            image[j][i].rgbtGreen = rgbtGray;
            image[j][i].rgbtRed = rgbtGray;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaBlue;
    float sepiaGreen;
    float sepiaRed;

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            sepiaBlue = (round(0.272 * image[j][i].rgbtRed + 0.534 * image[j][i].rgbtGreen + 0.131 * image[j][i].rgbtBlue));
            sepiaGreen = (round(0.349 * image[j][i].rgbtRed + 0.686 * image[j][i].rgbtGreen + 0.168 * image[j][i].rgbtBlue));
            sepiaRed = (round(0.393 * image[j][i].rgbtRed + 0.769 * image[j][i].rgbtGreen + 0.189 * image[j][i].rgbtBlue));

            image[j][i].rgbtBlue = sepiaBlue;
            image[j][i].rgbtGreen = sepiaGreen;
            image[j][i].rgbtRed = sepiaRed;
        }
    }


    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int T[3];  //temporary array for swaping

    for(int j = 0; j < height; j++)
    {
        for(int i = 0; i < width / 2; i++) //width/2 is for centeral rotation!!!!
        {


            T[0] = image[j][i].rgbtBlue;
            T[1] = image[j][i].rgbtGreen;
            T[2] = image[j][i].rgbtRed;

            image[j][i].rgbtBlue = image[j][width - i - 1].rgbtBlue;
            image[j][i].rgbtGreen = image[j][width - i - 1].rgbtGreen;
            image[j][i].rgbtRed = image[j][width - i - 1].rgbtRed;

            image[i][width - i - 1].rgbtBlue = T[0];
            image[i][width - i - 1].rgbtGreen = T[1];
            image[i][width - i - 1].rgbtRed = T[2];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int sumBlue;
    int sumGreen;
    int sumRed;
    float count;

    RGBTRIPLE T[height][width];

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            sumBlue = 0;
            sumGreen = 0;
            sumRed = 0;
            count = 0.00;

            for(int k = -1; k < 2; k++)
            {
                if(k + j < 0 || k + j > height -1)
                {
                    continue;
                }

                for(int l = -1; l < 2; l++)
                {
                    if(l + i < 0 || l + i > width -1)
                    {
                        continue;
                    }

                    sumBlue += image[j + k][i + l].rgbtBlue;
                    sumGreen += image[j + k][i + l].rgbtGreen;
                    sumRed += image[j + k][i + l].rgbtRed;
                    count++;
                }
            }

            T[j][i].rgbtBlue = round(sumBlue / count);
            T[j][i].rgbtGreen = round(sumGreen / count);
            T[j][i].rgbtRed = round(sumRed / count);
        }
    }

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            image[j][i].rgbtBlue = T[j][i].rgbtBlue;
            image[j][i].rgbtGreen = T[j][i].rgbtGreen;
            image[j][i].rgbtRed = T[j][i].rgbtRed;
        }
    }


    return;
}
