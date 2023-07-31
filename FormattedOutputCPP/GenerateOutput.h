#include <cstdlib>
#include <fstream>
// using namespace std;

void ExeAutomation()
{
    ofstream clearFile("@Automation.txt", 'w');
    clearFile.close();
    system("automation.py > @Automation.txt");
    // system("automation.py");
}