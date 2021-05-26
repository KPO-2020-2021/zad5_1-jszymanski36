
#include "../inc/drone.hh"
#include "../inc/matrix3x3.hh"
#include <fstream>
#include <cmath>
#include <unistd.h>
#define PI 3.14159265358979323846
#define FLIGHT_INC 2
#define ROTOR_ROTATE_INC 30
#define DRONE_ROTATE_INC 5
#define BODY_SCALE 10,8,4
#define ROTOR_SCALE 8,8,2
#define BODY_POS 0,0,2
#define ROTOR0_POS 5,4,5
#define ROTOR1_POS 5,-4,5
#define ROTOR2_POS -5,4,5
#define ROTOR3_POS -5,-4,5
#define DRONE_POS 20,20,0


bool Drone::CalcRotorGlobalCoords(const HexPrism &Rotor) const{

  std::ifstream local(Rotor.TakeFileName_LocalCoords());
  std::ofstream global(Rotor.TakeFileName_GlobalCoords());
  Vector3D point;

  if(!local.is_open() || !global.is_open()) return 0;
  while(local.is_open()){
    for(int i = 0; i < 4; ++i){
      if(!(local >> point)) return 1;
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
      point = Body.TransformToParentsCoords(point);
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

  double T_height[SIZE] = {0,0,50};
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

  CalcDroneGlobalCoords();
  double inc;
  if(distance > 0){
    inc = FLIGHT_INC;
  } else {
    inc = -FLIGHT_INC;
  }
  double T[3] = {0,0,inc};
  Vector3D trans(T);

  for(int i = 0; i < abs(distance); i+=FLIGHT_INC){
    
    Rotor[0].Rotate(ROTOR_ROTATE_INC);
    Rotor[1].Rotate(-ROTOR_ROTATE_INC);
    Rotor[2].Rotate(ROTOR_ROTATE_INC);
    Rotor[3].Rotate(-ROTOR_ROTATE_INC);
    Position = Position + trans;
    CalcDroneGlobalCoords();
    usleep(100000);
    Lacze.Rysuj();
  }
}

void Drone::HorizontalFlight(double distance, PzG::LaczeDoGNUPlota &Lacze){

  double radians = Orientation * PI/180;
  double x_inc = cos(radians) * FLIGHT_INC;
  double y_inc = sin(radians) * FLIGHT_INC;
  double T[3] = {x_inc, y_inc,0};
  Vector3D trans(T);
  CalcDroneGlobalCoords();

  for(int i = 0; i < distance; i+=FLIGHT_INC){
    Rotor[0].Rotate(ROTOR_ROTATE_INC);
    Rotor[1].Rotate(-ROTOR_ROTATE_INC);
    Rotor[2].Rotate(ROTOR_ROTATE_INC);
    Rotor[3].Rotate(-ROTOR_ROTATE_INC);
    Position = Position + trans;
    CalcDroneGlobalCoords();
    usleep(100000);
    Lacze.Rysuj();
  }
}

void Drone::Rotate(double degrees, PzG::LaczeDoGNUPlota &Lacze){

  CalcDroneGlobalCoords();

  for(int i = 0; i < degrees; i+=DRONE_ROTATE_INC){
    Rotor[0].Rotate(ROTOR_ROTATE_INC);
    Rotor[1].Rotate(-ROTOR_ROTATE_INC);
    Rotor[2].Rotate(ROTOR_ROTATE_INC);
    Rotor[3].Rotate(-ROTOR_ROTATE_INC);
    Orientation += DRONE_ROTATE_INC;
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

void Drone::Initiate(const std::string FileNames[2]){

  double TBody[SIZE] = {BODY_POS};
  double TR0[SIZE] = {ROTOR0_POS};
  double TR1[SIZE] = {ROTOR1_POS};
  double TR2[SIZE] = {ROTOR2_POS};
  double TR3[SIZE] = {ROTOR3_POS};

  double TDrone[SIZE] = {DRONE_POS};

  Vector3D VBody(TBody), VR0(TR0), VR1(TR1), VR2(TR2), VR3(TR3), VDrone(TDrone);

  Position = VDrone;
  Orientation = 0;

  Body.SetPosition(VBody);
  Rotor[0].SetPosition(VR0);
  Rotor[1].SetPosition(VR1);
  Rotor[2].SetPosition(VR2);
  Rotor[3].SetPosition(VR3);

  Body.Initiate(FileNames[0], BODY_SCALE);
  for(int i=0; i<4; i++){
    Rotor[i].Initiate(FileNames[1], ROTOR_SCALE);
  }
}
