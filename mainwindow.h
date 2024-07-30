#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    virtual void paintEvent(QPaintEvent*event);
    void SpriteQueue(float xposx, float xposy, char xtype);
    void SmapQueue(float xposx, float xposy);
    void SpriteClear();
    int carsinput;
    int bikesinput;
    int trucksinput;
    bool state;

public slots:
    void carsetValue(int xval);
    void bikesetValue(int xval);
    void trucksetValue(int xval);
    void startstop(bool xstate);

private:
    class Sprite{
        float positionx;
        float positiony;
        char type;
    public:
        Sprite(float xpos, float ypos, char xtype);
        float getposx();
        float getposy();
        char gettype();
    };
    std::vector<Sprite> sprites;
    std::vector<Sprite> smap;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
