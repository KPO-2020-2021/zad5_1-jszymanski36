#pragma once

#include "hexprism.hh"
#include "lacze_do_gnuplota.hh"

#include <iostream>
#include <vector>

class Drone: HexPrism, Cuboid {

  private:

    Vector3D Position;

    double Orientation;

    Cuboid Body;

    HexPrism Rotor[4];

    bool CalcBodyGlobalCoords() const;

    bool CalcRotorGlobalCoords(const HexPrism &Rotor) const;

  public:

    Vector3D TransformToParentsCoords(const Vector3D &Point) const;

    void PlanPath (double angle, double distance, std::vector<Vector3D> &PathPoints);

    void VerticalFlight (double distance, PzG::LaczeDoGNUPlota &Lacze);

    bool HorizontalFlight (double distance, PzG::LaczeDoGNUPlota &Lacze);

    bool CalcDroneGlobalCoords() const;

    void SetCoordFiles(const std::string filenames[10]);

    void SetDronePosition(double Pos_x, double Pos_y, double Pos_z);
};