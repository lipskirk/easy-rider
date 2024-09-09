#ifndef MACHINE_H
#define MACHINE_H
#include "vec2d.h"

/*! \brief Klasa abstakcyjna reprezentująca fizyczne parametry pojazdu.
 *
 * Odpowiada za przechowywanie i zmianę fizycznych cech pojazu,
 * jak pozycja, prędkość i przyspieszenie.
 */
class Machine
{
protected:
    int deleteCountdown; /*!< Licznik do usunięcia pojazdu (w przypadku utknięcia) */
    float speed; /*!< Aktualna prędkość */
    float maxSpeed; /*!< Maksymalna prędkość */
    float acceleration; /*!< Aktualne przyspieszenie */
    float maxAcceleration; /*!< Maksymalne przyspieszenie */
    float minAcceleration; /*!< Minimalne przyspieszenie (Maksymalne ujemne przyspieszenie)*/
    Vec2d position; /*!< Aktualna pozycja */

public:
    /*! \brief Konstruktor obiektu klasy Machine.
     */
    Machine();

    /*! \brief Odliczanie do usunięcia pojazdu.
     *
     */
    void countdownToDelete();

    /*! \brief Sprawdzenie, czy pojazd do usunięcia.
     *
     * Sprawdzenie wartości licznika do usunięcia pojazdu,
     * jeśli osiągnął wartość zerową jest kierowany do
     * usunięcia, zwrócenie wartości logicznej.
     *
     * @return true jeśli licznik równy zero, false w przeciwnym przypadku.
     */
    bool checkIfToDelete();



    /*! \brief Zwrócenie aktualnej prędkości.
     *
     * @return float aktualna prędkość pojazdu.
     */
    float getSpeed();

    /*! \brief Zwrócenie aktualnego przyspieszenia.
     *
     * @return float aktualne przyspieszenie pojazdu.
     */
    float getAcceleration();

    /*! \brief Zwrócenie współrzędniej x aktualnego wektora pozycji.
     *
     * @return float aktualna współrzędna x pojazdu.
     */
    float getPositionX();

    /*! \brief Zwrócenie współrzędniej y aktualnego wektora pozycji.
     *
     * @return float aktualna współrzędna y pojazdu.
     */
    float getPositionY();

    /*! \brief Zwrócenie przewidywanej odległości.
     *
     * Zwraca odległość jaką pokona dla zadanego czasu,
     * wyznaczoną z wartości prędkości i przyspieszenia.
     *
     * @param[in] xtime czas od ostatniej aktualizacji symulacji.
     * @return float aktualna prędkość pojazdu.
     */
    float getPredictedDistance(float xtime);



    /*! \brief Zmiana przyspieszenia pojazdu.
     *
     * Zmienia przyspieszenie pojazdu o wartość zadaną
     * parametrem, upeniając się, że nie przekroczy
     * wartości maksymalnej ani minimalnej.
     *
     * @param[in] xvalue wartość zmiany przyspieszenia.
     */
    void adjustAcceleration(float xvalue);

    /*! \brief Przesunięcie o wektor.
     *
     * Zmiana pozycji pojazdu o wektor zadany parametrem.
     *
     * @param[in] xvec wektor przesunięcia.
     */
    void moveBy(Vec2d xvec);

    /*! \brief Zmiana pozycji i parametrów pojazdu.
     *
     * Wyznaczenie nowej pozycji pojazdu na podstawie
     * czasu, prędkości i przyspieszenia, a następnie
     * zmiana prędkości wynikająca z przyspieszenia
     * i zwrócenie przejechanego dystansu.
     *
     * @param[in] xdirvec wektor wskazujący kierunek ruchu.
     * @param[in] xtime czas od ostatniej aktualizacji symulacji.
     * @return float przejechana odległość.
     */
    float drive(Vec2d xdirvec, float xtime);



    /*! \brief Sprawdzenie typu pojazdu.
     *
     * Metoda czysto wirtualna, do nadpisania przez klasy pochodne,
     * zwraca znacznik w postaci char odpowiadający danemu typowi pojazdu.
     *
     * @return char typ pojazdu.
     */
    virtual char getMachineType()=0;

    /*! \brief Zliczenie pojazdów poszczególnych typów.
     *
     * Metoda czysto wirtualna, do nadpisania przez klasy pochodne,
     * zlicza liczbę pojazdów poszczególnych typów w symulacji
     * i wpisuje do tablicy przekazanej przez referencję.
     *
     * @param[in] vnumber[] tablica z liczbą pojazdów poszczególnych typów.
     */
    virtual void countMachineType(int vnumber[])=0;
};

#endif // MACHINE_H
