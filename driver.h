#ifndef DRIVER_H
#define DRIVER_H
#include "vec2d.h"
#include "machine.h"
#include "roadmap.h"

/*! \brief Klasa reprezentująca kierowcę pojazdu.
 *
 * Zarządza zmianami stanu pojazdu, podejmuje
 * decyzje i reaguje na otoczenie
 */
class Driver
{
private:
    bool preferredTurnRight; /*!< Preferowany kierunek skrętu w prawo (jeśli false to w lewo) */
    bool isOvertaking; /*!< Stan wyprzedzania (jeśli true to aktualnie wyprzedza) */
    float distanceToStop; /*!< Odległość do zatrzymania (0 oznacza brak) */
    float distanceToObstacle; /*!< Odległość do przeszkody (0 oznacza brak przeszkody) */
    float distanceToOvertake; /*!< Odległość do wyprzedzenia */
    Vec2d crossDirection; /*!< Kierunek jazdy (tylko podczas przecinania przecznicy, inaczej (0,0)) */

public:
    /*! \brief Konstruktor obiektu klasy Driver.
     */
    Driver();

    /*! \brief Ustala nową odległość do zatrzymania.
     *
     * @param[in] xdist nowa odległość do zatrzymania.
     */
    void setDistanceToStop(float xdist);

    /*! \brief Ustala nową odległość do przeszkody.
     *
     * @param[in] xdist nowa odległość do przeszkody.
     */
    void setDistanceToObstacle(float xdist);

    /*! \brief Ustala nowy kierunek jazdy przez przecznicę.
     *
     * @param[in] xdist nowy kierunek.
     */
    void setCrossDirection(Vec2d xvec);

    /*! \brief Utrzymuje bezpieczną odległość do kolejnego pojazdu.
     *
     * Sprawdza odległość do kolejnego pojazdu
     * na pasie ruchu, jeśli zbyt blisko to hamuje.
     *
     * @param[in] xmachine referencja do wskażnika maszyny (pojazdu).
     * @param[in] xtime czas od ostatniej aktualizacji.
     */
    void keepDistanceToVehicleAhead(Machine *&xmachine, float xtime);

    /*! \brief Zmniejszenie odległości do zatrzymania.
     *
     * Pomniejsza pamiętaną odległość do zatrzymania
     * o przejechaną odległość, nowa wartość nie mniejsza od zera.
     *
     * @param[in] xchange wartość o którą należy pomniejszyć.
     */
    void reduceDistanceToStop(float xchange);



    /*! \brief Sprawdzenie, czy preferuje skręcić w prawo.
     *
     * Sprawdzenie preferencji kierunku skrętu kierowcy,
     * zwraca wartość true jeśli preferowany kierunek w prawo,
     * jeśli w lewo to false.
     *
     * @return true jeśli preferuje skręt w prawo, false w lewo
     */
    bool checkIfPreferredToTurnRight();

    /*! \brief Sprawdzenie, czy aktualnie wyprzedza.
     *
     * Sprawdza, czy jest w trakcie wyprzedzania, jeśli tak to
     * sprawdza czy może zakończyć wyprzedzanie i wrócić na pas ruchu.
     * W przypadku dalszego wyprzedzania zwraca true,
     * w przeciwnym wypadku false.
     *
     * @param[in] xroadmap referencja do mapy.
     * @param[in] xmachine referencja do wskażnika maszyny (pojazdu).
     * @return true jeśli dalej wyprzedza, false w przeciwnym wypadku
     */
    bool checkIfOvertaking(Roadmap &xroadmap, Machine *&xmachine);

    /*! \brief Zwraca odległość do przeszkody.
     *
     * Zwraca zapamiętaną odległość do kolejnego
     * pojazdu na pasie ruchu.
     *
     * @return float odległość do przeszkody.
     */
    float getDistanceToObstacle();

    /*! \brief Sprawdza, czy aktualnie przecina przecznicę.
     *
     * Zwraca stan logiczny zależnie od wektora
     * przecinania, jeśli jest różny od zerowego (0,0) true,
     * dla pozostałych wartości false.
     *
     * @return true jeśli przecina przecznicę, false w przeciwnym wypadku.
     */
    bool checkIfCrossing();

    /*! \brief Zwraca wektor kierunku przecinania przecznicy.
     *
     * @return Wektor kierunku przecinania przecznicy typu Vec2d.
     */
    Vec2d getCrossDirection();

    /*! \brief Sprawdzenie odległości do przeszkody na pasie ruchu.
     *
     * Sprawdza, czy w danym zakresie na pasie ruchu przed nim
     * znajduje się inny pojazd, jeśli tak, zwraca odległość.
     * Zerowa odległość oznacza brak przeszkody w zakresie.
     *
     * @param[in] xroadmap referencja do mapy.
     * @param[in] xmachine referencja do wskażnika maszyny (pojazdu).
     * @param[in] xrange zakres odległości szukania przeszkód.
     * @return float odległość do przeszkody (zero = brak przeszkód).
     */
    float checkDistanceToVehicleAhead(Roadmap &xroadmap, Machine *&xmachine, float xrange);

    /*! \brief Sprawdzenie, czy może wyprzedzić.
     *
     * Sprawdza, czy na pasie obok jest wystarczająco
     * dużo miejsca, żeby przeprowadzić manewr wyprzedzania.
     *
     * @param[in] xroadmap referencja do mapy.
     * @param[in] xmachine referencja do wskażnika maszyny (pojazdu).
     * @param[in] xrange zakres odległości szukania przeszkód.
     * @return Odległość do przeszkody typy float (zero = brak przeszkód).
     */
    bool checkIfCanOvertake(Roadmap &xroadmap,Machine *&xmachine);

    /*! \brief Sprawdzenie, czy może przeciąć przecznicę.
     *
     * Sprawdza, czy na każdym z pasów przecinanej drogi
     * jest wystarczająco dużo miejsca, aby przejechać,
     * po czym zwraca wartość logiczną.
     *
     * @param[in] xroadmap referencja do mapy.
     * @param[in] xmachine referencja do wskażnika maszyny (pojazdu).
     * @return true jeśli przecznica wolna, false w przeciwnym wypadku
     */
    bool checkIfCrossRoadEmpty(Roadmap &xroadmap, Machine *&xmachine);



    /*! \brief Rozpoczęcie przejazdu przez przecznicę.
     *
     * Ustala kierunek drogi na której aktualnie się znajduje
     * jako kierunek przecięcia przecznicy, rozpoczyna ruch
     * do przodu przecinając przecznicę.
     *
     * @param[in] xroadmap referencja do mapy.
     * @param[in] xmachine referencja do wskażnika maszyny (pojazdu).
     */
    void crossRoad(Roadmap &xroadmap,Machine *&xmachine);

    /*! \brief Rozpoczęcie manewru wyprzedzania.
     *
     * Inicjuje wyprzedzanie kolejnego pojazdu poprzez
     * zmianę pasa ruchu i ustalenie nowej odległości do wyprzedzenia.
     *
     * @param[in] xroadmap referencja do mapy.
     * @param[in] xmachine referencja do wskażnika maszyny (pojazdu).
     * @param[in] disttoobst nowa odległośc do wyprzedzenia.
     */
    void startOvertaking(Roadmap &xroadmap, Machine *&xmachine, float disttoobst);

    /*! \brief Zjechanie do boczny pas (domyślnie prawy).
     *
     * Sprawdza, czy po wskazanej stronie jest pas ruchu,
     * na którym jest wystarczająco dużo miejsca, jeśli tak
     * to zmienia pas ruchu na wskazany poprzez parametr toright
     * (domyślnie na prawo, w lewo jeśli toright=false).
     *
     * @param[in] xroadmap referencja do mapy.
     * @param[in] xmachine referencja do wskażnika maszyny (pojazdu).
     * @param[in] toright kierunek zmiany pasa (domyślnie prawo, po zanegowniu w lewo)
     */
    void goToRoadSide(Roadmap &xroadmap, Machine *&xmachine, bool toright=true);



    /*! \brief Przyspieszenie pojazdu.
     *
     * Zwiększenie wartości przyspieszenia pojazdu.
     *
     * @param[in] xmachine referencja do wskażnika maszyny (pojazdu).
     */
    void accelerate(Machine *&xmachine);

    /*! \brief Hamowanie pojazdu.
     *
     * Zmniejszenie wartości przyspieszenia pojazdu.
     *
     * @param[in] xmachine referencja do wskażnika maszyny (pojazdu).
     */
    void brake(Machine *&xmachine);

    /*! \brief Zatrzymanie pojazdu.
     *
     * Natychmiastowe awaryjne wyzerowanie prędkości
     * i przyspieszenia pojazdu.
     *
     * @param[in] xmachine referencja do wskażnika maszyny (pojazdu).
     */
    void stop(Machine *&xmachine);

    /*! \brief Zmiana pasa ruchu.
     *
     * Przesunięcie pojazdu o jedno pole na pas ruchu wskazany
     * wektorem kierunku.
     *
     * @param[in] xmachine referencja do wskażnika maszyny (pojazdu).
     * @param[in] xvec wektor kierunku wskazujący docelowy pas ruchu.
     */
    void changeLane(Machine *&xmachine, Vec2d xvec);

    /*! \brief Podjęcie decyzji o rozpoczęciu skręcania.
     *
     * Losowe podjęcie decyzji o skręcaniu lub jeździe prosto,
     * w przypadku wybrania skręcania zwraca wartość true i
     * ustala nowy kierunek skrętu i odległość do niego.
     *
     * @param[in] xdist nowa odległość do zatrzymania (skrętu).
     * @param[in] turnright znacznik skrętu w prawo (w lewo jeśli false)
     * @param[in] bypass obejście losowania jeśli musi skręcić (domyślnie false)
     * @return true jeśli będzie skręcał, false jeśli kontynuuje jazdę prosto
     */
    bool chooseIfTurn(float xdist, bool turnright, bool bypass=false);

    /*! \brief Podjęcie decyzji o włączeniu się do ruchu lub przecięciu przecznicy.
     *
     * Losowe podjęcie decyzji o włączeniu się do ruchu
     * lub przecięciu przecznicy - w przypadku wybrania
     * włączenia do ruchu zawraca wartość true, w przypadku
     * wybrania przecięcia przecznicy zwraca false.
     *
     * @param[in] xdist nowa odległość do zatrzymania (skrętu).
     * @param[in] turnright znacznik skrętu w prawo (w lewo jeśli false)
     * @param[in] bypass obejście losowania jeśli musi właczyć się do ruchu (domyślnie false)
     * @return true jeśli włącza sie do ruchu, false jeśli przecina przecznicę
     */
    bool chooseIfJoin(float xdist, bool xturnright, bool bypass=false);

    /*! \brief Wyzerowanie celu i kierunku ruchu.
     *
     * Losuje nowy preferowany kierunek skrętu,
     * zeruje zapamiętane stany i odległości.
     */
    void resetObjective();

};

#endif // DRIVER_H
