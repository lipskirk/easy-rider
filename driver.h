#ifndef DRIVER_H
#define DRIVER_H
#include "vec2d.h"
#include "machine.h"

class Driver
{
private:
    bool turnright;
    bool isovertaking;
    float disttoturn;
    float disttoobstacle;
    float disttoovertake;

public:
    Driver();

    bool checkifturnright();
    bool checkifovertaking();
    float getdisttoturn();
    float getdisttoobstacle();
    float getdisttoovertake();

    void setturnright(bool xdir);
    void startovertaking();
    void overtakingdone();
    void setdisttoturn(float xdist);
    void setdisttoobstacle(float xdist);
    void setdisttoovertake(float xdist);


    void accelerate(Machine *&xmachine);
    void brake(Machine *&xmachine);
    void stop(Machine *&xmachine);
    void changelane(Machine *&xmachine, Vec2d xvec);
    void join(Machine *&xmachine, Vec2d xvec);
    void setistostop(float xdist);
    bool chooseifturn(float xdist, bool turnright, bool bypass=false);
    bool chooseifjoin(float xdist, bool xturnright, bool bypass=false);
    void resetdirection();

};

#endif // DRIVER_H
