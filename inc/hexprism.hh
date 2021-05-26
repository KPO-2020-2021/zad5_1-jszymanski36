#pragma once

#include "cuboid.hh"

class HexPrism: public Solid {

  private:

    Vector3D Position;

    double Orientation;

  public:

    Vector3D TransformToParentsCoords(const Vector3D &Point) const;

    void SetPosition(const Vector3D Pos) {Position = Pos; Orientation = 0;};

};