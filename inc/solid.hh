#pragma once

#include "vector3D.hh"
#include <stdio.h>
#include <string>

class Solid {

  private:

    std::string FileName_LocalCoords;

    std::string FileName_GlobalCoords;

    Vector3D Scale_Vector;

  public:

    void SetScale(double x, double y, double z) {Scale_Vector[0] = x; Scale_Vector[1] = y; Scale_Vector[2] = z;};

    Vector3D Scale (const Vector3D &Point) const{return Scale_Vector * Point;};

    const std::string &TakeFileName_LocalCoords() const {return FileName_LocalCoords;};

    const std::string &TakeFileName_GlobalCoords() const {return FileName_GlobalCoords;};

    void SetFileNames(std::string local, std::string global) {FileName_GlobalCoords = global; FileName_LocalCoords = local;};   
};