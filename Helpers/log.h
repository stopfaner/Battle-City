#ifndef LOG
#define LOG

#include <fstream>
#include <ctime>
#include <QDebug>
#include <QString>

using namespace std;

class Log {

private:
    char* FILE_PATH = "C:\\Users\\Denys\\Documents\\Tanks\\Log.txt";
    ofstream of;

    Log() {
        of.open(FILE_PATH);
    }
    Log(const Log& game);
    Log& operator=(const Log& game);

    string getCurrentDateTime() {
        time_t rawtime;
        struct tm * timeinfo;
        char buffer[80];

        time (&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer,80,"%d-%m-%Y %I:%M:%S",timeinfo);
        string str(buffer);
        return str;
    }

    string resultString(char* type, const string& TAG, const string& MESSAGE) {
        string result = "[";
        result += getCurrentDateTime();
        result += "] ";
        result += TAG;
        result += " | ";
        result += type;
        result += " | ";
        result += MESSAGE;
        return result;
    }

public:
    static Log& getInstance() {
        static Log log;
        return log;
    }

    void debug(const string& TAG, const string& MESSAGE){
        if(!of.is_open())
            of.open(FILE_PATH);
        of<<resultString("DEBUG", TAG, MESSAGE)<<endl;
    }

    void info(const string& TAG, const string& MESSAGE){
          if(!of.is_open())
            of.open(FILE_PATH);
          of<<resultString("INFO", TAG, MESSAGE)<<endl;
    }

    void warning(const string& TAG, const string& MESSAGE){
        if(!of.is_open())
            of.open(FILE_PATH);
        of<<resultString("WARNING", TAG, MESSAGE)<<endl;
    }

    void wtf(const string& TAG, const string& MESSAGE){
        if(!of.is_open())
            of.open(FILE_PATH);
        of<<resultString("WTF IS GOING ON", TAG, MESSAGE)<<endl;
    }

    void game(const string& TAG, const string& MESSAGE){
        if(!of.is_open())
            of.open(FILE_PATH);
        of<<resultString("GAME", TAG, MESSAGE)<<endl;
    }

};

#endif // LOG

