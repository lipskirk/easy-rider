#include "mainwindow.h"
#include "app.h"
#include "simulation.h"
#include "machine.h"

#include <QApplication>
#include <QTime>
#include "vec2d.h"


void delay()
{
    QTime dieTime=QTime::currentTime().addMSecs(20);
    while(QTime::currentTime()<dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    App EasyRider;
    EasyRider.run();

    while(EasyRider.running)
    {
        if(w.simulationState)
        {
            Simulation demo;

            std::vector<Vec2d> roadsToSprites;
            demo.printRoadsPosition(roadsToSprites);
            for(auto& elem:roadsToSprites)
            {
                w.queueMapSprites(elem.getX(),elem.getY());
            }
            roadsToSprites.clear();

            auto tp1=std::chrono::system_clock::now();
            auto tp2=std::chrono::system_clock::now();

            std::vector<Machine*> vehiclesToSprites;
            while(w.simulationState)
            {
                demo.printVehiclesPosition(vehiclesToSprites);
                for(auto& elem:vehiclesToSprites)
                {
                    w.queueSprites(elem->getPositionX(),elem->getPositionY(),'m');
                }
                vehiclesToSprites.clear();

                tp2=tp1;
                tp1=std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed_seconds=tp1-tp2;
                demo.updateSimulation(elapsed_seconds.count(),w.inputCarsNumber,w.inputBikesNumber,w.inputTrucksNumber);

                demo.printVehiclesPosition(vehiclesToSprites);
                for(auto& elem:vehiclesToSprites)
                {
                    w.queueSprites(elem->getPositionX(),elem->getPositionY(),elem->getMachineType());
                }
                vehiclesToSprites.clear();

                w.repaint();
                w.clearSprites();
                delay();
            }

            demo.printVehiclesPosition(vehiclesToSprites);
            for(auto& elem:vehiclesToSprites)
            {
                w.queueSprites(elem->getPositionX(),elem->getPositionY(),'m');
            }
            vehiclesToSprites.clear();
        }

        w.repaint();
        delay();
    }

    return a.exec();
}
