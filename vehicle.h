#ifndef VEHICLE_H
#define VEHICLE_H
#include "objective.h"
#include "machine.h"
#include "driver.h"
#include "roadmap.h"

/*! \brief Klasa reprezentująca pojazd z zawartością.
 *
 * Zarządza danym pojazdem, zawiera wskaźniki do
 * kierowcy, maszyny oraz celu ruchu
 */
class Vehicle
{
private:
    Driver* driver; /*!< Wskaźnik do obiektu reprezentującego kierowcę */
    Machine* machine; /*!< Wskaźnik do maszyny, obiektu reprezentującego fizyczne cechy pojazdu */
    Objective* obj; /*!< Wskaźnik do obiektu okreśłającego cel ruchu */

public:

    /*! \brief Konstruktor obiektu klasy Vehicle.
     *
     *  Tworząc nowy obiekt klasy Vehicle, przypisywane są
     *  mu domyślne obiekty składowe klas Driver oraz
     *  ObjectiveForward, a także podany przez parametr
     *  wskaźnik do maszyny (pojazdu) odpowiedniego typu.
     *
     * @param[in] xmachineptr wskaźnik do maszyny (pojazdu) odpowiedniego typu.
     */
    Vehicle(Machine *xmachineptr);

    /*! \brief Przesunięcie pojazdu na mapie.
     *
     * Pobiera referencję do mapy i wartość czasu,
     * jeśli nowa pozycja mieści się w granicach mapy
     * przesuwa pojazd i zwraca wartość true.
     *
     * @param[in] xmapptr referencja do mapy.
     * @param[in] xtime czas od ostatniej aktualizacji.
     * @return true jeśli nowa pozycja w granicach, false w przeciwnym wypadku
     */
    bool moveVehicle(Roadmap &xmapptr, float xtime);

    /*! \brief Zwraca wskaźnik do maszyny (pojazdu)
     *
     * Zwraca wskaźnik do maszyny, reprezentującej
     * fizyczne cechy pojazdu
     *
     * @return machine* wskaźnik do maszyny (pojazdu)
     */
    Machine* getMachinePtr();
};

#endif // VEHICLE_H

