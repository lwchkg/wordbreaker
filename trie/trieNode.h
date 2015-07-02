#ifndef TRIENODE_H
#define TRIENODE_H

template<typename T>
class trieNode
{
    public:
        /** Default constructor */
        trieNode();
        /** Constructor with data (set hasData to true) */
        explicit trieNode(T value);
        /** Default destructor */
        virtual ~trieNode();

        /** Members */
        trieNode<T>* child[26];
        bool hasData;
        T value;

    protected:
    private:
};

template<typename T>
trieNode<T>::trieNode () {
    for (int i = 0; i<26; ++i) {
        this->child[i] = NULL;
    }
    this->hasData = false;
};

template<typename T>
trieNode<T>::trieNode (T value) {
    // call constructor
    for (int i = 0; i<26; ++i) {
        this->child[i] = NULL;
    }
    this->hasData = true;
    this->value = value;
};

template<typename T>
trieNode<T>::~trieNode () {
    for (int i = 0; i<26; ++i) {
        if (this->child[i]) delete this->child[i];
    }
}

#endif // TRIE_H
