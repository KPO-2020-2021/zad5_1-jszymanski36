// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "../tests/doctest/doctest.h"
#endif

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <fstream>
#include <string>

#include "exampleConfig.h"
#include "example.h"
#include "../inc/scene.hh"
#include "../inc/matrix3x3.hh"
#include "../inc/lacze_do_gnuplota.hh"

#define PLIK_ROBOCZY__DRON1_KORPUS  "../datasets/PlikRoboczy_Dron1_Korpus.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR1  "../datasets/PlikRoboczy_Dron1_Rotor1.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR2  "../datasets/PlikRoboczy_Dron1_Rotor2.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR3  "../datasets/PlikRoboczy_Dron1_Rotor3.dat"
#define PLIK_ROBOCZY__DRON1_ROTOR4  "../datasets/PlikRoboczy_Dron1_Rotor4.dat"

#define PLIK_WLASCIWY__DRON1_KORPUS  "../datasets/PlikWlasciwy_Dron1_Korpus.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR1  "../datasets/PlikWlasciwy_Dron1_Rotor1.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR2  "../datasets/PlikWlasciwy_Dron1_Rotor2.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR3  "../datasets/PlikWlasciwy_Dron1_Rotor3.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR4  "../datasets/PlikWlasciwy_Dron1_Rotor4.dat"

#define PLIK_TRASY_PRZELOTU "../datasets/trasa_przelotu.dat"

#define PLIK_WZORCOWEGO_SZESCIANU       "../datasets/szescian.dat"
#define PLIK_WZORCOWEGO_GRANIASTOSLUPA6 "../datasets/graniastoslup6.dat"

bool WritePathToFile(std::vector<Vector3D> PathPoints, std::string FileName){
       std::ofstream file(FileName);

       if(!file.is_open()) return 0;
       file << PathPoints[0];
       file << PathPoints[1];
       file << PathPoints[2];
       file << PathPoints[3];
       return 1;
}

int main()
{
  PzG::LaczeDoGNUPlota  Lacze;
  std::vector<Vector3D> Path;
  Drone drone;

  const std::string TemplateFileNames[2] = {PLIK_WZORCOWEGO_SZESCIANU, PLIK_WZORCOWEGO_GRANIASTOSLUPA6};
  const std::string FileNames[10] = {PLIK_ROBOCZY__DRON1_KORPUS, PLIK_WLASCIWY__DRON1_KORPUS, PLIK_ROBOCZY__DRON1_ROTOR1, PLIK_WLASCIWY__DRON1_ROTOR1, PLIK_ROBOCZY__DRON1_ROTOR2, PLIK_WLASCIWY__DRON1_ROTOR2, PLIK_ROBOCZY__DRON1_ROTOR3, PLIK_WLASCIWY__DRON1_ROTOR3, PLIK_ROBOCZY__DRON1_ROTOR4, PLIK_WLASCIWY__DRON1_ROTOR4};
  drone.SetCoordFiles(FileNames);
  drone.Initiate(TemplateFileNames);
  drone.CalcDroneGlobalCoords();



  Lacze.DodajNazwePliku("../datasets/plaszczyzna.dat");
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_KORPUS);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR1);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR2);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR3);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR4);

  Lacze.ZmienTrybRys(PzG::TR_3D);
  Lacze.Inicjalizuj();  // Tutaj startuje gnuplot.

  Lacze.UstawZakresX(0, 200);
  Lacze.UstawZakresY(0, 200);
  Lacze.UstawZakresZ(0, 120);


  Lacze.UstawRotacjeXZ(64,65); // Tutaj ustawiany jest widok

         Lacze.Rysuj();


  std::cout << "Nacisnij ENTER, aby zaplanować ścieżkę" << std::flush;
  std::cin.ignore(10000,'\n');
  drone.PlanPath(30, 100, Path);
  WritePathToFile(Path, PLIK_TRASY_PRZELOTU);
    Lacze.DodajNazwePliku(PLIK_TRASY_PRZELOTU);


  

  Lacze.Rysuj();        // Teraz powinno pojawic sie okienko gnuplota
                        // z rysunkiem, o ile istnieje plik "prostopadloscian1.pow"

  std::cout << "Nacisnij ENTER, aby polecieć w pizdu " << std::flush;
  std::cin.ignore(10000,'\n');

  drone.VerticalFlight(50, Lacze);
  drone.Rotate(30, Lacze);
  drone.HorizontalFlight(100,Lacze);
  drone.VerticalFlight(-50, Lacze);



/*   cout << "Nacisnij ENTER, aby pokazac sciezke przelotu drona " << flush;
  cin.ignore(10000,'\n');


  if (!DodajTrasePrzelotu(Lacze)) return 1;
  Lacze.Rysuj();


  cout << "Nacisnij ENTER, aby wykonac animacje lotu drona " << flush;
  cin.ignore(10000,'\n');
  if (!AnimacjaLotuDrona(Lacze)) return 1;

  cout << endl << "Nacisnij ENTER, aby usunac sciezke ... " << flush;
  cin.ignore(10000,'\n');

  Lacze.UsunNazwePliku(PLIK_TRASY_PRZELOTU);
  Lacze.Rysuj();
  
  cout << "Nacisnij ENTER, aby zakonczyc ... " << flush;
  cin.ignore(10000,'\n'); */
  
}