#pragma once

#include "solid.hh"

class Cuboid: public Solid {

  private:

    Vector3D Position;

    double Orientation;

  public:

    Vector3D TransformToParentsCoords(const Vector3D &Point) const;

    void SetPosition(const Vector3D Pos) {Position = Pos; Orientation = 0;};

    bool Initiate(std::string TemplateFile, double scale_x, double scale_y, double scale_z);
};
