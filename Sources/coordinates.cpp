#include "../Headers/coordinates.h"

Coordinates::Coordinates(const float x_coord, const float y_coord, const float z_coord): x (x_coord), y (y_coord), z(z_coord) {}

void Coordinates::set_coordinates(const float x_coord, const float y_coord, const float z_coord) {
    x = x_coord;
    y = y_coord;
    z = z_coord;
}

bool Coordinates::operator== (const Coordinates &other_coordinates) {
    if(x == other_coordinates.x
          && y == other_coordinates.y
          && z == other_coordinates.z)
          return true;
     else
          return false;
}
