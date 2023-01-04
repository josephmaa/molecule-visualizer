#ifndef COORDINATES_H
#define COORDINATES_H

class Coordinates {
    public: 
        float x;
        float y;
        float z;

        // Setter function.
        void set_coordinates(const float x, const float y, const float z);
        // Compare two coordinate objects.
        bool operator== (Coordinates & rhs_coord);        
};



#endif