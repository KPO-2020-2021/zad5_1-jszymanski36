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

    

    Solid() {double i[SIZE] = {1,1,1}; Scale_Vector = Vector3D(i);};

    Vector3D Scale (const Vector3D &Point) const{return Scale_Vector * Point;};

    const std::string &TakeFileName_LocalCoords() const {return FileName_LocalCoords;};

    const std::string &TakeFileName_GlobalCoords() const {return FileName_GlobalCoords;};

    void SetFileNames(std::string local, std::string global) {FileName_GlobalCoords = global; FileName_LocalCoords = local;};   
};