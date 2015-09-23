
#ifndef STATELOADING
#define STATELOADING

#include "States/state.h"
#include "States/statemenu.h"

class StateLoading : public State {

private:
    GameWidget* widget;
    QPixmap* pixmaps;
    QPainter* painter;
    int count = 0;
    int counter = 0;

    StateLoading(GameWidget *widget) {
        this->widget = widget;
        fillPixmaps();
        setState();
    }

    void fillPixmaps() {
        pixmaps = new QPixmap[7];
        pixmaps[0] = QPixmap(":/images/tank_art.jpg");
        pixmaps[1] = QPixmap(":/images/tank_art_2.jpg");
        pixmaps[2] = QPixmap(":/images/tank_art_3.jpg");
        pixmaps[3] = QPixmap(":/images/loading1.png");
        pixmaps[4] = QPixmap(":/images/loading2.png");
        pixmaps[5] = QPixmap(":/images/loading3.png");
        pixmaps[6] = QPixmap(":/images/loading4.png");
    }

public:
    static State* getInstance(GameWidget *widget) {
        return new StateLoading(widget);
    }

    //In this state we dont need implementation of theese methods
    void keyPress(QKeyEvent* event) {}
    void mousePress(QMouseEvent* event) {}

    void paint() {
        counter ++;
        this->widget->setStyleSheet("background-color:black;");
        if(this->counter > 301) {
            //TODO : logic of changing state
            setState();
        }
        painter = new QPainter(widget);
        setLoadingScreen();
    }

    void setState() {
        widget->setState(StateType::MENU_STATE);
    }


    void setLoadingScreen() {

        if(counter < 50){
            painter->setOpacity(0.02*(double)counter);
            painter->drawPixmap(0, 0, pixmaps[0].scaled(widget->size()));
        }
        else if(counter >= 50 && counter < 100) {
            painter->setOpacity(0.02*(double)(100-counter));
            painter->drawPixmap(0, 0, pixmaps[0].scaled(widget->size()));
        } else if(counter >= 100 && counter < 150) {
            painter->setOpacity(0.02*(double)(counter-100));
            painter->drawPixmap(0, 0, pixmaps[1].scaled(widget->size()));
        } else if(counter >= 150 && counter < 200) {
            painter->setOpacity(0.02*(double)(200-counter));
            painter->drawPixmap(0, 0, pixmaps[1].scaled(widget->size()));
        } else if(counter >= 200 && counter < 250) {
            painter->setOpacity(0.02*(double)(counter-200));
            painter->drawPixmap(0, 0, pixmaps[2].scaled(widget->size()));
        } else if(counter >= 250 && counter < 300) {
            painter->setOpacity(0.02*(double)(300-counter));
            painter->drawPixmap(0, 0, pixmaps[2].scaled(widget->size()));
        } else {
        }

        loadTitleModule();
        loadGearsModule();

        if(counter > 300){
            setState();
           // this->connection->setConnection();
        }
    }

    void loadTitleModule() {

        QPixmap title(":/images/title.png");
        QPainter* titlePaint = new QPainter(widget);
        titlePaint->drawPixmap(widget->width() / 2 - title.width() / 2, 200, title);

        QPainter* loadingPainter = new QPainter(widget);
        switch(getSinusQuard((float)(6.14*(float)counter))) {
        case 1:
            loadingPainter->drawPixmap(widget->width() - 400, widget->height() - 150, pixmaps[3]);
            break;
        case 2:
            loadingPainter->drawPixmap(widget->width() - 400, widget->height() - 150, pixmaps[4]);
            break;
        case 3:
            loadingPainter->drawPixmap(widget->width() - 400, widget->height() - 150, pixmaps[5]);
            break;
        case 4:
            loadingPainter->drawPixmap(widget->width() - 400, widget->height() - 150, pixmaps[6]);
            break;
        }
    }

    void loadGearsModule() {
        QPainter* loadBig = new QPainter(widget);
        QPixmap gearBig(":/images/gearBig.png");
        QPixmap gearLittle(":/images/gearLittle.png");

        loadBig->setRenderHint(QPainter::Antialiasing);
        loadBig->setRenderHint(QPainter::SmoothPixmapTransform);
        loadBig->setRenderHint(QPainter::HighQualityAntialiasing);
        loadBig->translate(gearBig.size().width() + 330, gearBig.size().height() + 150);
        loadBig->rotate(2*counter);
        loadBig->translate(-gearBig.size().width() / 2, -gearBig.size().height() / 2);
        loadBig->drawPixmap(0 , 0, gearBig);
        delete loadBig;

        QPainter* loadLittle = new QPainter(widget);
        loadLittle->setRenderHint(QPainter::Antialiasing);
        loadLittle->setRenderHint(QPainter::SmoothPixmapTransform);
        loadLittle->setRenderHint(QPainter::HighQualityAntialiasing);
        loadLittle->translate(gearLittle.size().width() + 770, gearLittle.size().height()+440);
        loadLittle->rotate(-2*counter);
        loadLittle->translate(-gearLittle.size().width() / 2, -gearLittle.size().height() / 2);
        loadLittle->drawPixmap(0 , 0, gearLittle);
        delete loadLittle;
    }
    int getSinusQuard(float angle) {
        float temp = angle;
        while(temp > 360)
            temp -= 360;
        if(temp > 0 && temp <= 90)
            return 1;
        if(temp > 90 && temp <= 180)
            return 2;
        if(temp > 180 && temp <= 270)
            return 3;
        return 4;
    }
};

#endif // STATELOADING

