
#include "../inc/hexprism.hh"
#include "../inc/matrix3x3.hh"
#include <fstream> 

Vector3D HexPrism::TransformToParentsCoords(const Vector3D &Point) const{

  Vector3D result;
  Matrix3x3 MatRot;
  MatRot.RotationMatrix(Orientation);

  result = MatRot * Point;;
  result = result + Position;

  return result;
}

bool HexPrism::Initiate(std::string TemplateFile, double scale_x, double scale_y, double scale_z){
  
  std::ifstream Template (TemplateFile);
  std::ofstream Local (TakeFileName_LocalCoords());
  Vector3D point;

  if(!Template.is_open() || !Local.is_open()) return 0;
  SetScale(scale_x, scale_y, scale_z);

  while(true){
  for(int i = 0; i < 4; ++i){
    Template >> point;
    if(Template.eof()) return 1;
    point = Scale(point);
    Local << point;
    }
  Local << std::endl;
  }
  return 1;
}