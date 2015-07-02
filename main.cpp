#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <utility>

#include "Timer/Timer.h" // High resolution timer by Song Ho Ahn (2003)
#include "trie/trie.h" // self-made trie library


using namespace std;

// strip non-letters, convert all to lower case
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

// strip everything other than letters and digits, convert all to lower case
// put into array of strings, alternating between letters and digits
vector<string> lowerOnlySplitDigits(const string& s)
{
    vector<string> vs;
    string s1;
    bool digit = false;

    for (string::const_iterator it = s.begin(); it != s.end(); ++it)
    {
        char c = tolower(*it);
        if (islower(c))
        {
            if (digit)
            {
                vs.push_back(s1);
                s1 = "";
                digit = false;
            }
            s1.push_back(c);
        }
        else if (isdigit(c))
        {
            if (!digit)
            {
                vs.push_back(s1);
                s1 = "";
                digit = true;
            }
            s1.push_back(c);
        }
    }
    if (s1.length()) vs.push_back(s1);
    return vs;
}


void outputResult(const string& s, const vector<vector<pair<int, int> > >& backpos, int startpos, int endpos)
{
    vector<int> pos;
    for(int i = endpos; i >= startpos;)
    {
        pos.push_back(i);
        if (!backpos[i].size()) break;
        i = backpos[i][0].second;
    }

    int prevpos = -1;
    for(vector<int>::reverse_iterator it = pos.rbegin();
            it != pos.rend();
            prevpos = *it, ++it)
    {

        if (prevpos == -1) continue;
        cout << s.substr(prevpos, *it - prevpos) << " ";
    }
}

template <typename T>
string NumberToString( T Number )
{
    ostringstream ss;
    ss << Number;
    return ss.str();
}

int main()
{
    trie<int> t;

    const int f1[] = {10, 20, 35, 40, 50};
    const vector<int> fns(f1, f1+5);


    Timer timer;
    timer.start();

    for (vector<int>::const_iterator it = fns.begin(); it != fns.end(); ++it)
    {
        string line, fn;
        fn = "words-" + NumberToString(*it) + ".txt";
        ifstream myfile(fn.data(), ios::binary);
        if (myfile.is_open())
        {
            while (!myfile.eof())
            {
                getline(myfile, line);
                line = lowerOnly(line);

                // slightly prefer word ending with s
                int weight = *(line.rbegin()) == 's' ? *it - 2 : *it;
                t.add(line, weight);
            }
            myfile.close();
        }
        else
        {
            cout << "Cannot read words-" << *it << ".txt" << endl;
            //return 1;
        }
        cout << "Number of words after reading words-" << *it << ".txt : " << t.length << endl;
    }

    timer.stop();
    cout << endl << "Time elapsed in reading dictionary: " << timer.getElapsedTime() << "s" << endl;



    cout << endl << "Enter the string to be broken into words: ";
    string s;
    getline(cin, s);
    cout << endl << endl << "Result:" << endl;

    // vs = vector of string
    vector<string> vs = lowerOnlySplitDigits(s);


    timer.start();

    bool digits = true;
    for (vector<string>::const_iterator it2 = vs.begin(); it2 != vs.end(); ++it2)
    {
        string s = *it2;

        digits = !digits;
        if (digits)
        {
            cout << s << " ";
            continue;
        }

        // data for Dijkstra's algorithm : the data is (totalWeight, posOfPreviousWord)
        vector<vector<pair<int, int> > > backpos(s.length() + 1);


        size_t maxpos = 0, startpos = 0;
        for (size_t i=0; i<s.length(); i++)
        {
            int currWeight;

            if (i > maxpos)
            {
                // no matching possible - output result and set startpos to new position
                outputResult(s, backpos, startpos, maxpos);
                cout << s[i-1] << " ";
                startpos = i;
                currWeight = 0;
            }
            else if (!i)
            {
                currWeight = 0;
            }
            else
            {
                if (!backpos[i].size()) continue;

                sort(backpos[i].begin(), backpos[i].end());
                currWeight = backpos[i][0].first;
            }
            vector<trieLengthValue<int> > matches = t.lookupallLengthValue(s, i);

            for (vector<trieLengthValue<int> >::const_iterator it = matches.begin(); it != matches.end(); ++it)
            {
                backpos[i + it->length].push_back(make_pair(currWeight + it->value, i));
                maxpos = max(maxpos, i + it->length);
            }
        }
        sort(backpos[backpos.size()-1].begin(), backpos[backpos.size()-1].end());

        outputResult(s, backpos, startpos, maxpos);
    }

    timer.stop();
    cout << endl << endl << "Time elapsed in splitting: " << timer.getElapsedTime() << "s" << endl;

    return 0;
}
