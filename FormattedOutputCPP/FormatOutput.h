#include <iostream>
#include <algorithm>
#include <string.h>
#include <string>
#include <fstream>
#include <regex>
using namespace std;

void Replace_all(string&, string const&, string const&);
void ReadFile()
{
    int line_index=0;
    string target = ", ";
    string file_dir = "@AutomationLog.txt";
    // string file_dir = "datagridview.txt";
    // string file_dir = "listbox.txt";
    string readline;
    string outputLines="";
    string test_str = "ControlType: PaneControl    ClassName: #32769    AutomationId:     Rect: (0,0,1920,1080)[1920x1080]    Name: '®à­± 1'    Handle: 0x10010(65552)    Depth: 0    SupportedPattern: LegacyIAccessiblePattern";
    ifstream inputFile(file_dir);
    ofstream outputFile("outputFile.txt", 'w');
    regex rect_pattern("(Rect: )\\(((-*\\d+,){3}-*\\d+)\\)");
    regex name_pattern("(Name: )('([^']*)')");
    regex value_pattern("(ValuePattern.Value: )('([^']*)')");
    regex pass_pattern("CustomControl|MenuBarControl|MenuItemControl|ButtonControl|ListControl");
    // regex pass_pattern("¸ê®Æ¦C|CustomControl");
    if(inputFile.is_open())
    {
        while(getline(inputFile, readline))
        {
            smatch rect_match;
            smatch name_match;
            smatch value_match;
            smatch pass_match;
            if(regex_search(readline, pass_match, pass_pattern))
            {
                cout << pass_match[0] << endl;
                continue;
            }
            else
            {
                if(regex_search(readline, rect_match, rect_pattern))
                    {
                        line_index++;
                        outputLines+=to_string(line_index);
                        outputLines+="@";
                        outputLines+=rect_match[2];
                    }
                    if(regex_search(readline, value_match, value_pattern))
                    {
                        outputLines += value_match[2];
                    }
                    else
                    {
                        if(regex_search(readline, name_match, name_pattern))
                        {
                            outputLines += name_match[2];
                        }
                    }
                    Replace_all(outputLines, ",", "@");
                    Replace_all(outputLines, "'", "@");
                    if(outputLines != "")
                    {
                        outputLines.pop_back();
                        outputFile << outputLines << endl;
                    }
            }
            outputLines = "";
        }
        inputFile.close();
    }
    else
    {
        cout << "File not exist" << endl;
    }
    outputFile.close();
    inputFile.close();
}
void Replace_all(
    string& s,
    string const& toReplace,
    string const& replaceWith
) {
    string buf;
    size_t pos = 0;
    size_t prevPos;

    // Reserves rough estimate of final size of string.
    buf.reserve(s.size());

    while (true) {
        prevPos = pos;
        pos = s.find(toReplace, pos);
        if (pos == string::npos)
            break;
        buf.append(s, prevPos, pos - prevPos);
        buf += replaceWith;
        pos += toReplace.size();
    }

    buf.append(s, prevPos, s.size() - prevPos);
    s.swap(buf);
}