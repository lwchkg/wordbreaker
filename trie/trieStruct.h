#include <string>

using namespace std;

template <typename T>
struct trieKeyValue
{
    string key;
    T value;

    trieKeyValue(string key, T value) : key(key), value(value) {};
};

template <typename T>
inline trieKeyValue<T> make_trieKeyValue(string key, T value)
{
    return (trieKeyValue<T>(key, value));
};


template <typename T>
struct trieLengthValue
{
    size_t length;
    T value;

    trieLengthValue(size_t length, T value) : length(length), value(value) {};
};

template <typename T>
inline trieLengthValue<T> make_trieLengthValue(size_t length, T value)
{
    return (trieLengthValue<T>(length, value));
};
