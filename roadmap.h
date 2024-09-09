#ifndef ROADMAP_H
#define ROADMAP_H
#include <vector>
#include <memory>
#include "road.h"

/*! \brief Klasa zawierająca mapę.
 *
 * Klasa zawiera wektor pól tworzący mapę, wymiary mapy
 * oraz punkty startowe, z których emitowane są pojazdy.
 */
class Roadmap
{
private:
    std::vector<std::unique_ptr<Road>> roads; /*!< Wektor z polami stanowiący mapę */
    std::vector<Vec2d> startPoints; /*!< Wektor z wektorami pozycji punktów startowych */
    int mapWidth; /*!< Szerokość mapy w pikselach */
    int mapHeight; /*!< Wysokość mapy w pikselach */

public:
    /*! \brief Konstruktor obiektu klasy Roadmap.
     */
    Roadmap();

    /*! \brief Utworzenie przykładowej mapy.
     *
     * Tworzy przykładową mapę o przykładowych wymiarach,
     * która zawiera wszystkie możliwe konfiguracje łączenia dróg.
     */
    void makeTestMap();

    /*! \brief Znalezienie punktów startowych.
     *
     * Wyszukuje punkty, w których droga rozpoczyna się przy
     * krawędzi mapy, będące punktami startowymi z których
     * emitowane będą pojazdy podczas symulacji.
     */
    void findStartPoints();

    /*! \brief Wybranie punktu startowego.
     *
     * Losowo wybiera punkt startowy do wyemitowania pojazdu.
     * W przypadku braku wolnych punktów startowych, zwraca false,
     * kolejna próba będzie przeprowadzona w kolejnej pętli.
     *
     * @param[in] xposvec referencja do wektora pozycji wybranego punktu.
     * @return true jeśli znaleziono wolny punkt startowy, false w przeciwnym wypadku
     */
    bool chooseStartPoint(Vec2d &xposvec);

    /*! \brief Zmiana stanu zajęcia pola.
     *
     * Zmiana stanu zajęcia wskazanego wektorem pozycji
     * fragmentu drogi na podany parametr,
     * wartość true oznacza zwolnienie, a false zajęcie.
     *
     * @param[in] xposvec wektor pozycji wybranego pola.
     * @param[in] isfree zadany stan zajęcia pola (domyślnie true, czyli wolny)
     */
    void setFree(Vec2d xposvec, bool isfree=true);



    /*! \brief Sprawdzenie, czy pole mieści się w granicach mapy.
     *
     * Porównanie współrzędnych wektora z wymiarami mapy,
     * w celu sprawdzenia czy pole wskazane wektorem pozycji
     * mieści sie w granicach mapy.
     *
     * @param[in] xposvec wektor pozycji wskazanego pola.
     * @return true jeśli mieści się w granicach, false w przeciwnym wypadku
     */
    bool checkIfInBounds(Vec2d xposvec);

    /*! \brief Sprawdzenie, czy pole zawiera drogę.
     *
     * Zwraca wartość logiczną true, jeśli pole
     * zawiera drogę po której mogą poruszać się pojazdy.
     *
     * @param[in] xposvec wektor pozycji wskazanego pola.
     * @return true jeśli zawiera drogę, false w przeciwnym przypadku
     */
    bool checkIfRoad(Vec2d xposvec);

    /*! \brief Sprawdzenie, czy pole ma kierunek tożsamy z podanym wektorem.
     *
     * Zwraca wartość logiczną true, jeśli wskazany wektorem
     * fragment mapy ma kierunek tożsamy z kierunkiem
     * drugiego podanego wektora.
     *
     * @param[in] xposvec wektor pozycji wskazanego pola.
     * @param[in] xposvec wektor kierunku do porównania.
     * @return true jeśli kierunek tożsamy, false w przeciwnym wypadku.
     */
    bool checkIfDirectionSame(Vec2d xposvec, Vec2d xdirvec);

    /*! \brief Sprawdzenie, czy pole jest wolne.
     *
     * Zwraca wartość logiczną true, jeśli fragment mapy wskazany wektorem
     * jest wolny, false jeśli jest zajęty przez pojazd.
     *
     * @param[in] xposvec wektor pozycji wskazanego pola.
     * @return true jeśli jest wolne, false w przeciwnym przypadku.
     */
    bool checkIfFree(Vec2d xposvec);

    /*! \brief Sprawdzenie, czy pas ruchu wskazany wektorem jest wolny w zakresie.
     *
     * Sprawdza kolejne pola na pasie ruchu, do którego należy
     * pole wskazane wektorem na zakresie wskazanym parametrem,
     * jeśli żadne z nich nie jest zajęte zwraca wartość true.
     *
     * @param[in] xposvec wektor pozycji pola na wskazanym pasie ruchu.
     * @param[in] xrange zakres w którym sprawdzany jest pas ruchu.
     * @param[in] reverse zmiana kierunku sprawdzania na przeciwny (jeśli =true).
     * @return true jeśli pas wolny w zakresie, false w przeciwnym wypadku.
     */
    bool checkIfLaneEmpty(Vec2d xposvec, float xrange, bool reverse=false);

    /*! \brief Sprawdzenie, czy poprzeczny pas ruchu wskazany wektorem jest wolny w zakresie.
     *
     * Sprawdza kolejne pola na pasie ruchu, do którego należy
     * pole wskazane wektorem na zakresie wskazanym parametrem,
     * jeśli żadne z nich nie jest zajęte zwraca wartość true.
     *
     * @param[in] xposvec wektor pozycji pola na wskazanym pasie ruchu.
     * @param[in] xrange zakres w którym sprawdzany jest pas ruchu.
     * @param[in] reverse zmiana kierunku sprawdzania na przeciwny (jeśli =true).
     * @return true jeśli pas wolny w zakresie, false w przeciwnym wypadku.
     */
    bool checkIfCrossLaneEmpty(Vec2d xposvec, float xrange, bool reverse=false);

    /*! \brief Sprawdzenie pozycji pola o podanym indeksie.
     *
     * Zwraca poprzez referencję wektor pozycji pola
     * znajdującego się w wektorze mapy pod indeksem
     * wskazanym parametrem, poprzez wartość zwraca wartość
     * logiczną mówiącą czy pole istnieje.
     *
     * @param[in] vecptr referencja do wektora pozycji danego pola.
     * @param[in] xnum indeks sprawdzanego pola.
     * @return true jeśli istnieje pole, false w przeciwnym przypadku
     */
    bool getRoadPosition(Vec2d &vecptr, int xnum);

    /*! \brief Sprawdzenie kierunku pola o wskazanej pozycji.
     *
     * Zwraca wektor kierunku pola wskazanego
     * wektorem pozycji przekazanym przez parametr.
     *
     * @param[in] xposvec wektor pozycji sprawdzanego pola.
     * @return Vec2d wektor kierunku sprawdzanego pola.
     */
    Vec2d getDirection(Vec2d xposvec);
};

#endif // ROADMAP_H
