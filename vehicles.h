#ifndef VEHICLES_H
#define VEHICLES_H
#include <vector>
#include <memory>
#include "vehicle.h"

/*! \brief Klasa zarządzająca wszystkimi pojazdami w symulacji.
 *
 * Odpowiada za czas życia pojazdów,
 * kontrolowanie ich ilości poprzez dodawanie i usuwanie
 */
class Vehicles
{
private:
    std::vector<std::unique_ptr<Vehicle>> vehicles; /*!< Wektor z unikalnymi wskaźnikami do pojazdów */

public:

    /*! \brief Konstruktor obiektu klasy Vehicles.
     */
    Vehicles();

    /*! \brief Dodanie pojazdu do symulacji.
     *
     * Sprawdza, który typ pojazdu należy uzupełnić
     * i umieszcza go we wskazanym miejscu na mapie.
     *
     * @param[in] xcars zadana ilość samochodów osobowych.
     * @param[in] xbikes zadana ilość motocykli.
     * @param[in] xtrucks zadana ilość samochodów ciężarowych.
     * @param[in] xvecpos wektor pozycji pojazdu do dodania.
     */
    void addVehicle(int xcars, int xbikes, int xtrucks, Vec2d xvecpos);

    /*! \brief Usunięcie pojazdu z symulacji.
     *
     * Usuwa pojazd z wektora i pomniejsza indeks
     * o jeden w celu zachowania ciągłości liczenia.
     *
     * @param[in] xcnt referencja do indeksu pojazdu do usunięcia.
     */
    void deleteVehicle(int &xcnt);

    /*! \brief Sprawdza, czy maksymalna zadana liczba
     *  pojazdów w symulacji została osiagnięta.
     *
     * Porównuje aktualną ilość pojazdów w symulacji
     * z liczbą zadaną przez użytkownika, zwraca sygnał
     * czy osiągnięto maksymalną pojemość.
     *
     * @param[in] xnumber łączna zadana ilość pojazdów.
     * @return true jeśli w symulacji jest zadana liczba pojazdów, false w przeciwnym wypadku
     */
    bool checkIfVehiclesFull(int xnumber);

    /*! \brief Zwraca wskażnik do pojazdu o podanym indeksie.
     *
     * Pobiera numer porządkowy pojazdu w symulacji,
     * jeśli istnieje taki pojazd to poprzez referencję
     * zwraca jego wskaźnik i wartość logiczną.
     *
     * @param[in] vehicleptr referencja do wskaźnika pojazdu.
     * @param[in] xnum indeks pobieranego pojazdu.
     * @return true jeśli udało się pobrać wskaźnik, false jeśli brak pojazdu o tym indeksie
     */
    bool getVehiclePtr(Vehicle *&vehicleptr, int xnum);
};

#endif // VEHICLES_H
