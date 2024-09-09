#ifndef CAR_H
#define CAR_H
#include "machine.h"

/*! \brief Klasa pochodna będąca typem pojazdu.
 *
 */
class Car :public Machine
{
public:

    /*! \brief Konstruktor obiektu klasy Car.
     *
     * @param[in] xposvec wektor pozycji startowej pojazdu.
     */
    Car(Vec2d xposvec);

    /*! \brief Sprawdzenie typu pojazdu.
     *
     * Nadpisanie funkcji z klasy bazowej, zwraca znacznik
     * w postaci char odpowiadający danemu typowi pojazdu.
     *
     * @return char typ pojazdu.
     */
    char getMachineType() override;

    /*! \brief Zliczenie pojazdów danego typu.
     *
     * Nadpisanie funkcji z klasy bazowej, zlicza liczbę pojazdów
     * danego typu w symulacji i wpisuje do tablicy przekazanej przez referencję.
     *
     * @param[in] vnumber[] tablica z liczbą pojazdów poszczególnych typów.
     */
    void countMachineType(int vnumber[]) override;
};

#endif // CAR_H
