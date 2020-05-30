#include "protos.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //Declares variable which will later be used to calculate average color
    float avrg;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            //Calculates average value for Red Blue and Green values of each pixel.
            avrg = round(((round(image[j][i].rgbtBlue) + round(image[j][i].rgbtGreen) + round(image[j][i].rgbtRed)) / 3.000));
            image[j][i].rgbtBlue = avrg; //Applies the average value to each pixel's red green and blue values.
            image[j][i].rgbtGreen = avrg;
            image[j][i].rgbtRed = avrg;
        }
    }
}



// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
                {
                //Initializes Sepia effect variables based on the "formula" for sepia effect.
                int sepiaRed = round(.393 * image[j][i].rgbtRed + .769 * image[j][i].rgbtGreen + .189 * image[j][i].rgbtBlue);
                int sepiaGreen = round(.349 * image[j][i].rgbtRed + .686 * image[j][i].rgbtGreen + .168 * image[j][i].rgbtBlue);
                int sepiaBlue = round(.272 * image[j][i].rgbtRed + .534 * image[j][i].rgbtGreen + .131 * image[j][i].rgbtBlue);

                //Prevents overflow of RGB values.
                if( sepiaRed > 255)
                sepiaRed = 255;
                if( sepiaGreen > 255)
                sepiaGreen = 255;
                if( sepiaBlue > 255)
                sepiaBlue = 255;

                //Applies the sepia effect on each RGB value of pixel.
                image[j][i].rgbtRed = sepiaRed;
                image[j][i].rgbtGreen = sepiaGreen;
                image[j][i].rgbtBlue = sepiaBlue;

                }
        }

}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    int hwid = width / 2; //Declares variable for half the length
    int tmpr = 0; //Declares variable for temporary colors (which will be used in swapping)
    int tmpg = 0;
    int tmpb = 0;
    int tmpr1 = 0; //Second time, because I've used a separate for loop for another half of the image.
    int tmpg1 = 0;
    int tmpb1 = 0;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {

        if (i <= hwid) //Gets pixels from first half of the image and stores them into temporary variables
        {
            tmpr = image[j][i + (2*(hwid - i))].rgbtRed;
            tmpg = image[j][i + (2*(hwid - i))].rgbtGreen;
            tmpb = image[j][i + (2*(hwid - i))].rgbtBlue;
        }
        else if (i > hwid) //Gets pixels from second half of the image and stores them into second temporary variables.
        {
            tmpr1 = image[j][i - (2*(i - hwid))].rgbtRed;
            tmpg1 = image[j][i - (2*(i - hwid))].rgbtGreen;
            tmpb1 = image[j][i - (2*(i - hwid))].rgbtBlue;
        }

        if (i <= hwid) //Applies the themporary variables to pixels RGB values
        {
            image[j][i].rgbtRed = tmpr;
            image[j][i].rgbtGreen = tmpg;
            image[j][i].rgbtBlue = tmpb;

        }
        else if (i > hwid) //Applies the themporary variables to pixels RGB values
        {
            image[j][i].rgbtRed = tmpr1;
            image[j][i].rgbtGreen = tmpg1;
            image[j][i].rgbtBlue = tmpb1;
        }


        }
    }

}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width]; //Declaring temporary RGB values for later usage below.

    int lurj;
    int mwv;
    int wtl;
    float cntr; //Counter for usage in calculating average.


    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            lurj = 0;
            mwv = 0;
            wtl = 0;
            cntr = 0.00;

            for (int k = -1; k < 2; k++)
            {
                if (j + k < 0 || j + k > height - 1) //Prevents the chance of neighboring pixels going out of borders
                {
                    continue;
                }

                for (int h = -1; h < 2; h++)
                {
                    if (i + h < 0 || i + h > width - 1)//Prevents the chance of neighboring pixels going out of borders
                    {
                        continue;
                    }


                    cntr++;//Increments counter for calculation of average.
                    lurj += image[j + k][i + h].rgbtBlue;
                    mwv += image[j + k][i + h].rgbtGreen;
                    wtl += image[j + k][i + h].rgbtRed;

                }
            }

            //Stores the calculated average values in respective RGB temporary values.
            temp[j][i].rgbtBlue = round(lurj / cntr);
            temp[j][i].rgbtGreen = round(mwv / cntr);
            temp[j][i].rgbtRed = round(wtl / cntr);
        }
    }


    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        { //Applies temporary values to final value.
            image[j][i].rgbtBlue = temp[j][i].rgbtBlue;
            image[j][i].rgbtGreen = temp[j][i].rgbtGreen;
            image[j][i].rgbtRed = temp[j][i].rgbtRed;
        }
    }

}
