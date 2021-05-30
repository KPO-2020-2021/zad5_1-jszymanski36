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

/*!
* \brief Pozycja 1. drona
*/
#define DRONE1_POS 20,20,0

/*!
* \brief Pozycja 2. drona
*/
#define DRONE2_POS 80,50,0


/*!
* \brief Zapisz ścieżkę lotu do odpowiedniego pliku
* \param[in] PathPoints - kontener zawierający poszczególne punkty na planowanej ścieżce lotu drona
* \param[in] FileName - nazwa pliku do którego ścieżka powinna zostać zapisana
*/
void WritePathToFile(std::vector<Vector3D> PathPoints, std::string FileName){
       std::ofstream file(FileName);

       if(!file.is_open()) throw std::runtime_error("Błąd w otwieraniu pliku!");
       file << PathPoints[0];
       file << PathPoints[1];
       file << PathPoints[2];
       file << PathPoints[3];
}

/*!
* \brief Wyświetl opcje menu programu
*/
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
  Drone *dronePtr;          // wskaźnik na aktywnego drona, to przez niego wykonywane są operacje na dronie

  char choice;              // wybór opcji przez użytkownika
  double angle, distance;   // kąt i odległość wybierane przez użytkownika

  const std::string TemplateFileNames[2] = {PLIK_WZORCOWEGO_SZESCIANU, PLIK_WZORCOWEGO_GRANIASTOSLUPA6};
  const std::string FileNames1[7] = {PLIK_ROBOCZY__DRON_KORPUS, PLIK_WLASCIWY__DRON1_KORPUS, PLIK_ROBOCZY__DRON_ROTOR, PLIK_WLASCIWY__DRON1_ROTOR1, PLIK_WLASCIWY__DRON1_ROTOR2, PLIK_WLASCIWY__DRON1_ROTOR3, PLIK_WLASCIWY__DRON1_ROTOR4};

  drone1.SetCoordFiles(FileNames1);
  drone1.Initiate(TemplateFileNames, DRONE1_POS, 0);
  drone1.CalcDroneGlobalCoords();


  const std::string FileNames2[7] = {PLIK_ROBOCZY__DRON_KORPUS, PLIK_WLASCIWY__DRON2_KORPUS, PLIK_ROBOCZY__DRON_ROTOR, PLIK_WLASCIWY__DRON2_ROTOR1, PLIK_WLASCIWY__DRON2_ROTOR2, PLIK_WLASCIWY__DRON2_ROTOR3, PLIK_WLASCIWY__DRON2_ROTOR4};
  drone2.SetCoordFiles(FileNames2);
  drone2.Initiate(TemplateFileNames, DRONE2_POS, 30);
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
                            if(scene.ReturnAtiveDroneNum() == 0) std::cout << " ^Dron aktywny";
                            std::cout << std::endl <<  "2- Polozenie: ";
                            drone2.PrintPosition();
                            if(scene.ReturnAtiveDroneNum() == 1) std::cout << " ^Dron aktywny";

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
       return 0;
}