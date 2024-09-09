#ifndef SIMULATION_H
#define SIMULATION_H
#include "vehicles.h"
#include "roadmap.h"

/*! \brief Klasa reprezentująca symulację ruchu pojazdów na mapie.
 *
 * Zarządza czasem życia symulacji,
 * zawiera listę pojazdów oraz mapę.
 */

class Simulation
{
private:
    Roadmap roadmap; /*!< Obiekt zawierający mapę */
    Vehicles vehicles; /*!< Obiekt zawierający pojazdy w symulacji */

public:
    /*! \brief Konstruktor obiektu klasy Simulation.
     */
    Simulation();

    /*! \brief Aktualizacja stanu symulacji.
     *
     * Pobiera czas jaki upłynął od ostatniej aktualizacji
     * i zadną przez użytkownika liczbę pojazdów każdego typu.
     *
     * @param[in] xtime czas od ostatniej aktualizacji.
     * @param[in] xcars ilość samochodów osobowych.
     * @param[in] xbikes ilość motocykli.
     * @param[in] xtrucks ilość samochodów ciężarowych.
     */
    void updateSimulation(double xtime, int xcars, int xbikes, int xtrucks);

    /*! \brief Przekazanie pojazdów do wyświetlenia.
     *
     * Wpisuje kopię każdego pojazdu z symulacji do wektora
     * przekazanego przez referencję w celu późniejszego
     * wyświetlenia w interfejsie graficznym.
     *
     * @param[in] xmachines referencja do wektora wskaźników do pojaazdów.
     */
    void printVehiclesPosition(std::vector<Machine*> &xmachines);

    /*! \brief Przekazanie mapy do wyświetlenia.
     *
     * Wpisuje wektor pozycji pola mapy do wektora
     * przekazanego przez referencję w celu późniejszego
     * wyświetlenia w interfejsie graficznym.
     *
     * @param[in] xroads referencja do wektora wektorów pozycji.
     */
    void printRoadsPosition(std::vector<Vec2d> &xroads);
};

#endif // SIMULATION_H
