#pragma once

#include "drone.hh"

class Scene: Drone {

  private:

    std::vector<Drone> DroneArray;

    unsigned int ActiveDrone;

  public: 

    void AddDrone(Drone new_drone) {DroneArray.push_back(new_drone);};

    Drone *GetActiveDrone(){return (&DroneArray[ActiveDrone]);};

    void ChooseActiveDrone(unsigned int choice) {ActiveDrone = choice-1;};

    int ReturnAtiveDroneNum() {return ActiveDrone;};
};