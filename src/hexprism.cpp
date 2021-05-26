
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