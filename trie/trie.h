#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
#include <utility>

#include "trieStruct.h"
#include "trieNode.h"


using namespace std;

template<typename T>
class trie
{
public:
    int length;

    /** Default constructor */
    trie() { length = 0; };

    /** Default destructor */
    virtual ~trie() {};

    /** Member functions*/
    trie<T>& add(const string& s, T value);

    // lookup: return true for match, false for no match. data store the value if matched.
    bool lookup(const string& s, T& value);

    // return vector of values
    vector<T> lookupallValue(const string& s, size_t startpos = 0);

    // return vector of keys
    vector<string> lookupallKey(const string& s, size_t startpos = 0);

    // return vector of key-value pairs
    vector<trieKeyValue<T> > lookupallKeyValue(const string& s, size_t startpos = 0);

    // return vector of lengths
    vector<size_t> lookupallLength(const string& s, size_t startpos = 0);

    // return vector of length-value pairs
    vector<trieLengthValue<T> > lookupallLengthValue(const string& s, size_t startpos = 0);

protected:
private:
    trieNode<T> rootNode;
};


template<typename T>
trie<T>& trie<T>::add(const string& s, T value)
{

    trieNode<T>* curNode = &(this->rootNode);

    for (string::const_iterator it = s.begin(); it != s.end(); ++it)
    {
        char c = tolower(*it);
        // ignore characters not in a-z
        if (islower(c))
        {
            int i = c - 'a';
            if (!curNode->child[i])
            {
                curNode->child[i] = new trieNode<T>;
            }
            curNode = curNode->child[i];
        }
    }

    // check if the node has advanced
    if (curNode != &(this->rootNode))
    {
        if (!curNode->hasData)
        {
            ++this->length;
            curNode->hasData = true;
            curNode->value = value;
        }
    }

    return *this;

};


template<typename T>
bool trie<T>::lookup(const string& s, T& value)
{

    trieNode<T>* curNode = &(this->rootNode);

    for (string::const_iterator it = s.begin(); it != s.end(); ++it)
    {
        char c = tolower(*it);
        // ignore characters not in a-z
        if (islower(c))
        {
            int i = c - 'a';
            if (!curNode->child[i])
            {
                return false;
            }
            curNode = curNode->child[i];
        }
    }

    if (curNode->hasData)
    {
        value = curNode->value;
        return true;
    }
    return false;

};

template <typename T>
vector<T> trie<T>::lookupallValue(const string& s, size_t startpos)
{

    vector<T> ret;

    trieNode<T>* curNode = &(this->rootNode);

    for (string::const_iterator it = s.begin() + startpos; it != s.end(); ++it)
    {
        char c = tolower(*it);
        // ignore characters not in a-z
        if (islower(c))
        {
            int i = c - 'a';
            if (!curNode->child[i])
            {
                return ret;
            }
            curNode = curNode->child[i];
            if (curNode->hasData)
            {
                ret.push_back(curNode->value);
            }
        }
    }
    return ret;
};

template <typename T>
vector<string> trie<T>::lookupallKey(const string& s, size_t startpos)
{

    vector<string> ret;

    trieNode<T>* curNode = &(this->rootNode);

    for (string::const_iterator it = s.begin() + startpos; it != s.end(); ++it)
    {
        char c = tolower(*it);
        // ignore characters not in a-z
        if (islower(c))
        {
            int i = c - 'a';
            if (!curNode->child[i])
            {
                return ret;
            }
            curNode = curNode->child[i];
            if (curNode->hasData)
            {
                ret.push_back(s.substr(startpos, it - s.begin() - startpos + 1));
            }
        }
    }
    return ret;
};

template <typename T>
vector<trieKeyValue<T> > trie<T>::lookupallKeyValue(const string& s, size_t startpos)
{

    vector<trieKeyValue<T> > ret;

    trieNode<T>* curNode = &(this->rootNode);

    for (string::const_iterator it = s.begin() + startpos; it != s.end(); ++it)
    {
        char c = tolower(*it);
        // ignore characters not in a-z
        if (islower(c))
        {
            int i = c - 'a';
            if (!curNode->child[i])
            {
                return ret;
            }
            curNode = curNode->child[i];
            if (curNode->hasData)
            {
                ret.push_back(make_trieKeyValue(s.substr(startpos, it - s.begin() - startpos + 1), curNode->value));
            }
        }
    }
    return ret;
};

template <typename T>
vector<size_t> trie<T>::lookupallLength(const string& s, size_t startpos)
{

    vector<size_t> ret;

    trieNode<T>* curNode = &(this->rootNode);

    for (string::const_iterator it = s.begin() + startpos; it != s.end(); ++it)
    {
        char c = tolower(*it);
        // ignore characters not in a-z
        if (islower(c))
        {
            int i = c - 'a';
            if (!curNode->child[i])
            {
                return ret;
            }
            curNode = curNode->child[i];
            if (curNode->hasData)
            {
                ret.push_back(it - s.begin() - startpos + 1);
            }
        }
    }
    return ret;
};


template <typename T>
vector<trieLengthValue<T> > trie<T>::lookupallLengthValue(const string& s, size_t startpos)
{

    vector<trieLengthValue<T> > ret;

    trieNode<T>* curNode = &(this->rootNode);

    for (string::const_iterator it = s.begin() + startpos; it != s.end(); ++it)
    {
        char c = tolower(*it);
        // ignore characters not in a-z
        if (islower(c))
        {
            int i = c - 'a';
            if (!curNode->child[i])
            {
                return ret;
            }
            curNode = curNode->child[i];
            if (curNode->hasData)
            {
                ret.push_back(make_trieLengthValue(it - s.begin() - startpos + 1, curNode->value));
            }
        }
    }
    return ret;
};


#endif // TRIE_H
