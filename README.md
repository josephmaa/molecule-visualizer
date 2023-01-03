### Molecule visualizer

Converts xyz file formats into qml formats for use with the QDataVisualization module in QT for visualizing molecules.

#### Installation:
1. Clone the repository locally.
2. Run the command `ccmake .` Configure and generate the Makefile from cmakelists.txt.
3. Run `make` to generate `molecule_visualizer` executable.

#### To run:
1. The `make` command generates an executable file to the root directory of the project. To run, execute the command `./molecule_visualizer -i <input_xyz_file> -o <output_qml_file>`.

Tested on the following hardware:

Model Name:	MacBook Pro
Model Identifier:	MacBookPro16,3
Processor Name:	Quad-Core Intel Core i5
Processor Speed:	1.4 GHz
Number of Processors:	1
Total Number of Cores:	4