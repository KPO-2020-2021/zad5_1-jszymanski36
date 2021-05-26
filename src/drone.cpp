
#include "../inc/drone.hh"
#include "../inc/matrix3x3.hh"
#include <fstream>
#include <cmath>
#include <unistd.h>
#define PI 3.14159265358979323846
#define FLIGHT_INC 2
#define ROTATE_INC 30



bool Drone::CalcRotorGlobalCoords(const HexPrism &Rotor) const{

  std::ifstream local(Rotor.TakeFileName_LocalCoords());
  std::ofstream global(Rotor.TakeFileName_GlobalCoords());
  Vector3D point;

  if(!local.is_open() || !global.is_open()) return 0;
  while(local.is_open()){
    for(int i = 0; i < 4; ++i){
      if(!(local >> point)) return 1;
      point = Rotor.Scale(point);
      point = Rotor.TransformToParentsCoords(point);
      point = TransformToParentsCoords(point);
      global << point;
    }
    global << std::endl;
  }
  return 1;
}

bool Drone::CalcBodyGlobalCoords() const{

  std::ifstream local(Body.TakeFileName_LocalCoords());
  std::ofstream global(Body.TakeFileName_GlobalCoords());
  Vector3D point;

  if(!local.is_open() || !global.is_open()) return 0;

  while(true){
    for(int i = 0; i < 4; ++i){
      local >> point;
      if( local.eof()) return 1;
/*       std::cout << Body.Scale_Vector << std::endl; */
      point = Body.Scale(point);
      point = Body.TransformToParentsCoords(point);
                  std::cout << point << std::endl;
      point = TransformToParentsCoords(point);

      global << point;
    }
    global << std::endl;
  }
  return 1;
}

Vector3D Drone::TransformToParentsCoords(const Vector3D &Point) const{

  Vector3D result;
  Matrix3x3 MatRot;
  MatRot.RotationMatrix(Orientation);

  result = MatRot * Point;
  result = result + Position;

  return result;
}

void Drone::PlanPath (double angle, double distance, std::vector<Vector3D> &PathPoints){

  double T_height[SIZE] = {0,0,20};
  double radians = angle * PI/180;
  double T_flight[SIZE] = {cos(radians)*distance, sin(radians)*distance, 0};
  
  Vector3D height(T_height);
  Vector3D flight(T_flight);
  PathPoints.push_back(Position);
  PathPoints.push_back(Position + height);
  PathPoints.push_back(Position + height + flight);
  PathPoints.push_back(Position + flight);
}

void Drone::VerticalFlight(double distance, PzG::LaczeDoGNUPlota &Lacze){

  double T[3] = {0,0,FLIGHT_INC};
  Vector3D trans(T);
  CalcDroneGlobalCoords();

  for(int i = 0; i < distance; i+=FLIGHT_INC){
    Rotor[0].Rotate(ROTATE_INC);
    Rotor[1].Rotate(-ROTATE_INC);
    Rotor[2].Rotate(ROTATE_INC);
    Rotor[3].Rotate(-ROTATE_INC);
    Position = Position + trans;
    CalcDroneGlobalCoords();
    usleep(100000);
    Lacze.Rysuj();
  }
}

bool Drone::CalcDroneGlobalCoords() const{

  if(!CalcBodyGlobalCoords()) return 0;
  for(int i = 0; i < 4; ++i){
    if(!CalcRotorGlobalCoords(Rotor[i])) return 0;
  }
  return 1;
}

void Drone::SetCoordFiles(const std::string filenames[10]){

  Body.SetFileNames(filenames[0], filenames[1]);
  Rotor[0].SetFileNames(filenames[2], filenames[3]);
  Rotor[1].SetFileNames(filenames[4], filenames[5]);
  Rotor[2].SetFileNames(filenames[6], filenames[7]);
  Rotor[3].SetFileNames(filenames[8], filenames[9]);
}

void Drone::SetDronePosition(double Pos_x, double Pos_y, double Pos_z){

  double TBody[SIZE] = {0,0,2};
  double TR0[SIZE] = {5,4,5};
  double TR1[SIZE] = {5,-4,5};
  double TR2[SIZE] = {-5,4,5};
  double TR3[SIZE] = {-5,-4,5};
  double TDrone[SIZE] = {Pos_x, Pos_y, Pos_z};

  Vector3D VBody(TBody), VR0(TR0), VR1(TR1), VR2(TR2), VR3(TR3), VDrone(TDrone);

/*   Body.SetPosition(VBody);
  Rotor[0].SetPosition(VR0);
  Rotor[1].SetPosition(VR1);
  Rotor[2].SetPosition(VR2);
  Rotor[3].SetPosition(VR3); */


  Position = VDrone;
  Orientation = 0;

}