#include "PPMImage.h"

/**
 * Consturctor.
 * 
 * Initializes image to NULL.
 * 
 */
PPMImage::PPMImage(void)
{
	image = NULL;
}

/**
 * Destruct.
 * 
 * Cleans up image memory. Returning it back to the OS.
 */
PPMImage::~PPMImage(void)
{
	if (image != NULL)
		delete[] image;
}

/**
 * Allocates memory for an image.
 *
 * This dynamically creates an array of width*height*3, the three comes from 
 * RGB. Each color is byte.
 * 
 * \param width
 * \param height
 */
void PPMImage::AllocateMemory(int width, int height)
{
	this->width = width;
	this->height = height;
	image = new unsigned char[width * height * 3];
}

/**
 * Reads in PPM to be stored to image variable.
 * 
 * \param fileName	- filename of an existing file.
 */
void PPMImage::ReadFile(string fileName)
{
	file.open(fileName, ios_base::binary);

	if (!file.is_open())
	{
		cout << fileName << " couldn't be opened.\n";
		system("pause");
		exit(1);
	}

	string fileType;
	file >> fileType;

	CheckComment();
	file >> width >> height;
	image = new unsigned char[width * height * 3];

	int maxValue;

	file >> maxValue;

	if (fileType == "P3")
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width * 3; j++)
			{
				string temp;
				file >> temp;
				image[i * width * 3 + j] = (unsigned char)atoi(temp.c_str());
			}
		}
	}

	else if (fileType == "P6")
	{
		file.getline(buf, 127);
		file.read((char*)image, height * width * 3);
	}

	file.close();
}

/**
 * Writes an image to a file.
 * 
 * \param fileName	-	Name of the output file.
 * \param fileType	-	file type. (P3/P6).
 */
void PPMImage::WriteFile(string fileName, string fileType)
{
	// Read and understand the code.
	if (fileType == "P6")
	{
		outFile.open(fileName, ios_base::binary);

		if (!outFile.is_open())
		{
			cout << fileName << " couldn't be opened.\n";
			system("pause");
			exit(1);
		}

		outFile << fileType << endl;
		outFile << width << " " << height << endl;
		outFile << 255 << endl;

		outFile.write((char*)image, height * width * 3);
	}
	else if (fileType == "P3")
	{
		outFile.open(fileName);

		if (!outFile.is_open())
		{
			cout << fileName << " couldn't be opened.\n";
			system("pause");
			exit(1);
		}

		outFile << fileType << endl;
		outFile << width << " " << height << endl;
		outFile << 255 << endl;

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width * 3; j++)
			{
				outFile << (int)image[i * width * 3 + j] << " ";
			}
			outFile << endl;
		}
	}
	outFile.close();
}

/**
 * Checks to see if there is a comment.
 * 
 * This simply moves current line past any comments.
 */
void PPMImage::CheckComment()
{
	c = file.peek();

	while (c == '#' || c == '\n' || c == ' ')
	{
		file.getline(buf, 127);
		c = file.peek();
	}
}

/**
 * Vertically flips the image.
 * 
 * Create a temp image and saves the temp image in place of the 
 * image variable.
 */
void PPMImage::VerticalFlip()
{
	unsigned char* flippedImage;
	flippedImage = new unsigned char[width * height * 3];
	// Do a vertical flip.  You need to use the help variable declared above.
	// Also do dynamic memory allocation for the variable based on the image size.
	int t = 0;
	for (int i = height -1; i >= 0; i--)
	{
		for (int j = 0; j < width * 3; j++)
		{
			flippedImage[t * width * 3 + j] = (int)image[i * width * 3 + j];
		}
		t++;
	}
	delete [] image;
	// assign the flippedImage to the image.
	image = flippedImage;

}