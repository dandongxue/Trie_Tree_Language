#include "trie_set_tree.h"

namespace trietree {

void TrieTree::Add(const char * values, const string & slot)
{
    const char *ch = values;
    _curSet = &_rootSet;
    while (true)
    {
        if (!*(ch + 1))
            break;
        
        _curSet = _insert(CharUnit(*ch));
        ch++;
    }
    _insert(CharUnit(*ch, slot));
    _curSet = &_rootSet;
}


pair<string, string> TrieTree::Translate(const string sentence)
{
    _curSet = &_rootSet;
    const char *ch = sentence.data();
    string result = "";
    string slots = "";
    string last_values = "";
    string last_slot = "";
    
    while (*ch)
    {
        pair<set<CharUnit> *, string> piece_result = _find(CharUnit(*ch));
        set<CharUnit> * nextSet = piece_result.first;
        string curSlot = piece_result.second;
        
        if (NULL != nextSet) {
            last_values += *ch;
            if (!curSlot.empty())
                last_slot = curSlot;
            _curSet = nextSet;
        }
        else
        {
            _curSet = &_rootSet;
            if (!last_slot.empty()) {
                result += last_values + ':' + last_slot + " ";
                slots += last_slot + " ";
                last_values = "";
                last_slot = "";
                continue;
            }
        }
        ch++;
    }
    
    if (!last_slot.empty()) {
        result += last_values + ':' + last_slot;
        slots += last_slot;
    }
    
    return pair<string, string>(result, slots);
}

set<CharUnit> * TrieTree::_insert(const CharUnit & charUnit)
{
    CharUnit * temp = _cast2var(_curSet->insert(charUnit).first);
    return temp->getNextSet();
}

pair<set<CharUnit> *, string> TrieTree::_find(const CharUnit & charUnit)
{
    set<CharUnit>::iterator it;
    it = _curSet->find(charUnit);
    if (it == _curSet->end())
        return pair<set<CharUnit> *, string> (NULL, string());

    CharUnit * temp = _cast2var(it);
    return pair<set<CharUnit> *, string>(temp->getNextSet(), temp->getSlot());
}

CharUnit * TrieTree::_cast2var(const set<CharUnit>::iterator & iter)
{
    return const_cast<CharUnit *>(&(*iter));
}

}
