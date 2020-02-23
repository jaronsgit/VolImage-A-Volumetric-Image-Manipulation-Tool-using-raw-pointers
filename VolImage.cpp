#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "VolImage.h"

#define PRINT(x) std::cout << x;

CHNJAR003::VolImage::VolImage() : width(0), height(0){};

CHNJAR003::VolImage::~VolImage()
{

    for (int i = 0; i < slices.size(); i++) //Loop through all the individual 2D slices
    {
        for (int j = 0; j < height; j++) //Loop through the rows of each 2D slice
        {
            delete[] slices[i][j]; //Destroy each row
        }
        delete[] slices[i]; //Destroy the slice itself
    }
}

bool CHNJAR003::VolImage::readImages(std::string baseName)
{
    std::ifstream baseNameFile;

    baseNameFile.open((baseName + ".data").c_str());

    if (!baseNameFile)
    {
        std::cerr << "File with base name: " << baseName << " could not be opened for reading.";
    }
    else
    {
        CHNJAR003::VolImage::slices.clear();

        while (!baseNameFile.eof())
        {
            std::string line;
            getline(baseNameFile, line);

            std::istringstream iss(line);
            std::string token;
            std::vector<std::string> tokens;

            while (getline(iss, token, ' '))
            {
                tokens.push_back(token);
            }

            for (std::string temp : tokens)
            {
                PRINT(temp + '\n');
            }
        }
    }

    return false;
}