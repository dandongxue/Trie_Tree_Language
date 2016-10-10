#pragma once

#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

namespace trietree {

class CharUnit {
public:
    CharUnit(const string& value, const string& slot) { _value = value; _slot = slot; }
    CharUnit(const string& value) { _value = value; }
    const string& getValue() const { return _value; }
    const string& getSlot() const { return _slot; }
    set<CharUnit> * getNextSet() { return &_next; }
    bool operator < (const CharUnit & charUnit) const { return this->_value < charUnit.getValue(); }

private:
    string _value;
    string _slot;
    set<CharUnit> _next;
};

class TrieTree {
public:
    TrieTree() { _curSet = &_rootSet; }
    virtual void Add(const string& values, const string& slot) = 0;
    virtual pair<string, string> Translate(const string& sentence,string& secstr) = 0;

protected:
    set<CharUnit> * _insert(const CharUnit& charUnit);
    pair<set<CharUnit> *, string> _find(const CharUnit& charUnit);
    CharUnit * _cast2var(const set<CharUnit>::iterator& iter);

    set<CharUnit> _rootSet;
    set<CharUnit> * _curSet;
};

class SlotTree : public TrieTree {
public:
    void Add(const string& values, const string& slot);
    pair<string, string> Translate(const string& sentence, string &secstr);
};

class IntentTree : public TrieTree {
public:
    void Add(const string& value, const string& slot);
    pair<string, string> Translate(const string& sentence, string& secstr);
};

// Common string processing function
string trim(const string& str);
int split(const string& str, vector<string>& ret_, string sep = ",");

}
