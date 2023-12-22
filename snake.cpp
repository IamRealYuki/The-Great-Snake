#include<windows.h> 
#include<iostream>
using namespace std;
int main()
{
    cout << WinExec("SFMLlib\\bin\\main.exe", 9);
    cout << endl <<"I am in the new stream";
    return 0;
}