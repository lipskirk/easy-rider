#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    inputCarsNumber=0;
    inputBikesNumber=0;
    inputTrucksNumber=0;
    simulationState=false;
    connect(ui->carSlider,SIGNAL(valueChanged(int)),this,SLOT(carSetValue(int)));
    connect(ui->bikeSlider,SIGNAL(valueChanged(int)),this,SLOT(bikeSetValue(int)));
    connect(ui->truckSlider,SIGNAL(valueChanged(int)),this,SLOT(truckSetValue(int)));
    connect(ui->startButton,SIGNAL(toggled(bool)),this,SLOT(changeButtonState(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush((Qt::SolidPattern));

    QPen pen;
    pen.setWidth(0);

    for(auto& elem:mapSprites){
        pen.setColor(Qt::black);
        painter.setPen(pen);
        painter.drawRect(QRect(2*static_cast<int>(elem.getPositionX())-1,2*static_cast<int>(elem.getPositionY())-1,2,2));
    }

    pen.setWidth(1);

    for(auto& elem:sprites){
        switch(elem.getType())
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
        painter.drawRect(QRect(2*static_cast<int>(elem.getPositionX())-1,2*static_cast<int>(elem.getPositionY())-1,2,2));
    }
}

void MainWindow::queueSprites(float xposx,float xposy,char xtype)
{
    sprites.push_back(Sprite(xposx,xposy,xtype));
}

void MainWindow::queueMapSprites(float xposx,float xposy)
{
    mapSprites.push_back(Sprite(xposx,xposy,'m'));
}

void MainWindow::clearSprites()
{
    sprites.clear();
}



void MainWindow::carSetValue(int xval)
{
    inputCarsNumber=xval;
}

void MainWindow::bikeSetValue(int xval)
{
    inputBikesNumber=xval;
}

void MainWindow::truckSetValue(int xval)
{
    inputTrucksNumber=xval;
}

void MainWindow::changeButtonState(bool xstate)
{
    simulationState=xstate;
    if(simulationState)
    {
        ui->startButton->setText(QStringLiteral("Zakoncz symulacje"));
    }
    else
    {
        ui->startButton->setText(QStringLiteral("Uruchom symulacje"));
    }
}



MainWindow::Sprite::Sprite(float xpos,float ypos,char xtype){
    positionX=10+xpos;
    positionY=10+ypos;
    type=xtype;
}

float MainWindow::Sprite::getPositionX()
{
    return positionX;
}

float MainWindow::Sprite::getPositionY()
{
    return positionY;
}

char MainWindow::Sprite::getType()
{
    return type;
}
