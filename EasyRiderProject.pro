QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    app.cpp \
    bike.cpp \
    car.cpp \
    driver.cpp \
    machine.cpp \
    main.cpp \
    mainwindow.cpp \
    objective.cpp \
    objectivecross.cpp \
    objectiveforward.cpp \
    objectivejoin.cpp \
    objectivestop.cpp \
    objectiveturn.cpp \
    road.cpp \
    roadmap.cpp \
    simulation.cpp \
    truck.cpp \
    vec2d.cpp \
    vehicle.cpp \
    vehicles.cpp

HEADERS += \
    app.h \
    bike.h \
    car.h \
    driver.h \
    machine.h \
    mainwindow.h \
    objective.h \
    objectivecross.h \
    objectiveforward.h \
    objectivejoin.h \
    objectivestop.h \
    objectiveturn.h \
    road.h \
    roadmap.h \
    simulation.h \
    truck.h \
    vec2d.h \
    vehicle.h \
    vehicles.h

FORMS += \
    mainwindow.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
