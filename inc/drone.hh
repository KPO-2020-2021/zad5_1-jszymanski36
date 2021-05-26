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

    void Rotate (double degrees, PzG::LaczeDoGNUPlota &Lacze);

    void HorizontalFlight (double distance, PzG::LaczeDoGNUPlota &Lacze);

    bool CalcDroneGlobalCoords() const;

    void SetCoordFiles(const std::string filenames[7]);

    void Initiate(const std::string FileNames[2], double pos_x, double pos_y, double pos_z);

    void PrintPosition() {std::cout << Position;};
};