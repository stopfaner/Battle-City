#ifndef STATERATINGS
#define STATERATINGS

#include "States/state.h"
#include <fstream>
#include <string>

using namespace std;

class StateRatings : public State {

private:

    class Rate {
        public:
        string score;
        string name;
    };

    std::string path = "C:\\Users\\Denys\\Documents\\Tanks\\rating.dat";
    std::vector<Rate> rates;

    GameWidget* widget;
    QPainter* painter;

    StateRatings(GameWidget* widget) {
        this->widget =  widget;
        readData();
        sort();
    }

    void readData() {
        ifstream fin(path);
        while(!fin.eof()) {
            Rate temp;
            fin >> temp.name;
            fin >> temp.score;
            rates.push_back(temp);
        }
        fin.close();
    }

    void displayData() {
        for(int i = 0; i < 10; i++) {
            if(rates[i].name != "" && rates[i].score != "") {
                painter->drawText(widget->size().width() / 2 - 250, 350 + i*50, QString(rates[i].name.c_str()));
                painter->drawText(widget->size().width() / 2 + 200, 350 + i*50, QString(rates[i].score.c_str()));
            } else
                i = 10;
        }
    }

public:
    static State* getInstance(GameWidget* widget) {
        return new StateRatings(widget);
    }

    void paint() {
        painter = new QPainter(widget);
        painter->drawPixmap(0, 0, QPixmap(":/images/menubackground.png").scaled(widget->size()));

        painter->setPen(QColor(Qt::white));
        painter->setFont(QFont("Arial",25));

        painter->drawText(widget->size().width() / 2 - 50, 200, "Ratings");
        painter->drawText(widget->size().width() / 2 - 250, 250, "Name");
        painter->drawText(widget->size().width() / 2 + 200, 250, "Score");
        displayData();
    }

    void sort() {
        for(int i = 0; i < rates.size(); i++){
                for(int j = rates.size() - 1 ; j > i; j--){
                    if(rates[j-1].score.compare(rates[j].score) < 0){
                        Rate x = rates[j-1];
                        rates[j-1] = rates[j];
                        rates[j] = x;
                    }
                }
            }
    }


    void keyPress(QKeyEvent* event) {
        if(event->key() == Qt::Key_Escape)
            widget->setState(StateType::MENU_STATE);
    }

    void mousePress(QMouseEvent* event) {

    }

};

#endif // STATERATINGS

