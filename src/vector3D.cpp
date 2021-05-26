#include "../inc/vector3D.hh"
#include <iomanip>

/*!
* \file 
* \brief Metody zdefiniowane dla Wektora3D
*/

/*!
* \brief Przeciążenie operatora << dla Wektora3D
* 
* \param[in] out - adres strumienia wyjściowego
* \param[in] tmp - wektor
*/
std::ostream &operator << (std::ostream &out, Vector3D const &tmp) {
    for (int i = 0; i < SIZE; ++i) {
        out << std::fixed << std::setprecision(5) << tmp[i] << ' ';
    }
    out << std::endl;
    return out;
}


/*!
* \brief Przeciążenie operatora >> dla Wektora3D
* 
* \param[in] in - adres strumienia wejściowego
* \param[in] tmp - wektor
*/
std::istream &operator >> (std::istream &in, Vector3D &tmp) {
    for (int i = 0; i < SIZE; ++i) {
        in >> tmp[i];
    }
    return in;
}
