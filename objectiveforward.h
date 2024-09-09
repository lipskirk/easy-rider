#ifndef OBJECTIVEFORWARD_H
#define OBJECTIVEFORWARD_H
#include "objective.h"

/*! \brief Klasa pochodna określająca cel ruchu pojazdu.
 *
 * Zarządza ruchem pojazdu, kierując go prosto
 * i weryfikuje, czy droga prowadzi prosto,
 * czy oferuje zmiany kierunku.
 */
class ObjectiveForward : public Objective
{
private:
    /*! \brief Sprawdzenie, czy droga jest prosto.
     *
     * Metoda wekryfikuje jakie są dostępne kierunki ruchu,
     * w razie potrzeby zmienia cel ruchu i zwraca wartość true,
     * w przeciwnym razie false.
     *
     * @param[in] xmapptr referencja do mapy.
     * @param[in] driver referencja do wskaźnika na kierowcę pojazdu.
     * @param[in] machine referencja do wskaźnika na maszynę (pojazd).
     * @param[in] objective referencja do wskaźnika na cel ruchu.
     * @param[in] xdist przewidywana odległość którą pojazd pokona.
     * @return true jeśli zmienił sie cel ruchu, false w przeciwnym wypadku.
     */
    bool checkIfRoadStraight(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective, float xdist);

public:

    /*! \brief Konstruktor obiektu klasy ObjectiveForward.
     */
    ObjectiveForward();

    /*! \brief Zmiana stanu pojazdu zależnie od otoczenia.
     *
     * Metoda zarządza ruchem pojazdu, zmianą jego stanu i celu ruchu,
     * kieruje go prosto i szuka zmian kierunku, jeśli cel ruchu się zmienił
     * zwraca wartość true.
     *
     * @param[in] xmapptr referencja do mapy.
     * @param[in] driver referencja do wskaźnika na kierowcę pojazdu.
     * @param[in] machine referencja do wskaźnika na maszynę (pojazd).
     * @param[in] objective referencja do wskaźnika na cel ruchu.
     * @param[in] xdist przewidywana odległość którą pojazd pokona.
     * @return true jeśli zmienił sie cel ruchu, false w przeciwnym wypadku.
     */
    bool move(Roadmap &xmapptr, Driver *&driver, Machine *&machine, Objective *&objective, float xdist) override;
};

#endif // OBJECTIVEFORWARD_H
