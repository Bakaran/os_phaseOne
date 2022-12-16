#include "MainH.h"
class Process{
private:
    QString ID;
    QString State;
    QString File_Name;
    int Instruction_Register;
    int Accumulator;
    int Temp;
    int PC;
public:
    Process(QString ID,QString File_Name)
    {
        this->ID = ID;
        this->File_Name = File_Name;
        this->State = "Ready";
        this->Instruction_Register = 0;
        this->Accumulator = 0;
        this->PC = 0;
        this->Temp = 0;
    }
    void Set_IR(int IR_Data)
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
    int Get_IR()
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

int main (void)
{
    std::cout <<  "hello world!" <<std::endl;
}
