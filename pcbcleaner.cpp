/*
* Cleans up eagle brd files, main intention is to remove silkscreen before manufactoring.
* by Pascal Schwarz
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char *argv[])
{
    int lineok = 0;
    std::string line;
    std::string searchtext;
    std::string outputfilename;
    std::ifstream infile;
    std::ofstream outfile;

    if(argc == 1)
    {
        std::cout << "No file given, exiting!" << std::endl;
        return 1;
    }

    if(std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h")
    {
        std::cout << "Usage:" << std::endl;
        std::cout << argv[0] << " [Layers] [File]" << std::endl;
        std::cout << "Layers: default is all silk layers: 21, 22, 25, 26, 27 ,28" << std::endl;
        std::cout << "Example: " << argv[0] << " 21 22 demo.brd" << std::endl;
        return 0;
    }

    infile.open(argv[argc-1]);

    if (!infile.is_open())
    {
        std::cout << "Unable to open file: " << argv[argc-1] << std::endl;
        return 1;
    }

    //opens or creates output file with modified name
    outputfilename = argv[argc-1];
    outputfilename.erase(outputfilename.find(".brd",0), 4);
    outputfilename += "_clean.brd";    
    outfile.open(outputfilename);

    if(!outfile.is_open())
    {
        std::cout << "Unable to open file: " << "outputfile.brd" << std::endl;
    }

    while (getline(infile, line))
    {
        lineok = 1;

        if(argc > 2){
            //remove given layers
            for(int i = 1; i < argc-1; i++)
            {
                searchtext.clear();
                searchtext += "layer=\"";
                searchtext += argv[i];
                searchtext += "\"";

                if(line.find(searchtext, 0) != std::string::npos) lineok = 0;
            }
        }
        else
        {
            //default settings, remove all silk layers
            if(line.find("layer=\"21\"",0) != std::string::npos) lineok = 0;
            if(line.find("layer=\"22\"",0) != std::string::npos) lineok = 0;
            if(line.find("layer=\"25\"",0) != std::string::npos) lineok = 0;
            if(line.find("layer=\"26\"",0) != std::string::npos) lineok = 0;
            if(line.find("layer=\"27\"",0) != std::string::npos) lineok = 0;
            if(line.find("layer=\"28\"",0) != std::string::npos) lineok = 0;
        }

        //if line does not contain any of the layers to be removed add it to output file
        if(lineok == 1)
            outfile << line << '\n';
    }

    std::cout << "PCBcleaner done! Please check result file for errors!" << std::endl;

    infile.close(); 
    outfile.close(); 
}