//author: Garrett Welton
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "bitmap.h"

using namespace std;

Bitmap image;
vector <vector <Pixel> > bmp;
vector <vector <vector <Pixel> > > combo;
Pixel rgb;
Pixel fRgb;

vector <vector <vector <Pixel> > > getImages()
{
	string imageName;
	int imageNumber;
	bool stop;
	int row;
	int col;
	int j, k;

	row = 0;
	col = 0;
	imageNumber = 0;

	stop = false;

	while(stop == false); // loop to enter files
	{
		cin >> imageName;

		if (imageName == "DONE" || imageNumber == 10) // ends loop
		{
			stop = true;
		}
		if (imageName == "DONE" && imageNumber < 2) // checks that they have more than 1 image 
		{
			cout << "composite image cannot be created" << endl;
		}
		else
		{
			image.open(imageName);

			bool validBmp = image.isImage();

			if (validBmp == true) // checks that its a valid file
			{
				bmp = image.toPixelMatrix(); // turns Bitmap into matrix

				if (row == 0) // if statement to enter the first line of the 3D vector
				{
					row = bmp.size();
					col = bmp[0].size();

					for (j = 0; j < row; j++)
					{
						for (k = 0; k < col; k++)
						{
							combo[imageNumber][j][k] = bmp[j][k];

							imageNumber++;
						}
					}
				}
				if (row == bmp.size() && col == bmp[0].size()) // if statement for other rows
				{
					for (j = 0; j < row; j++)
					{
						for (k = 0; k < col; k++)
						{
							combo[imageNumber][j][k] = bmp[j][k];

							imageNumber++;
						}
					}
				}
				else // tells user if image isnt the right size
				{
					cout << "file isn't the same dimensions as the first image loaded. Try again" << endl;
				}
			}

			else // telss user file doesnt exist
			{
				cout << "file doesn't exist or isn't a valid bitmap. Try again" << endl;
			}
		}
	}
		return combo; // returns 3D vector 
}

vector <vector <Pixel> > createComp(vector <vector <vector <Pixel> > > a)  
{
	for (int j = 0; j < a[0].size(); j++)
	{
		for (int k = 0; k < a.size(); k++)
		{
			for (int i = 0; i < a[0][0].size(); i++)
			{
				rgb = a[i][j][k]; //takes out a pixel from the matrix
					
				fRgb.red = 0;
				fRgb.green = 0;
				fRgb.blue = 0;
				
				fRgb.red = fRgb.red + (rgb.red / a[0][0].size());
				fRgb.green = fRgb.green + (rgb.green / a[0][0].size()); //combines the rgb values
				fRgb.blue = fRgb.blue + (rgb.blue / a[0][0].size());		
			}
			bmp[j][k] = fRgb; //puts rgb info of the new pixel and puts it into a 2D vector
		}
	}
	return bmp; // returns a 2D vector
}

int main()
{
	cout << "Enter the names of the files you want to use to create a composite" << endl;
	
	combo = getImages(); //takes files and puts them in a 3D vector
	
	bmp = createComp(combo); // function to compile images

	image.fromPixelMatrix(bmp); // turns matrix into a bitmap
    	image.save("composite-gwelton.bmp"); //saves the image



	return 0;
}
