#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "../Headers/coordinates.h"

int main(int argc, char **argv)
{
    // Grab the command line arguments for parsing the input file.
    std::vector<std::string> args(argv + 1, argv + argc);
    std::string infname, outfname;

    // Loop over command-line args.
    for (auto i = args.begin(); i != args.end(); ++i)
    {
        if (*i == "-h" || *i == "--help")
        {
            std::cout << "Generates a qml file from an xyz formatted chemical." << std::endl;
            return 0;
        }
        else if (*i == "-i")
        {
            infname = *++i;
        }
        else if (*i == "-o")
        {
            outfname = *++i;
        }
    }

    std::ofstream qml_file;
    qml_file.open(outfname);
    // Header for qml files.
    const char *header = R"(import QtQuick 2.1

Item {
    property alias model: dataModel
    property alias modelTwo: dataModelTwo
    property alias modelThree: dataModelThree
    )";
    qml_file << header;

    // Read in the input xyz molecular file format.
    std::ifstream input_file(infname);
    std::string line;
    std::string atom_type;
    float x, y, z;
    int num_molecules;

    // Get the number of molecules in the file.
    input_file >> num_molecules;

    // Add containers to hold the cartesian coordinates of the atoms.
    std::vector<Coordinates> carbons;
    std::vector<Coordinates> hydrogens;
    std::vector<Coordinates> oxygens;

    // Read in the actual atom coordinates.
    int NUM_HEADER_LINES = 2;
    for (int line_index = 0; line_index < num_molecules + NUM_HEADER_LINES; line_index++)
    {
        std::getline(input_file, line);
        // Skip header information.
        if (line_index == 0 or line_index == 1)
        {
            continue;
        }

        // Read in the atoms and their cartesian coordinates.
        std::istringstream split_line(line);
        split_line >> atom_type >> x >> y >> z;

        Coordinates coordinates{x, y, z};
        // We currently only handle carbons, hydrogens, and oxygens.
        if (atom_type == "C")
        {
            carbons.push_back(coordinates);
        }
        else if (atom_type == "H")
        {
            hydrogens.push_back(coordinates);
        }
        else if (atom_type == "O")
        {
            oxygens.push_back(coordinates);
        }
    }

    // Add dataModel ids to ListModels.
    std::vector<std::string> ids{"dataModel", "dataModelTwo", "dataModelThree"};

    std::unordered_map<std::string, std::vector<Coordinates>> ids_to_coordinates;

    ids_to_coordinates["dataModel"] = carbons;
    ids_to_coordinates["dataModelTwo"] = hydrogens;
    ids_to_coordinates["dataModelThree"] = oxygens;

    // TODO: Replace with ostringstream
    std::string list_model;

    for (int id_idx = 0; id_idx < ids.size(); ++id_idx)
    {
        std::string id = ids[id_idx];
        list_model += "ListModel {\n";
        // TODO: Upgrade GCC to use C++20 and use std::format.
        list_model += "    id: " + id + "\n";
        for (Coordinates coordinate : ids_to_coordinates[id])
        {
            list_model += "        ListElement{ xPos: " + std::to_string(coordinate.x) + " ; yPos: " + std::to_string(coordinate.y) + " ; zPos: " + std::to_string(coordinate.z) + " }\n";
        }
        list_model += "}\n";
        qml_file << list_model;

        list_model.clear();
    }
    list_model += "}\n";
    qml_file << list_model;

    qml_file.close();
    return 0;
}