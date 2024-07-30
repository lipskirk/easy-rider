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
        if(w.state)
        {
            Simulation demo;

            std::vector<Vec2d> roadstosprites;
            demo.printroadspos(roadstosprites);
            for(auto& elem:roadstosprites)
            {
                w.SmapQueue(elem.getx(),elem.gety());
            }
            roadstosprites.clear();

            auto tp1=std::chrono::system_clock::now();
            auto tp2=std::chrono::system_clock::now();

            std::vector<Machine*> machinestosprites;
            while(w.state)
            {
                demo.printvehiclespos(machinestosprites);
                for(auto& elem:machinestosprites)
                {
                    w.SpriteQueue(elem->getposx(),elem->getposy(),'m');
                }
                machinestosprites.clear();

                tp2=tp1;
                tp1=std::chrono::system_clock::now();
                std::chrono::duration<double> elapsed_seconds=tp1-tp2;
                demo.update(elapsed_seconds.count(),w.carsinput,w.bikesinput,w.trucksinput);

                demo.printvehiclespos(machinestosprites);
                for(auto& elem:machinestosprites)
                {
                    w.SpriteQueue(elem->getposx(),elem->getposy(),elem->gettype());
                }
                machinestosprites.clear();

                w.repaint();
                w.SpriteClear();
                delay();
            }

            demo.printvehiclespos(machinestosprites);
            for(auto& elem:machinestosprites)
            {
                w.SpriteQueue(elem->getposx(),elem->getposy(),'m');
            }
            machinestosprites.clear();
        }

        w.repaint();
        delay();
    }

    return a.exec();
}
