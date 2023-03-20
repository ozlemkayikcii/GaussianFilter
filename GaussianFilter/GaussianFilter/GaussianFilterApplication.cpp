#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <time.h>
#include <cmath>

#define FILTERSIZE 9

using namespace std;




int main()
{
	ifstream infile;
	ofstream outfile;

	int imageSize;
	int filterSize;
	int whitePixel;
	int blackPixel;

	double image[9][9];
	double grid[21][21];
	double grid2[21][21];
	double shape[20][20];
	double shape2[20][20];

	double kernel[FILTERSIZE][FILTERSIZE] = { 0 };
	int d, i, j, f, h, w;
	double value;
	int temp;



	outfile.open("result.txt");

	outfile << fixed << showpoint;
	outfile << setprecision(4);
	cout.setf(ios::fixed);
	cout.precision(4);


	srand(time(NULL));

	infile.open("inputs.txt");

	if (!infile)
	{
		cout << "the file cannot be open..." << endl;
	}
	else
	{
		infile >> imageSize;
		infile >> filterSize;
		infile >> whitePixel;
		infile >> blackPixel;
		if (imageSize % 2 == 0 || filterSize % 2 == 0 || whitePixel < 0 || blackPixel < 0 || whitePixel > 255 || blackPixel > 255)
		{
			cout << "Please check the numbers odd or even.Filter and image size must be odd numbers." << endl;
			cout << "Please check the numbers. Pixel values must be positive integer and smaller than 256." << endl;

		}
		else if (imageSize > 9 || filterSize > 9 || imageSize < 0 || filterSize < 0)
		{
			cout << "Image size and filter size must be maximum 9 and minimum 1." << endl;
		}
		else {

			temp = imageSize;

			for (int i = 0; i < imageSize; i++)
			{
				for (int j = 0; j < imageSize; j++)
				{
					if (whitePixel > blackPixel)
						image[i][j] = rand() % (whitePixel - blackPixel + 1) + blackPixel;
				}
			}

			outfile << "   Input Image (" << imageSize << "x" << imageSize << ")" << endl;
			outfile << "---------------------------------------------" << endl;
			outfile << endl;
			cout << "   Input Image (" << imageSize << "x" << imageSize << ")" << endl;
			cout << "---------------------------------------------" << endl;
			cout << endl;

			for (int i = 0; i < imageSize; i++)
			{
				for (int j = 0; j < imageSize; j++)
				{
					outfile << right << setw(9) << image[i][j];
					cout << right << setw(9) << image[i][j];
				}
				cout << endl;
				outfile << endl << endl;
			}
			outfile << "---------------------------------------------" << endl;
			cout << "---------------------------------------------" << endl;
			outfile << endl << endl;
			cout << endl << endl << endl;

			f = filterSize / 2;
			for (d = 0; d < f; d++)
			{
				value = 1.0 / pow((2 * (d + 1) + 1), 2);
				for (i = -(d + 1); i <= d + 1; i++)
				{
					for (j = -(d + 1); j <= d + 1; j++)
						kernel[f - i][f - j] = kernel[f - i][f - j] + value;
				}

			}


			for (i = 0; i < filterSize; i++)
			{
				for (j = 0; j < filterSize; j++)
				{
					kernel[i][j] = kernel[i][j] / static_cast<double>(filterSize);
				}
			}
			outfile << "   Gaussian Filter (" << filterSize << "x" << filterSize << ")" << endl;
			outfile << "---------------------------" << endl;
			outfile << endl;
			cout << "   Gaussian Filter (" << filterSize << "x" << filterSize << ")" << endl;
			cout << "---------------------------" << endl;
			cout << endl;
			for (i = 0; i < filterSize; i++)
			{
				for (j = 0; j < filterSize; j++)
				{

					outfile << right << setw(9) << kernel[i][j];
					cout << right << setw(9) << kernel[i][j];

				}
				cout << endl;
				outfile << endl;
			}
			outfile << "---------------------------" << endl;
			cout << "---------------------------" << endl;
			outfile << endl << endl;
			outfile << endl << endl;
			cout << endl << endl << endl;

			for (int i = 0; i < 21; i++)
			{
				for (int j = 0; j < 21; j++)
				{
					grid[i][j] = 0;
					grid2[i][j] = 0;
				}
			}

			int ort1 = (21 - imageSize) / 2;
			int ort2 = (21 - temp) / 2;


			for (int i = 0; i < imageSize; i++)
			{
				for (int j = 0; j < imageSize; j++)
				{
					grid[ort1 + i][ort1 + j] = image[i][j];
				}

			}


			for (int j = 0; j < imageSize; j++)
			{
				grid[ort1 + j][ort1 - 1] = grid[ort1 + j][ort1];
				grid[ort1 - 1][ort1 + j] = grid[ort1][ort1 + j];
				grid[(ort1 + imageSize - 1) + 1][ort1 + j] = grid[ort1 + imageSize - 1][ort1 + j];
				grid[ort1 + j][(ort1 + imageSize - 1) + 1] = grid[ort1 + j][ort1 + imageSize - 1];


				grid[ort1 - 1][ort1 - 1] = grid[ort1][ort1 - 1];
				grid[ort1 - 1][ort1 + imageSize] = grid[ort1][ort1 + imageSize];
				grid[ort1 + imageSize][ort1 + imageSize] = grid[ort1 + imageSize - 1][ort1 + imageSize];
				grid[ort1 + imageSize][ort1 - 1] = grid[ort1 + imageSize - 1][ort1 - 1];
			}

			if (f > 1)
			{
				for (int i = 1; i < f; i++)
				{
					imageSize += 2;
					ort1 = (21 - imageSize) / 2;
					for (int j = 0; j < imageSize; j++)
					{
						grid[ort1 - 1][ort1 + j] = grid[ort1][ort1 + j];
						grid[(ort1 + imageSize - 1) + 1][ort1 + j] = grid[ort1 + imageSize - 1][ort1 + j];

					}
				}
			}
			imageSize += 2;
			ort1 = (21 - imageSize) / 2;

			outfile << "   Input Grid: Edge Mirrored Image (21x21)" << endl;
			outfile << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			outfile << endl;
			cout << "   Input Grid: Edge Mirrored Image (21x21)" << endl;
			cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			cout << endl;

			for (int i = 0; i < 21; i++)
			{
				for (int j = 0; j < 21; j++)
				{

					outfile << right << setw(9) << grid[i][j];
					cout << right << setw(9) << grid[i][j];
				}
				cout << endl;
				outfile << endl;
			}
			outfile << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			outfile << endl << endl << endl;
			cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			cout << endl << endl << endl;

			for (int i = 0; i < imageSize; i++)
			{
				for (int j = 0; j < imageSize; j++)
				{
					shape[i][j] = grid[ort1 + i][ort1 + j];
				}
			}


			int newImage = imageSize - filterSize + 1;

			for (i = 0; i < newImage; i++)
			{
				for (j = 0; j < newImage; j++)
				{
					for (h = i; h < i + filterSize; h++)
					{
						for (w = j; w < j + filterSize; w++)
						{
							grid2[ort2 + i][ort2 + j] += (kernel[h - i][w - j] / (filterSize * filterSize)) * shape[h][w];
						}
					}
				}

			}


			outfile << "   Output Grid: Cutted-Edge Image (21x21)" << endl;
			outfile << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			outfile << endl;
			cout << "   Output Grid: Cutted-Edge Image (21x21)" << endl;
			cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			cout << endl;
			for (int i = 0; i < 21; i++)
			{
				for (int j = 0; j < 21; j++)
				{

					outfile << right << setw(9) << grid2[i][j];
					cout << right << setw(9) << grid2[i][j];
				}
				cout << endl;
				outfile << endl;
			}
			outfile << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			cout << "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
			outfile << endl << endl << endl;
			cout << endl << endl << endl;

			for (int i = 0; i < imageSize; i++)
			{
				for (int j = 0; j < imageSize; j++)
				{
					shape2[i][j] = grid2[ort2 + i][ort2 + j];
				}
			}

			outfile << "   Output (Filtered) Image (" << temp << "x" << temp << ")" << endl;
			outfile << "---------------------------------------------" << endl;
			outfile << endl;
			cout << "   Output (Filtered) Image (" << temp << "x" << temp << ")" << endl;
			cout << "---------------------------------------------" << endl;
			cout << endl;
			for (int i = 0; i < temp; i++)
			{
				for (int j = 0; j < temp; j++)
				{
					outfile << right << setw(9) << shape2[i][j];
					cout << right << setw(9) << shape2[i][j];
				}
				outfile << endl;
				cout << endl;
			}
			outfile << "---------------------------------------------" << endl;
			cout << "---------------------------------------------" << endl;

			infile.close();
			outfile.close();
		}
	}
	return 0;
}

