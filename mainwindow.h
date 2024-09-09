#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/*! \brief Klasa obsługująca interfejs graficzny.
 *
 * Zarządza danymi wejściowymi oraz wyświetlaniem
 * wyniku symulacji w postaci graficznej.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*! \brief Konstruktor obiektu klasy MainWindow.
     */
    MainWindow(QWidget *parent = nullptr);

    /*! \brief Destruktor obiektu klasy MainWindow.
     */
    ~MainWindow();

    /*! \brief Metoda wirtualna rysująca sprite'y w oknie aplikacji.
     *
     * Podczas każdej aktualizacji okna aplikacji,
     * w interfejsie graficznym rysuje zakolejkowane
     * sprite'y pojazdów i mapy.
     *
     * @param[in] event wskaźnik do zdarzenia odświeżającego okno.
     */
    virtual void paintEvent(QPaintEvent*event);

    /*! \brief Metoda wpisująca sprite'y do kolejki.
     *
     * Wpisuje kolejne sprite'y pojazdów do kolejki
     * oczekującej na rysowanie w oknie aplikacji.
     *
     * @param[in] xposx współrzędna x pozycji sprite'a.
     * @param[in] xposy współrzędna y pozycji sprite'a.
     * @param[in] xtype typ sprite'a odpowiadający typowi pojazdu.
     */
    void queueSprites(float xposx, float xposy, char xtype);

    /*! \brief Metoda wpisująca sprite'y do kolejki.
     *
     * Wpisuje kolejne sprite'y mapy do kolejki
     * oczekującej na rysowanie w oknie aplikacji.
     *
     * @param[in] xposx współrzędna x pozycji sprite'a.
     * @param[in] xposy współrzędna y pozycji sprite'a.
     */
    void queueMapSprites(float xposx, float xposy);

    /*! \brief Metoda usuwająca spite'y z kolejki.
     *
     *  Sprite'y zostają usunięte w celu zwolnienia pamięci
     *  i przygotowania miejsca na sprite'y w kolejnej
     *  pętli działania programu.
     */
    void clearSprites();

    int inputCarsNumber; /*!< Wejściowa liczba samochodów osobowych */
    int inputBikesNumber; /*!< Wejściowa liczba motocykli */
    int inputTrucksNumber; /*!< Wejściowa liczba samochodów ciężarowych */
    bool simulationState; /*!< Stan aktywności symulacji */

public slots:
    /*! \brief Wpisanie zadanej liczby samochodów osobowych.
     *
     * Wpisanie liczby pojazdów ustalonej przez użytkownika
     * za pomocą suwaka w interfejsie graficznym, inicjowane
     * przy zmianie wartości suwaka.
     *
     * @param[in] xval zadana liczba samochodów osobowych.
     */
    void carSetValue(int xval);

    /*! \brief Wpisanie zadanej liczby motocykli.
     *
     * Wpisanie liczby pojazdów ustalonej przez użytkownika
     * za pomocą suwaka w interfejsie graficznym, inicjowane
     * przy zmianie wartości suwaka.
     *
     * @param[in] xval zadana liczba motocykli.
     */
    void bikeSetValue(int xval);

    /*! \brief Wpisanie zadanej liczby samochodów ciężarowych.
     *
     * Wpisanie liczby pojazdów ustalonej przez użytkownika
     * za pomocą suwaka w interfejsie graficznym, inicjowane
     * przy zmianie wartości suwaka.
     *
     * @param[in] xval zadana liczba samochodów ciężarowych.
     */
    void truckSetValue(int xval);

    /*! \brief Uruchomienie lub zatrzymanie symulacji.
     *
     * Zmiana stanu aktywności symulacji za pomocą
     * przycisku w interfejsie graficznym, inicjowana
     * przy kliknięciu przycisku.
     *
     * @param[in] xstate zadany stan aktywności symulacji.
     */
    void changeButtonState(bool xstate);

private:

    /*! \brief Klasa reprezentująca sprite'y w interfejsie graficznym
     *
     * Zawiera pozycję i typ sprite'a,
     * a także metody ich sprawdzenia.
     */
    class Sprite{
        float positionX; /*!< Współrzędna x sprite'a */
        float positionY; /*!< Współrzędna y sprite'a */
        char type; /*!< Typ sprite'a, odpowiadający typowi pojazdu lub drodze */
    public:

        /*! \brief Konstruktor obiektu klasy Sprite.
         *
         * @param[in] xpos współrzędna x sprite'a.
         * @param[in] ypos współrzędna y sprite'a.
         * @param[in] xtype typ sprite'a.
         */
        Sprite(float xpos, float ypos, char xtype);

        /*! \brief Zwrócenie współrzędnej x sprite'a.
         *
         * @return float współrzędna x sprite'a.
         */
        float getPositionX();

        /*! \brief Zwrócenie współrzędnej y sprite'a.
         *
         * @return float współrzędna y sprite'a.
         */
        float getPositionY();

        /*! \brief Zwrócenie typu sprite'a.
         *
         * @return char typ sprite'a.
         */
        char getType();
    };
    std::vector<Sprite> sprites; /*!< Wektor zawierający sprite'y */
    std::vector<Sprite> mapSprites; /*!< Wektor zawierający sprite'y mapy*/
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
