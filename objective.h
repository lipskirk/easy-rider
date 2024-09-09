#ifndef OBJECTIVE_H
#define OBJECTIVE_H
#include "roadmap.h"
#include "driver.h"
#include "machine.h"

/*! \brief Klasa abstrakcyjna reprezentująca cel ruchu pojazdu.
 *
 * Klasy pochodne zarządzają zachowaniem pojazdu,
 * które różni się zależnie od celu ruchu.
 */
class Objective
{
public:
    /*! \brief Konstruktor obiektu klasy Bike.
     */
    Objective();

    /*! \brief Zmiana stanu pojazdu zależnie od otoczenia.
     *
     * Metoda czysto wirtualna, do nadpisania przez klasy pochodne,
     * zarządza ruchem pojazdu, zmianą jego stanu i celu ruchu.
     *
     * @param[in] xmapptr referencja do mapy.
     * @param[in] driver referencja do wskaźnika na kierowcę pojazdu.
     * @param[in] machine referencja do wskaźnika na maszynę (pojazd).
     * @param[in] objective referencja do wskaźnika na cel ruchu.
     * @param[in] xdist przewidywana odległość którą pojazd pokona.
     */
    virtual bool move(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective, float xdist)=0;
};

#endif // OBJECTIVE_H
