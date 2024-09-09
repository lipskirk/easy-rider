#ifndef ROAD_H
#define ROAD_H
#include "vec2d.h"

/*! \brief Klasa reprezentująca fragment drogi (pole).
 *
 * Pole będące wycinkiem drogi,
 * o określonej pozycji, kierunku i stanie zajęcia.
 */
class Road
{
private:
    bool isFree; /*!< Stan zajęcia pola, wartość true oznacza wolne */
    Vec2d direction; /*!< Wektor kierunku pola */
    Vec2d position; /*!< Wektor pozycji pola */

public:

    /*! \brief Konstruktor obiektu klasy Road.
     *
     * @param[in] xfree stan zajęcia pola.
     * @param[in] xpos współrzędna x pozycji pola.
     * @param[in] ypos współrzędna y pozycji pola.
     * @param[in] xdir współrzędna x kierunku pola.
     * @param[in] ydir współrzędna y kierunku pola.
     */
    Road(bool xfree, int xpos, int ypos, float xdir, float ydir);

    /*! \brief Sprawdzenie współrzędnej x wektora pozycji.
     *
     * Zwraca wartość współrzędnej x wektora pozycji
     * w postaci typu float.
     *
     * @return float współrzędna x wektora pozycji.
     */
    float getPositionX();

    /*! \brief Sprawdzenie współrzędnej y wektora pozycji.
     *
     * Zwraca wartość współrzędnej y wektora pozycji
     * w postaci typu float.
     *
     * @return float współrzędna y wektora pozycji.
     */
    float getPositionY();

    /*! \brief Sprawdzenie, czy pole zawiera funkcjonalną drogę.
     *
     * Zwraca wartość logiczną true, jeśli pole
     * zawiera drogę po której mogą poruszać się pojazdy,
     * co jest określane wektorem kierunku różnym od (0,0).
     *
     * @return true jeśli pole zawiera drogę, false w przeciwnym wypadku
     */
    bool checkIfRoad();

    /*! \brief Sprawdzenie, czy pole jest zajęte.
     *
     * Zwraca wartość logiczną true, jeśli pole
     * jest wolne, lub false, jeśli jest zajęte
     * przez pojazd.
     *
     * @return true jeśli pole zawiera drogę, false w przeciwnym wypadku
     */
    bool checkIfFree();

    /*! \brief Sprawdzenie kierunku pola.
     *
     * Zwraca wektor kierunku fragmentu drogi.
     *
     * @return Vec2d wektor kierunku pola.
     */
    Vec2d getDirection();

    /*! \brief Zmiana stanu zajęcia pola.
     *
     * Zmiana stanu zajęcia fragmentu drogi na podany parametr,
     * wartość true oznacza zwolnienie, a false zajęcie.
     *
     * @param[in] xstate stan zajęcia pola.
     */
    void setFree(bool xstate);
};

#endif // ROAD_H
