#include "MainH.h"
class Process{
private:
    QString ID;
    QString State;
    QString File_Name;
    QString Instruction_Register;
    int Accumulator;
    int Temp;
    int PC;
public:
    Process()
    {
        this->ID = "";
        this->File_Name = "";
        this->State = "";
        this->Instruction_Register = "null";
        this->Accumulator = 0;
        this->PC = 0;
        this->Temp = 0;
    }
    void Set_ID(QString ID_Data)
    {
        this->ID = ID_Data;
    }
    void Set_File_Name(QString FN_Data)
    {
        this->File_Name = FN_Data;
    }
    void Set_State(QString S_Data)
    {
        this->State = S_Data;
    }
    void Set_IR(QString IR_Data)
    {
        this->Instruction_Register = IR_Data;
    }
    void Set_AC(int AC_Data)
    {
        this->Accumulator = AC_Data;
    }
    void Set_Temp(int T_Data)
    {
        this->Temp = T_Data;
    }
    void Set_PC(int PC_Data)
    {
        this->PC = PC_Data;
    }
    QString Get_ID()
    {
        return this->ID;
    }
    QString Get_State()
    {
        return this->State;
    }
    QString Get_FN()
    {
        return this->File_Name;
    }
    QString Get_IR()
    {
        return this->Instruction_Register;
    }
    int Get_AC()
    {
        return this->Accumulator;
    }
    int Get_Temp()
    {
        return this->Temp;
    }
    int Get_PC()
    {
        return this->PC;
    }

};
void Convert_State(QString state,Process p);
class Signal{
  private:
    //---
  public:
    void Create(QStringList Info,Process P)
    {
        QFile Check_ID("Process_File");
        Check_ID.open(QFile::ReadOnly | QFile::Text);
        QTextStream Check_ID_reader(&Check_ID);
        bool Is_Exist = false;
        while (!Check_ID_reader.atEnd())//ID,File_Name,State,I_R,ac,pc,temp
        {
            QStringList line = Check_ID_reader.readLine().split(',');
            if (line[0] == Info[1])
            {
                Is_Exist = true;
                break;
            }
        }
        Check_ID.close();
        if (Is_Exist == false)
        {
            P.Set_ID(Info[1]);
            P.Set_File_Name(Info[2]);
            P.Set_State("Ready");
            QFile Insert_Process("Process_File");
            Insert_Process.open(QFile::Append | QFile::Text);
            QTextStream Writer(&Insert_Process);
            Writer << P.Get_ID() << ',' << P.Get_FN() << ','
                   << P.Get_State() << ',' << P.Get_IR() << ','
                   << P.Get_AC() << ',' << P.Get_PC() << ','
                   << P.Get_Temp() << '\n';
            Insert_Process.close();
        }
        else
        {
            std::cout << "This ID Exist!" <<std::endl;
        }
    }
    void Run(QString ID)
    {
        Process P;
        QFile Find_Process("Process_File");
        QTextStream Find_Process_Reader(&Find_Process);
        Find_Process.open(QFile::ReadOnly | QFile::Text);
        while (!Find_Process_Reader.atEnd())
        {
            QStringList line = Find_Process_Reader.readLine().split(',');//ID,File_Name,State,I_R,ac,pc,temp
            if (ID == line[0])
            {
                P.Set_ID(line[0]);
                P.Set_File_Name(line[1]);
                P.Set_State(line[2]);
                P.Set_IR(line[3]);
                P.Set_AC(line[4].toInt());
                P.Set_PC(line[5].toInt());
                P.Set_Temp(line[6].toInt());
                break;
            }

        }
        Find_Process.close();
        if (P.Get_ID() == "")
        {
            std::cout << "Process Not Found!" << std::endl;
        }
        else
        {
            if (P.Get_State() == "Blocked")
            {
                std::cout << "Process is Blocked!" << std::endl;
            }
            else
            {
                P.Set_PC(P.Get_PC()+1);
                Convert_State("Running",P);
                int cnt = 1;
                QFile Instruction_File(P.Get_FN());
                QTextStream Instruction_File_Reader(&Instruction_File);
                Instruction_File.open(QFile::ReadOnly | QFile::Text);
                while(!Instruction_File_Reader.atEnd())
                {
                    QStringList Sl = Instruction_File_Reader.readLine().split(' ');
                    if (cnt == P.Get_PC())
                    {
                        P.Set_IR(Sl[0] + ' ' + Sl[1]);
                        if (Sl[0] == "load")
                        {
                            P.Set_Temp(Sl[1].toInt());
                            P.Set_AC(P.Get_Temp());
                        }
                        else if (Sl[0] == "sub")
                        {
                            P.Set_Temp(Sl[1].toInt());
                            P.Set_AC(P.Get_AC() - P.Get_Temp());
                        }
                        else if (Sl[0] == "add")
                        {
                            P.Set_Temp(Sl[1].toInt());
                            P.Set_AC(P.Get_AC() + P.Get_Temp());
                        }
                        else if (Sl[0] == "mul")
                        {
                            P.Set_Temp(Sl[1].toInt());
                            P.Set_AC(P.Get_AC() * P.Get_Temp());
                        }
                        Convert_State("Ready",P);
                        break;
                    }
                    else
                    {
                        cnt++;
                    }
                }
                Instruction_File.close();
            }
        }
    }
    void show(QString ID)
    {
        QFile Show_File("Process_File");
        QTextStream S_F_Reader(&Show_File);
        Show_File.open(QFile::ReadOnly | QFile::Text);
        while (!S_F_Reader.atEnd())
        {
            QStringList Sl = S_F_Reader.readLine().split(',');
            if (ID == Sl[0])
            {
                std::cout << "Process ID : " << Sl[0].toStdString() << std::endl;
                std::cout << "Instruction Register : " << Sl[3].toStdString() << std::endl;
                std::cout << std::endl;
                std::cout << "Accumulator : " << Sl[4].toStdString() << "     Temp : " << Sl[6].toStdString() << std::endl;
                std::cout << "Program Counter : " << Sl[5].toStdString() << "     State : " << Sl[2].toStdString() << std::endl;
            }
        }
    }
};
void Convert_State(QString state,Process p)//ID,File_Name,State,I_R,ac,pc,temp
{
    QFile Old_State("Process_File");
    QTextStream O_S_reader(&Old_State);
    QFile New_State("Process1_File");
    QTextStream N_S_Writer(&New_State);
    Old_State.open(QFile::ReadOnly | QFile::Text);
    New_State.open(QFile::WriteOnly | QFile::Text);
    while (!O_S_reader.atEnd())
    {
        QStringList Info = O_S_reader.readLine().split(',');
        if (Info[0] == p.Get_ID())
        {
            N_S_Writer << p.Get_ID() << ',' << p.Get_FN() << ','
                       << state << ',' << p.Get_IR() << ','
                       << p.Get_AC() << ',' << p.Get_PC() << ','
                       << p.Get_Temp() << '\n';
        }
        else
        {
            N_S_Writer << Info[0] << ',' << Info[1] << ','
                       << Info[2] << ',' << Info[3] << ','
                       << Info[4] << ',' << Info[5] << ','
                       << Info[6] << '\n';
        }
    }
    Old_State.remove();
    New_State.rename("Process_File");
}
int main (void)
{
    Signal sg;
//    Process P1;
//    QString s = "Create_Process Pr_1 P1_File";
//    QStringList sl = s.split(' ');
//    sg.Create(sl,P1);
//    s = "Create_Process Pr_2 process2_instruction_file.txt";
//    sl = s.split(' ');
//    Process P2;
//    sg.Create(sl,P2);
//    s = "Create_Process Pr_2 process2_instruction_file.txt";
//    sl = s.split(' ');
//    Process P3;
//    sg.Create(sl,P3);
//    Process P4;
//    s = "Create_Process Pr_1 process1_instruction_file.txt";
//    sl = s.split(' ');
//    sg.Create(sl,P1);
    //sg.Run("Pr_1");
    sg.show("Pr_1");

    return 0;
}
