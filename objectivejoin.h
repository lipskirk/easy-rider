#ifndef OBJECTIVEJOIN_H
#define OBJECTIVEJOIN_H
#include "objective.h"

/*! \brief Klasa pochodna określająca cel ruchu pojazdu.
 *
 * Zarządza ruchem pojazdu, kierując go
 * do włączenia się do ruchu w przecznicy.
 */
class ObjectiveJoin : public Objective
{
public:

    /*! \brief Konstruktor obiektu klasy ObjectiveJoin.
     */
    ObjectiveJoin();

    /*! \brief Zmiana stanu pojazdu zależnie od otoczenia.
     *
     * Metoda zarządza ruchem pojazdu i zmianą jego stanu,
     * kieruje go do włączenia się do ruchu w przecznicy,
     * jeśli cel ruchu się zmienił zwraca wartość true.
     *
     * @param[in] xmapptr referencja do mapy.
     * @param[in] driver referencja do wskaźnika na kierowcę pojazdu.
     * @param[in] machine referencja do wskaźnika na maszynę (pojazd).
     * @param[in] objective referencja do wskaźnika na cel ruchu.
     * @param[in] xdist przewidywana odległość którą pojazd pokona.
     * @return true jeśli zmienił sie cel ruchu, false w przeciwnym wypadku
     */
    bool move(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective, float xdist) override;
};

#endif // OBJECTIVEJOIN_H
