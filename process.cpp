#include "process.h"

process::process()
{
    this->ID = "";
    this->fileName = "";
    this->state = "";
    this->IR = "null";
    this->AC = 0;
    this->PC = 0;
    this->temp = 0;
}

void process::setID(QString ID)
{
    this->ID = ID;
}

void process::setFileName(QString fileName)
{
    this->fileName = fileName;
}

void process::setState(QString state)
{
    this->state = state;
}

void process::setIR(QString IR)
{
    this->IR = IR;
}

void process::setAC(int AC)
{
    this->AC = AC;
}

void process::setTemp(int temp)
{
    this->temp = temp;
}

void process::setPC(int PC)
{
    this->PC = PC;
}

QString process::getID()
{
    return this->ID;
}

QString process::getState()
{
    return this->state;
}

QString process::getFileName()
{
    return this->fileName;
}

QString process::getIR()
{
    return this->IR;
}

int process::getAC()
{
    return this->AC;
}

int process::getTemp()
{
    return this->temp;
}

int process::getPC()
{
    return this->PC;
}

void Signal::Create(QStringList info, process process)
{
    QFile checkID("processFile.txt");
    checkID.open(QFile::ReadOnly | QFile::Text);
    QTextStream Reader(&checkID);
    bool isExist = false;
    while (!Reader.atEnd()) //format: ID,File_Name,State,I_R,ac,pc,temp
    {
        QStringList line = Reader.readLine().split(',');
        if (line[0] == info[1])
        {
            isExist = true;
            break;
        }
    }
    checkID.close();
    if (!isExist)
    {
        process.setID(info[1]);
        process.setFileName(info[2]);
        process.setState("Ready");
        QFile insertProcess("processFile.txt");
        insertProcess.open(QFile::Append | QFile::Text);
        QTextStream writer(&insertProcess);
        writer << process.getID() << ',' << process.getFileName() << ',' << process.getState() << ',' << process.getIR() << ',' << process.getAC() << ',' << process.getPC() << ',' << process.getTemp() << '\n';
        insertProcess.close();
    }
    else
        std::cout << "This ID Exist!" << std::endl;
}

void Signal::Run(QString ID)
{
    process process;
    QFile findProcess("processFile.txt");
    QTextStream reader(&findProcess);
    findProcess.open(QFile::ReadOnly | QFile::Text);
    while (!reader.atEnd())
    {
        QStringList line = reader.readLine().split(','); //format: ID,File_Name,State,I_R,ac,pc,temp
        if (ID == line[0])
        {
            process.setID(line[0]);
            process.setFileName(line[1]);
            process.setState(line[2]);
            process.setIR(line[3]);
            process.setAC(line[4].toInt());
            process.setPC(line[5].toInt());
            process.setTemp(line[6].toInt());
            break;
        }

    }
    findProcess.close();
    if (process.getID().isEmpty())
        std::cout << "Process Not Found!" << std::endl;
    else
    {
        if (process.getState() == "Blocked")
            std::cout << "Process is Blocked!" << std::endl;
        else
        {
            process.setPC(process.getPC()+1);
            convertState("Running", process);
            int cnt = 1;
            QFile instructionFile(process.getFileName());
            QTextStream Reader(&instructionFile);
            instructionFile.open(QFile::ReadOnly | QFile::Text);
            while(!Reader.atEnd())
            {
                QStringList Sl = Reader.readLine().split(' ');
                if (cnt == process.getPC())
                {
                    process.setIR(Sl[0] + ' ' + Sl[1]);
                    if (Sl[0] == "load")
                    {
                        process.setTemp(Sl[1].toInt());
                        process.setAC(process.getTemp());
                    }
                    else if (Sl[0] == "sub")
                    {
                        process.setTemp(Sl[1].toInt());
                        process.setAC(process.getAC() - process.getTemp());
                    }
                    else if (Sl[0] == "add")
                    {
                        process.setTemp(Sl[1].toInt());
                        process.setAC(process.getAC() + process.getTemp());
                    }
                    else if (Sl[0] == "mul")
                    {
                        process.setTemp(Sl[1].toInt());
                        process.setAC(process.getAC() * process.getTemp());
                    }
                    convertState("Ready", process);
                    break;
                }
                else
                    cnt++;
            }
            instructionFile.close();
        }
    }
}

void Signal::show(QString ID)
{
    QFile showFile("processFile.txt");
    QTextStream reader(&showFile);
    showFile.open(QFile::ReadOnly | QFile::Text);
    while (!reader.atEnd())
    {
        QStringList Sl = reader.readLine().split(',');
        if (ID == Sl[0])
            std::cout << "Process ID : " << Sl[0].toStdString() << std::endl << "Instruction Register : " << Sl[3].toStdString() << std::endl << std::endl << "Accumulator : " << Sl[4].toStdString() << "     Temp : " << Sl[6].toStdString() << std::endl << "Program Counter : " << Sl[5].toStdString() << "     State : " << Sl[2].toStdString() << std::endl;
    }
}

void Signal::kill(process process)
{
    QFile oldState("processFile.txt");
    QTextStream reader(&oldState);
    QFile newState("tmp.txt");
    QTextStream Writer(&newState);
    oldState.open(QFile::ReadOnly | QFile::Text);
    newState.open(QFile::WriteOnly | QFile::Text);
    while (!reader.atEnd())
    {
        QStringList Info = reader.readLine().split(',');
        if (Info[0] != process.getID())
            Writer << Info[0] << ',' << Info[1] << ',' << Info[2] << ',' << Info[3] << ',' << Info[4] << ',' << Info[5] << ',' << Info[6] << endl;
    }
    oldState.remove();
    newState.rename("processFile.txt");
}

void Signal::block(process process)
{
    convertState("blocked", process);
}

void convertState(QString state, process process)
{
    QFile oldState("processFile.txt");
    QTextStream reader(&oldState);
    QFile newState("tmp.txt");
    QTextStream Writer(&newState);
    oldState.open(QFile::ReadOnly | QFile::Text);
    newState.open(QFile::WriteOnly | QFile::Text);
    while (!reader.atEnd())
    {
        QStringList Info = reader.readLine().split(',');
        if (Info[0] == process.getID())
            Writer << process.getID() << ',' << process.getFileName() << ',' << state << ',' << process.getIR() << ',' << process.getAC() << ',' << process.getPC() << ',' << process.getTemp() << endl;
        else
            Writer << Info[0] << ',' << Info[1] << ',' << Info[2] << ',' << Info[3] << ',' << Info[4] << ',' << Info[5] << ',' << Info[6] << endl;
    }
    oldState.remove();
    newState.rename("processFile.txt");
}
