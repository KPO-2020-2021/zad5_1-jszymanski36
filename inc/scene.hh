#pragma once

#include "drone.hh"

class Scene: Drone {

  private:

    Drone DroneArray[2];

    PzG::LaczeDoGNUPlota Lacze;

  public:

    const Drone &ChooseActiveDrone() const;

    Drone &UseActiveDrone();
};