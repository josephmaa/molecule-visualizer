#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main (int argc, char**argv) {
    // Grab the command line arguments for parsing the input file.
    std::vector<std::string> args(argv + 1, argv + argc);
    std::string infname, outfname;

    // Loop over command-line args.
    for (auto i = args.begin(); i != args.end(); ++i) {
        if (*i == "-h" || *i == "--help") {
            std::cout << "Generates a qml file from an xyz formatted chemical." << std::endl;
            return 0;
        } else if (*i == "-i") {
            infname = *++i;
        } else if (*i == "-o") {
            outfname = *++i;
        }
    }

    std::ofstream qml_file;
    qml_file.open(outfname);
    // Header for qml files. 
    const char * header = R"(import QtQuick 2.1

Item {
    //! [1]
    property alias model: dataModel
    property alias modelTwo: dataModelTwo
    property alias modelThree: dataModelThree
    //! [1])";
    qml_file << header;

    // Read in the input xyz molecular file format.
    std::ifstream input_file(infname);
    std::string line;
    float x, y, z;
    int num_molecules;

    // Get the number of molecules in the file.
    input_file >> num_molecules;

    // Skip a line referencing extra header information.
    std::getline(input_file, line);

    // Read in the actual atom coordinates.
    for (int _ = 0; _ < num_molecules; _++) {
        std::getline(input_file, line);
        std::cout << line << std::endl;
    }

    qml_file.close();
    return 0;
}