#include <bits/stdc++.h>
#include <process.h>
using namespace std;

int main()
{
    QFile file("processFile");
    file.open(QFile::WriteOnly | QFile::Text);
    file.remove();
    Signal sg;
    int i = 0;
    QFile Input_File("Input");
    QTextStream reader(&Input_File);
    Input_File.open(QFile::ReadOnly | QFile::Text);
    while(!reader.atEnd())
    {
        std::cout << "loop : " << i++ << std::endl;
        process p;
        QStringList value = reader.readLine().split(' ');
        if(value[0] == "create_process")
        {
            sg.Create(value, p);
        }
        else if (value[0] == "run_process")
        {
            sg.Run(value[1]);
        }
        else if (value[0] == "block_process")
        {
            sg.block_unblock(value[1],"Blocked");
        }
        else if (value[0] == "show_context")
        {
            sg.show(value[1]);
        }
        else if (value[0] == "unblock_process")
        {
            sg.block_unblock(value[1],"Ready");
        }
        else if (value[0] == "kill_process")
        {
            sg.kill(value[1]);
        }
    }
    Input_File.close();
    return 0;
}
