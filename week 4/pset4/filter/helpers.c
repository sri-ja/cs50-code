#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            BYTE value = round(average);
            image[i][j].rgbtBlue = value;
            image[i][j].rgbtGreen = value;
            image[i][j].rgbtRed = value;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int till = width / 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < till; j++)
        {
            BYTE btemp = image[i][j].rgbtBlue;
            BYTE gtemp = image[i][j].rgbtGreen;
            BYTE rtemp = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;

            image[i][width - 1 - j].rgbtBlue = btemp;
            image[i][width - 1 - j].rgbtGreen = gtemp;
            image[i][width - 1 - j].rgbtRed = rtemp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // creating a copy array to retain the original values to ensure we implement the blurring effect properly
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //deciding which neighboring elements to loop through
            int top = i - 1;
            int bottom = i + 1;
            int left = j - 1;
            int right = j + 1;

            //adjusting values if it happens to be out of the bounds of the array
            if (top < 0)
            {
                top = i;
            }
            if (bottom > (height - 1))
            {
                bottom = i;
            }
            if (left < 0)
            {
                left = j;
            }
            if (right > (width - 1))
            {
                right = j;
            }

            //adding up all the elements, and then finding the average wisely
            int bsum = 0;
            int gsum = 0;
            int rsum = 0;
            int count = 0;

            for (int k = top; k <= bottom; k++)
            {
                for (int l = left; l <= right; l++)
                {
                    bsum = bsum + copy[k][l].rgbtBlue;
                    gsum = gsum + copy[k][l].rgbtGreen;
                    rsum = rsum + copy[k][l].rgbtRed;
                    count++;
                }
            }

            float bavg = bsum / ((float)count);
            float gavg = gsum / ((float)count);
            float ravg = rsum / ((float)count);

            image[i][j].rgbtBlue = round(bavg);
            image[i][j].rgbtGreen = round(gavg);
            image[i][j].rgbtRed = round(ravg);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //making a copy array and also ensuring i give border pixels
    RGBTRIPLE copy[height + 2][width + 2];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i + 1][j + 1].rgbtBlue = image[i][j].rgbtBlue;
            copy[i + 1][j + 1].rgbtGreen = image[i][j].rgbtGreen;
            copy[i + 1][j + 1].rgbtRed = image[i][j].rgbtRed;
        }
    }

    //assigning the border pixels
    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (i == 0 || j == 0 || i == height + 1 || j == width + 1)
            {
                copy[i][j].rgbtBlue = 0;
                copy[i][j].rgbtGreen = 0;
                copy[i][j].rgbtRed = 0;
            }
        }
    }

    //initializing the gx kernal
    int gx[3][3] = 
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    //initializing the gy kernal
    int gy[3][3] = 
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            int top = i - 1;
            int bottom = i + 1;
            int left = j - 1;
            int right = j + 1;

            int rx = 0;
            int ry = 0;
            int grx = 0;
            int gry = 0;
            int bx = 0;
            int by = 0;

            for (int k = top; k <= bottom; k++)
            {
                for (int l = left; l <= right; l++)
                {
                    //here's where we do the kernal manipulation things basically with things from the copy array
                    rx = rx + (copy[k][l].rgbtRed * gx[k - top][l - left]);
                    ry = ry + (copy[k][l].rgbtRed * gy[k - top][l - left]);

                    grx = grx + (copy[k][l].rgbtGreen * gx[k - top][l - left]);
                    gry = gry + (copy[k][l].rgbtGreen * gy[k - top][l - left]);

                    bx = bx + (copy[k][l].rgbtBlue * gx[k - top][l - left]);
                    by = by + (copy[k][l].rgbtBlue * gy[k - top][l - left]);
                }
            }

            float ravg = sqrt((rx * rx) + (ry * ry));
            float gavg = sqrt((grx * grx) + (gry * gry));
            float bavg = sqrt((bx * bx) + (by * by));

            int rfinal = round(ravg);
            if (rfinal > 255)
            {
                rfinal = 255;
            }

            int gfinal = round(gavg);
            if (gfinal > 255)
            {
                gfinal = 255;
            }

            int bfinal = round(bavg);
            if (bfinal > 255)
            {
                bfinal = 255;
            }

            image[i - 1][j - 1].rgbtBlue = bfinal;
            image[i - 1][j - 1].rgbtGreen = gfinal;
            image[i - 1][j - 1].rgbtRed = rfinal;
        }
    }
    return;
}
