#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    carsinput=0;
    bikesinput=0;
    trucksinput=0;
    state=false;
    connect(ui->carSlider,SIGNAL(valueChanged(int)),this,SLOT(carsetValue(int)));
    connect(ui->bikeSlider,SIGNAL(valueChanged(int)),this,SLOT(bikesetValue(int)));
    connect(ui->truckSlider,SIGNAL(valueChanged(int)),this,SLOT(trucksetValue(int)));
    connect(ui->startButton,SIGNAL(toggled(bool)),this,SLOT(startstop(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::Sprite::Sprite(float xpos,float ypos,char xtype){
    positionx=10+xpos;
    positiony=10+ypos;
    type=xtype;
}

void MainWindow::SpriteClear()
{
    sprites.clear();
}

void MainWindow::SpriteQueue(float xposx,float xposy,char xtype)
{
    sprites.push_back(Sprite(xposx,xposy,xtype));
}

void MainWindow::SmapQueue(float xposx,float xposy)
{
    smap.push_back(Sprite(xposx,xposy,'m'));
}

void MainWindow::carsetValue(int xval)
{
    carsinput=xval;
}

void MainWindow::bikesetValue(int xval)
{
    bikesinput=xval;
}

void MainWindow::trucksetValue(int xval)
{
    trucksinput=xval;
}

void MainWindow::startstop(bool xstate)
{
    state=xstate;
    if(state)
    {
        ui->startButton->setText(QStringLiteral("Zakoncz symulacje"));
    }
    else
    {
        ui->startButton->setText(QStringLiteral("Uruchom symulacje"));
    }
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush((Qt::SolidPattern));

    QPen pen;
    pen.setWidth(0);

    for(auto& elem:smap){
        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawRect(QRect(2*static_cast<int>(elem.getposx())-1,2*static_cast<int>(elem.getposy())-1,2,2));
    }

    pen.setWidth(1);

    for(auto& elem:sprites){
        switch(elem.gettype())
        {
        case 'b':
            pen.setColor(Qt::red);
            break;
        case 't':
            pen.setColor(Qt::yellow);
            break;
        case 'c':
            pen.setColor(Qt::green);
            break;
        case 'm':
            pen.setColor(Qt::black);
            break;
        default:
            pen.setColor(Qt::white);
        }
        painter.setPen(pen);
        painter.drawRect(QRect(2*static_cast<int>(elem.getposx())-1,2*static_cast<int>(elem.getposy())-1,2,2));
    }
}

float MainWindow::Sprite::getposx()
{
    return positionx;
}

float MainWindow::Sprite::getposy()
{
    return positiony;
}

char MainWindow::Sprite::gettype()
{
    return type;
}
