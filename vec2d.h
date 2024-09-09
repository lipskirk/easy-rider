#ifndef VEC2D_H
#define VEC2D_H

/*! \brief Klasa reprezentująca wektor dwuwymiarowy.
 *
 *Wektor dwuwymiarowy zawierające współrzędne x i y,
 *wraz z wybranymi operacjami na wektorach.
 */
class Vec2d
{
private:
    float x; /*!< Współrzędna x wektora */
    float y; /*!< Współrzędna y wektora */
public:

    /*! \brief Konstruktor domyślny obiektu klasy Vec2d.
     *
     *  Umożliwia utworzenie wektora
     *  bez wartości początkowych.
     */
    Vec2d();

    /*! \brief Konstruktor obiektu klasy Vec2d.
     *
     *  Umożliwia utworzenie wektora
     *  z wartościami początkowymi.
     *
     * @param[in] sx współrzędna x wektora.
     * @param[in] sy współrzędna y wektora.
     */
    Vec2d(float sx, float sy);

    /*! \brief Pobranie współrzędnej x wektora.
     *
     * @return float współrzędna x wektora.
     */
    float getX();

    /*! \brief Pobranie współrzędnej y wektora.
     *
     * @return float współrzędna y wektora.
     */
    float getY();

    /*! \brief Ustawienie współrzędnych x i y wektora.
     *
     * @param[in] sx współrzędna x wektora.
     * @param[in] sy współrzędna y wektora.
     */
    void setXY(float sx, float sy);

    /*! \brief Wyznaczenie wektora prostopadłego.
     *
     * Wyznaczenie wektora prostopadłego do danego wektora,
     * w przyjętej konwencji zwróconego w lewą stronę
     * względem kierunku pierwotnego wektora.
     *
     * @return Vec2d wektor prostopadły do wejściowego.
     */
    Vec2d getPerpendicular();

    /*! \brief Dodawanie dwóch wektorów.
     *
     * Przeciążenie operatora dodawania,
     * dodanie dwóch wektorów poprzez dodanie ich
     * odpowiadających sobie współrzędnych.
     *
     * @param[in] other wektor dodany do pierwotnego.
     * @return Vec2d wektor będący sumą wektorów wejściowych.
     */
    Vec2d operator+(const Vec2d& other)
    {
        Vec2d tmpVec(x+other.x,y+other.y);
        return tmpVec;
    }

    /*! \brief Odejmowanie dwóch wektorów.
     *
     * Przeciążenie operatora odejmowania,
     * odjęcie dwóch wektorów poprzez odjęcie ich
     * odpowiadających sobie współrzędnych.
     *
     * @param[in] other wektor odjęty do pierwotnego.
     * @return Vec2d wektor będący różnicą wektorów wejściowych.
     */
    Vec2d operator-(const Vec2d& other)
    {
        Vec2d tmpVec(x-other.x,y-other.y);
        return tmpVec;
    }

    /*! \brief Mnożenie wektora przez skalar.
     *
     * Przeciążenie operatora mnożenia,
     * mnożenie wektora przez skalar poprzez pomnożenie
     * obu jego współrzędnych przez ten skalar.
     *
     * @param[in] other skalar przez który mnożony jest wektor.
     * @return Vec2d wektor będący wynikiem mnożenia.
     */
    Vec2d operator*(const float& other)
    {
        Vec2d tmpVec(x*other,y*other);
        return tmpVec;
    }

    /*! \brief Porównanie dwóch wektorów.
     *
     * Przeciążenie operatora porównania,
     * porównanie dwóch wektorów poprzez porównanie
     * ich odpowiednich współrzędnych, zwraca wartość logiczną.
     *
     * @param[in] other wektor porównywany z pierwotnym.
     * @return true jeśli oba wektory identyczne, false w przeciwnym wypadku.
     */
    bool operator==(const Vec2d& other)
    {
        if(x==other.x&&y==other.y)
        {
            return true;
        }
        return false;
    }
};

#endif // VEC2D_H
