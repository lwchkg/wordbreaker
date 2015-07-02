#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "trie/trie.h"

using namespace std;

// This version has no weight and no timer

string lowerOnly(const string& s)
{
    string s1;
    for (string::const_iterator it = s.begin(); it != s.end(); ++it)
    {
        char c = tolower(*it);
        if (islower(c))
        {
            s1.push_back(c);
        }
    }
    return s1;
}

void outputResult(const string& s, const vector<vector<int> >& backpos, int startpos, int endpos)
{
    vector<int> pos;
    for(int i = endpos; i >= startpos;)
    {
        pos.push_back(i);
        if (!backpos[i].size()) break;
        i = backpos[i][0];
    }

    int prevpos = -1;
    for(vector<int>::reverse_iterator it = pos.rbegin();
        it != pos.rend();
        prevpos = *it, ++it) {

        if (prevpos == -1) continue;
        cout << s.substr(prevpos, *it - prevpos) << " ";
    }
}

int main()
{
    trie<int> t;

    string line;
    ifstream myfile("words-35.txt", ios::binary);
    if (myfile.is_open())
    {
        while (!myfile.eof())
        {
            getline(myfile, line);
            line = lowerOnly(line);
            t.add(line, 0);
        }
        myfile.close();
    }
    else
    {
        cout << "Cannot read words.txt" << endl;
        return 1;
    }

    cout << "Number of words in dictionary: " << t.length << endl;

    cout << "Enter the string to be broken into words: ";
    string s;
    getline(cin, s);
    cout << endl << endl << "Result:" << endl;

    s = lowerOnly(s);


    vector<vector<int> > backpos(s.length() + 1);


    size_t maxpos = 0, startpos = 0;
    for (size_t i=0; i<s.length(); i++)
    {
        if (i > maxpos) {
            // no matching possible - output result and set startpos to new position
            outputResult(s, backpos, startpos, maxpos);
            cout << s[i-1] << " ";
            startpos = i;
        }
        else
        {
            if (i && !backpos[i].size()) continue;
        }

        vector<size_t> matches = t.lookupallLength(s, i);

        for (vector<size_t>::iterator it = matches.begin(); it != matches.end(); ++it)
        {
            backpos[i + *it].push_back(i);
            maxpos = max(maxpos, i + *it);
        }
    }

    outputResult(s, backpos, startpos, maxpos);

    return 0;
}
