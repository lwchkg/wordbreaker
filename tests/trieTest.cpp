#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <utility>
#include <cstdlib>
#include <time.h>

#include "../trie/trie.h" // self-made trie library


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

template <typename T>
string NumberToString( T Number )
{
    ostringstream ss;
    ss << Number;
    return ss.str();
}

void test1()
{
    cout << "Functional test" << endl
         << "===============" << endl;

    trie<int> t;
    t.add("apple", 100).add("all", 200).add("allstar", 300).add("star", 400);

    cout << "Lookups" << endl;
    int junk;
    cout << t.lookup("appl", junk) << endl;
    cout << t.lookup("apple", junk) << endl;
    cout << t.lookup("apples", junk) << endl;
    cout << t.lookup("bad", junk) << endl;

    cout << endl;

    cout << "Matching from position 0 (implicit)" << endl;

    vector<int> matchvalue;
    vector<string> matchkey;
    vector<trieKeyValue<int> > matchKeyValue;
    vector<size_t> matchLength;
    vector<trieLengthValue<int> > matchLengthValue;

    matchvalue = t.lookupallValue("allstars");
    cout << matchvalue.size() << " matches : ";
    for (std::vector<int>::const_iterator i = matchvalue.begin(); i != matchvalue.end(); ++i)
        std::cout << *i << ' ';
    cout << endl;

    matchkey = t.lookupallKey("allstars");
    cout << matchkey.size() << " matches : ";
    for (std::vector<string>::const_iterator i = matchkey.begin(); i != matchkey.end(); ++i)
        std::cout << *i << ' ';
    cout << endl;

    matchKeyValue = t.lookupallKeyValue("allstars");
    cout << matchKeyValue.size() << " matches : ";
    for (std::vector<trieKeyValue<int> >::const_iterator i = matchKeyValue.begin(); i != matchKeyValue.end(); ++i)
        std::cout << i -> key << ',' << i -> value << ' ';
    cout << endl;

    matchLength = t.lookupallLength("allstars");
    cout << matchLength.size() << " matches : ";
    for (std::vector<size_t>::const_iterator i = matchLength.begin(); i != matchLength.end(); ++i)
        std::cout << *i << ' ';
    cout << endl;

    matchLengthValue = t.lookupallLengthValue("allstars");
    cout << matchLengthValue.size() << " matches : ";
    for (std::vector<trieLengthValue<int> >::const_iterator i = matchLengthValue.begin(); i != matchLengthValue.end(); ++i)
        std::cout << i -> length << ',' << i -> value << ' ';
    cout << endl;

    cout << endl;


    cout << "Matching from position 3" << endl;

    matchvalue = t.lookupallValue("allstars", 3);
    cout << matchvalue.size() << " matches : ";
    for (std::vector<int>::const_iterator i = matchvalue.begin(); i != matchvalue.end(); ++i)
        std::cout << *i << ' ';
    cout << endl;

    matchkey = t.lookupallKey("allstars", 3);
    cout << matchkey.size() << " matches : ";
    for (std::vector<string>::const_iterator i = matchkey.begin(); i != matchkey.end(); ++i)
        std::cout << *i << ' ';
    cout << endl;

    matchKeyValue = t.lookupallKeyValue("allstars", 3);
    cout << matchKeyValue.size() << " matches : ";
    for (std::vector<trieKeyValue<int> >::const_iterator i = matchKeyValue.begin(); i != matchKeyValue.end(); ++i)
        std::cout << i -> key << ',' << i -> value << ' ';
    cout << endl;

    matchLength = t.lookupallLength("allstars", 3);
    cout << matchLength.size() << " matches : ";
    for (std::vector<size_t>::const_iterator i = matchLength.begin(); i != matchLength.end(); ++i)
        std::cout << *i << ' ';
    cout << endl;

    matchLengthValue = t.lookupallLengthValue("allstars", 3);
    cout << matchLengthValue.size() << " matches : ";
    for (std::vector<trieLengthValue<int> >::const_iterator i = matchLengthValue.begin(); i != matchLengthValue.end(); ++i)
        std::cout << i -> length << ',' << i -> value << ' ';
    cout << endl;

    cout << endl;
    return;
}

void test2()
{
    const int dicSize = 100000, nTries = 100;

    cout << "Memory leak test" << endl
         << "================" << endl;

    string s;

    vector<string> dict;
    for (int i = 0; i < dicSize; ++i) {
        int j = rand() % 100;
        size_t l = j < 70 ? (j / 7 + 1) : ((j-70) / 3 + 11);

        s = "";
        for (size_t p = 0; p < l; p++) {
            int k = rand() % 26;
            s += char('a' + k);
        }
        dict.push_back(s);
    }

    cout << "Generated a dictionary of size " << dicSize << endl;

    cout << "Please check memory usage and then press Enter.";
    getline(cin, s);

    for (int i = 1; i <= nTries; ++i)
    {
        cout << "Pass " << i << " ...";

        trie<int> t;

        for (vector<string>::const_iterator it = dict.begin(); it != dict.end(); ++it)
        {
            t.add(*it, 0);
        }

        cout << " end." << endl;
    }

    cout << "Please check memory usage again and then press Enter.";
    getline(cin, s);

    return;
}

int main()
{
    srand(time(NULL));

    test1();
    test2();
    return 0;
}
