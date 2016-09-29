#pragma once

#include <iostream>
#include <set>
#include <string>
#include <utility>

using namespace std;

namespace trietree {

class CharUnit {
public:
    CharUnit(char value, string slot) { _value = value; _slot = slot; }
    CharUnit(char value) { _value = value; }
    char getValue() const { return _value; }
    string getSlot() { return _slot; }
    set<CharUnit> * getNextSet() { return &_next; }
    bool operator < (const CharUnit & charUnit) const { return this->_value < charUnit.getValue(); }
    
private:
    char _value;
    string _slot;
    set<CharUnit> _next;
};

class TrieTree {
public:
    void Add(const char * values, const string & slot);
    pair<string, string> Translate(const string sentence);
    
private:
    set<CharUnit> * _insert(const CharUnit & charUnit);
    pair<set<CharUnit> *, string> _find(const CharUnit & charUnit);
    CharUnit * _cast2var(const set<CharUnit>::iterator & iter);
    
    set<CharUnit> _rootSet;
    set<CharUnit> * _curSet;
};

}
