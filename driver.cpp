#include <iostream>
#include <string>
#include "VolImage.h"

#define PRINT(x) std::cout << x;

int main(int argc, char *argv[])
{
    PRINT(argc + "\n");

    if (argc == 2)
    {
        std::string imageBase = argv[1];

        CHNJAR003::VolImage *temp = new CHNJAR003::VolImage();
        temp->readImages(imageBase);
        //PRINT("Number of bytes required: " + std::to_string(temp->volImageSize()) + "\n");

        delete temp;
    }
    else if (argc > 2)
    {
        std::string imageBase = argv[1];
        //PRINT("imageBase=" + imageBase + "\n");

        std::string flag1 = argv[2];
        //PRINT("flag1=" + flag1 + "\n");
        if (flag1 == "-d")
        {
            if (argc == 6)
            {
                int imageI = std::stoi(argv[3]);
                int imageJ = std::stoi(argv[4]);
                std::string outputFileName = argv[5];

                CHNJAR003::VolImage *temp = new CHNJAR003::VolImage();

                temp->readImages(imageBase);
                temp->diffmap(imageI, imageJ, outputFileName);
                //PRINT("Number of bytes required: " + std::to_string(temp->volImageSize()) + "\n");

                delete temp;
            }
            else
            {
                std::cerr << "Incorrect flag parameters passed in for -d (difference map).";
            }
        }
        else if (flag1 == "-x")
        {
            if (argc == 5)
            {
                int imageI = std::stoi(argv[3]);
                std::string outputFileName = argv[4];

                CHNJAR003::VolImage *temp = new CHNJAR003::VolImage();

                temp->readImages(imageBase);
                temp->extract(imageI, outputFileName);
                //PRINT("Number of bytes required: " + std::to_string(temp->volImageSize()) + "\n");

                delete temp;
            }
            else
            {
                std::cerr << "Incorrect flag parameters passed in for -x (slice extraction).";
            }
        }
    }

    return 0;
}