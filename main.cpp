#include <bits/stdc++.h>
#include <process.h>
using namespace std;

int main()
{
    Signal sg;
    QList<process> processes;
    int i = 0;
    while(1)
    {
        cout << "loop : " << i++ << endl;
        QTextStream s(stdin);
        QStringList value = s.readLine().split(' ');
        if(value[0] == "create_process")
        {
            processes.addLast;
            sg.Create(vlaue, )
        }
    }
    return 0;
}
