#pragma once

#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

namespace trietree {

class CharUnit {
public:
    CharUnit(string value, string slot) { _value = value; _slot = slot; }
    CharUnit(string value) { _value = value; }
    string getValue() const { return _value; }
    string getSlot() { return _slot; }
    set<CharUnit> * getNextSet() { return &_next; }
    bool operator < (const CharUnit & charUnit) const { return this->_value < charUnit.getValue(); }

private:
    string _value;
    string _slot;
    set<CharUnit> _next;
};

class TrieTree {
public:
    virtual void Add(const string values, const string & slot) = 0;
    virtual pair<string, string> Translate(const string sentence) = 0;

private:
    set<CharUnit> * _insert(const CharUnit & charUnit);
    pair<set<CharUnit> *, string> _find(const CharUnit & charUnit);
    CharUnit * _cast2var(const set<CharUnit>::iterator & iter);

    set<CharUnit> _rootSet;
    set<CharUnit> * _curSet;
};

class SlotTree : public TrieTree {
public:
    void Add(const string values, const string & slot);
    pair<string, string> Translate(const string sentence);
};

class IntentTree : public TrieTree {
public:
    void Add(const string values, const string & slot);
    pair<string, string> Translate(const string sentence);
};

// Common string processing function
string trim(const string& str);
int split(const string& str, vector<string>& ret_, string sep = ",");

}
