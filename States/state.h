#ifndef STATE
#define STATE

#include "gamewidget.h"
#include "Helpers/gameconstants.h"
#include "Helpers/log.h"

#include <QKeyEvent>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include <QPaintEvent>
#include <QPainter>
#include <QImage>
#include <QRect>
#include <QBrush>

class GameWidget;

class State {

public:
    virtual void paint() = 0;
    virtual void keyPress(QKeyEvent* event) = 0;
    virtual void mousePress(QMouseEvent* event) = 0;
};

#endif // STATE

