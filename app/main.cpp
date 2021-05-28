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

#define PLIK_ROBOCZY__DRON_KORPUS  "../datasets/PlikRoboczy_Dron_Korpus.dat"
#define PLIK_ROBOCZY__DRON_ROTOR  "../datasets/PlikRoboczy_Dron_Rotor.dat"

#define PLIK_WLASCIWY__DRON1_KORPUS  "../datasets/PlikWlasciwy_Dron1_Korpus.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR1  "../datasets/PlikWlasciwy_Dron1_Rotor1.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR2  "../datasets/PlikWlasciwy_Dron1_Rotor2.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR3  "../datasets/PlikWlasciwy_Dron1_Rotor3.dat"
#define PLIK_WLASCIWY__DRON1_ROTOR4  "../datasets/PlikWlasciwy_Dron1_Rotor4.dat"

#define PLIK_WLASCIWY__DRON2_KORPUS  "../datasets/PlikWlasciwy_Dron2_Korpus.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR1  "../datasets/PlikWlasciwy_Dron2_Rotor1.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR2  "../datasets/PlikWlasciwy_Dron2_Rotor2.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR3  "../datasets/PlikWlasciwy_Dron2_Rotor3.dat"
#define PLIK_WLASCIWY__DRON2_ROTOR4  "../datasets/PlikWlasciwy_Dron2_Rotor4.dat"

#define PLIK_TRASY_PRZELOTU "../datasets/trasa_przelotu.dat"

#define PLIK_WZORCOWEGO_SZESCIANU       "../datasets/szescian.dat"
#define PLIK_WZORCOWEGO_GRANIASTOSLUPA6 "../datasets/graniastoslup6.dat"

#define DRONE1_POS 20,20,0
#define DRONE2_POS 80,50,0

bool WritePathToFile(std::vector<Vector3D> PathPoints, std::string FileName){
       std::ofstream file(FileName);

       if(!file.is_open()) return 0;
       file << PathPoints[0];
       file << PathPoints[1];
       file << PathPoints[2];
       file << PathPoints[3];
       return 1;
}

void PrintMenu(){

       std::cout << "a - wybierz aktywnego drona" << std::endl;
       std::cout << "p - zadaj parametry przelotu" << std::endl;
       std::cout << "m - wyswietl menu" << std::endl << std::endl;
       std::cout << "k - koniec działania programu" << std::endl;
}

int main()
{
  PzG::LaczeDoGNUPlota  Lacze;
  std::vector<Vector3D> Path;
  Scene scene;
  Drone drone1, drone2;
  Drone *dronePtr;

  

  char choice;
  double angle, distance;

  const std::string TemplateFileNames[2] = {PLIK_WZORCOWEGO_SZESCIANU, PLIK_WZORCOWEGO_GRANIASTOSLUPA6};

  const std::string FileNames1[7] = {PLIK_ROBOCZY__DRON_KORPUS, PLIK_WLASCIWY__DRON1_KORPUS, PLIK_ROBOCZY__DRON_ROTOR, PLIK_WLASCIWY__DRON1_ROTOR1, PLIK_WLASCIWY__DRON1_ROTOR2, PLIK_WLASCIWY__DRON1_ROTOR3, PLIK_WLASCIWY__DRON1_ROTOR4};
  drone1.SetCoordFiles(FileNames1);
  drone1.Initiate(TemplateFileNames, DRONE1_POS);
  drone1.CalcDroneGlobalCoords();

  const std::string FileNames2[7] = {PLIK_ROBOCZY__DRON_KORPUS, PLIK_WLASCIWY__DRON2_KORPUS, PLIK_ROBOCZY__DRON_ROTOR, PLIK_WLASCIWY__DRON2_ROTOR1, PLIK_WLASCIWY__DRON2_ROTOR2, PLIK_WLASCIWY__DRON2_ROTOR3, PLIK_WLASCIWY__DRON2_ROTOR4};
  drone2.SetCoordFiles(FileNames2);
  drone2.Initiate(TemplateFileNames, DRONE2_POS);
  drone2.CalcDroneGlobalCoords();

  scene.AddDrone(drone1);
  scene.AddDrone(drone2);
  scene.ChooseActiveDrone(1);
  dronePtr = scene.GetActiveDrone();

  Lacze.DodajNazwePliku("../datasets/plaszczyzna.dat");
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_KORPUS);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR1);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR2);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR3);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON1_ROTOR4);
  
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_KORPUS);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_ROTOR1);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_ROTOR2);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_ROTOR3);
  Lacze.DodajNazwePliku(PLIK_WLASCIWY__DRON2_ROTOR4);

  Lacze.ZmienTrybRys(PzG::TR_3D);
  Lacze.Inicjalizuj();

  Lacze.UstawZakresX(0, 200);
  Lacze.UstawZakresY(0, 200);
  Lacze.UstawZakresZ(0, 120);


  Lacze.UstawRotacjeXZ(64,65); 

       Lacze.Rysuj();

       std::cout << "Położenie drona aktywnego: ";
       (*dronePtr).PrintPosition();
       std::cout << std::endl;
       PrintMenu();

       while(choice!='k'){
              std::cout << std::endl << "Aktualna ilość obiektów Wektor3D: " << Vector3D::ReturnActiveNumVectors() << std::endl;
              std::cout << "Laczna ilość obiektów Wektor3D: " << Vector3D::ReturnAllNumVectors() << std::endl;
              std::cout << "Twój wybór? (m - menu) > ";
              std::cin >> choice;
              

              switch(choice){
                     case 'a':{
                            int i;
                            std::cout << "Wybór aktywnego drona" << std::endl << std::endl;
                            std::cout << "1- Polozenie: ";
                            drone1.PrintPosition();
                            if(scene.ReturnAtiveDroneNum() == 0) std::cout << " <-- Dron aktywny";
                            std::cout << std::endl <<  "2- Polozenie: ";
                            drone2.PrintPosition();
                            if(scene.ReturnAtiveDroneNum() == 1) std::cout << " <-- Dron aktywny";

                            std::cout << std::endl << "Wprowadź numer aktywnego drona>";
                            std::cin >> i;
                            scene.ChooseActiveDrone(i);
                            dronePtr = scene.GetActiveDrone();
                            std::cout << std::endl << "Polozenie drona aktywnego: ";
                            (*dronePtr).PrintPosition();

                     break;
                     }

                     case 'p':
                            std::cout << "Podaj kierunek lotu (kat w stopniach) > ";
                            std::cin >> angle;
                            std::cout  << "Podaj długość lotu > ";
                            std::cin >> distance;
                            std::cout << "Rysuje zaplanowana sciezke lotu ..." << std::endl;
                            (*dronePtr).PlanPath(angle, distance, Path);
                            WritePathToFile(Path, PLIK_TRASY_PRZELOTU);
                            Lacze.DodajNazwePliku(PLIK_TRASY_PRZELOTU);

                            std::cout << "Realizacja przelotu ..." << std::endl;
                            (*dronePtr).VerticalFlight(80, Lacze);
                            (*dronePtr).Rotate(angle, Lacze);
                            (*dronePtr).HorizontalFlight(distance, Lacze);
                            (*dronePtr).VerticalFlight(-80, Lacze);

                            std::cout << "Dron wyladował ..." << std::endl << std::endl;
                            std::cout << "Polozenie drona aktywnego: ";
                            (*dronePtr).PrintPosition();

                            Lacze.UsunNazwePliku(PLIK_TRASY_PRZELOTU);
                            Lacze.Rysuj();
                     break;

                     case 'm':
                            PrintMenu();
                     break;

                     case 'k':
                            std::cout << "Koniec działania programu. " << std::endl;
                     break;

                     default:
                            std::cout << "Nieprawidłowy wybór opcji" << std::endl;
                     break;
              }
       }





/*   std::cout << "Nacisnij ENTER, aby zaplanować ścieżkę" << std::flush;
  std::cin.ignore(10000,'\n');
  drone.PlanPath(30, 100, Path);
  WritePathToFile(Path, PLIK_TRASY_PRZELOTU);
    Lacze.DodajNazwePliku(PLIK_TRASY_PRZELOTU);


  

  Lacze.Rysuj();        // Teraz powinno pojawic sie okienko gnuplota
                        // z rysunkiem, o ile istnieje plik "prostopadloscian1.pow"

  std::cout << "Nacisnij ENTER, aby polecieć w pizdu " << std::flush;
  std::cin.ignore(10000,'\n');

  (*dronePtr).VerticalFlight(50, Lacze);
  (*dronePtr).Rotate(30, Lacze);
  (*dronePtr).HorizontalFlight(100,Lacze);
  (*dronePtr).VerticalFlight(-50, Lacze); */



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