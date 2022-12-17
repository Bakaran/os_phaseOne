#ifndef PROCESS_H
#define PROCESS_H

#include <bits/stdc++.h>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>

class process
{
private:
    QString ID, state, fileName, IR;
    int AC, temp, PC;

public:
    process();

    //setter functrion
    void setID(QString);
    void setFileName(QString);
    void setState(QString);
    void setIR(QString);
    void setAC(int);
    void setTemp(int);
    void setPC(int);

    //getter function
    QString getID();
    QString getState();
    QString getFileName();
    QString getIR();
    int getAC();
    int getTemp();
    int getPC();
};

void convertState(QString, process); //format: ID,File_Name,State,I_R,ac,pc,temp

class Signal{
public:
    void Create(QStringList, process);
    void Run(QString);
    void show(QString);
    void kill(QString);
    void block_unblock(QString,QString);
};

#endif // PROCESS_H
