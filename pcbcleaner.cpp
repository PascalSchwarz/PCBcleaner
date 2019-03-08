/*
* Cleans up eagle brd files, main intention is to remove silkscreen before manufactoring.
* by Pascal Schwarz
*/

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[])
{
    std::string line;
    std::ifstream infile;
    std::ofstream outfile;

    if(argc == 1)
    {
        std::cout << "No file given, exiting!" << std::endl;
    }

    infile.open(argv[1]);
    outfile.open("outputfile.brd"); //TODO: have outputfile follow naming of inputfile

    if (!infile.is_open())
    {
        std::cout << "Unable to open file: " << argv[1] << std::endl;
    }

    if(!outfile.is_open())
    {
        std::cout << "Unable to open file: " << "outputfile.brd" << std::endl;
    }

    while ( getline (infile,line) )
    {
        //if line found does not contain tPlace put to output file
        if(line.find("layer=\"21\"",0) == std::string::npos)
            outfile << line << '\n';
    }

    infile.close(); 
}