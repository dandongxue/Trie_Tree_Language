#include "trie_set_tree.h"

namespace trietree {

string trim(const string& str)
{
    string::size_type pos = str.find_first_not_of(' ');
    if (pos == string::npos)
    {
        return str;
    }
    string::size_type pos2 = str.find_last_not_of(' ');
    if (pos2 != string::npos)
    {
        return str.substr(pos, pos2 - pos + 1);
    }
    return str.substr(pos);
}

int split(const string& str, vector<string>& ret_, string sep)
{
    if (str.empty())
    {
        return 0;
    }

    string tmp;
    string::size_type pos_begin = str.find_first_not_of(sep);
    string::size_type comma_pos = 0;

    while (pos_begin != string::npos)
    {
        comma_pos = str.find(sep, pos_begin);
        if (comma_pos != string::npos)
        {
            tmp = str.substr(pos_begin, comma_pos - pos_begin);
            pos_begin = comma_pos + sep.length();
        }
        else
        {
            tmp = str.substr(pos_begin);
            pos_begin = comma_pos;
        }

        if (!tmp.empty())
        {
            ret_.push_back(tmp);
            tmp.clear();
        }
    }
    return 0;
}

// TrieTree implement begin

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

// TrieTree implement end

// SlotTree implement begin

void SlotTree::Add(const string values, const string & slot)
{
    const char *ch = values.data();
    string tempStr;
    _curSet = &_rootSet;
    while (true)
    {
        tempStr = *ch;
        if (!*(ch + 1))
            break;

        _curSet = _insert(CharUnit(tempStr));
        ch++;
    }
    _insert(CharUnit(tempStr, slot));
    _curSet = &_rootSet;
}


pair<string, string> SlotTree::Translate(const string sentence,string &secStr)
{
    _curSet = &_rootSet;
    const char *ch = sentence.data();
    const char *memory_point = ch + 1;
    string tempStr;
    string result = "";
    string slots = "";
    string last_values = "";
    string last_slot = "";
    string last_result = "";
    

    while (*ch)
    {
        tempStr = *ch;
        pair<set<CharUnit> *, string> piece_result = _find(CharUnit(tempStr));
        set<CharUnit> * nextSet = piece_result.first;
        string curSlot = piece_result.second;

        if (NULL != nextSet) {
            last_values += tempStr;
            if (!curSlot.empty()) {
            	last_slot = curSlot;
            	last_result = last_values + last_slot + " ";
            	memory_point = ch + 1;    
            }
            _curSet = nextSet;
        }
        else
        {
            _curSet = &_rootSet;
            if (!last_slot.empty()) {
                result += last_result;
                slots += last_slot + " ";
                last_values = "";
                last_slot = "";
                ch = memory_point;
                continue;
            }
            else{
                if (!last_values.empty()) {
                    last_values = "";
                    last_slot = "";
                    ch = memory_point++;
                    continue;
                }
                else {
                	last_values = "";
                	last_slot = "";
                	memory_point++;
               	}
            }
        }
        ch++;
    }

    if (!last_slot.empty()) {
        result += last_values + last_slot;
        slots += last_slot;
    }

    return pair<string, string>(trim(result), trim(slots));
}

// SlotTree implement end

// IntentTree implement begin

void IntentTree::Add(const string value, const string & slot)
{
    if (slot.empty()) {
        _curSet = _insert(CharUnit(value));
        //cout << "Insert(" << value << ")" << endl;
    }
    else {
        _insert(CharUnit(value, slot));
        _curSet = &_rootSet;
        //cout << "Insert(" << value << ", " << slot << ")" << endl;
    }
}

pair<string, string> IntentTree::Translate(const string sentence,string &secstr)
{
    _curSet = &_rootSet;
    vector<string> strPieces;
    vector<string> vecSecStr;
    string tempStr,tempSec;
    string result = "";
    string slots = "";
    string last_values = "",last_sec="";
    string last_slot = "";
    string last_result = "";
    split(sentence, strPieces, " ");
    split(secstr, vecSecStr, " ");
    secstr="";
    
    unsigned int idx = 0;
    unsigned int memory_idx = idx + 1;
    while (idx < strPieces.size()) {
        tempStr = strPieces[idx];
        tempSec=vecSecStr[idx];
        pair<set<CharUnit> *, string> piece_result = _find(CharUnit(tempStr));
        set<CharUnit> * nextSet = piece_result.first;
        string curSlot = piece_result.second;

        if (NULL != nextSet) {
            last_values += tempStr + " ";
            last_sec+=tempSec+tempStr+" ";
            if (!curSlot.empty()) {
                last_slot = curSlot;
                last_result = last_values + last_slot + " ";
                memory_idx = idx + 1;
            }
            _curSet = nextSet;
        }
        else
        {
            _curSet = &_rootSet;
            if (!last_slot.empty()) {
                result += last_result;
                slots  += last_slot + " ";
                secstr += last_sec + " ";
                last_values = "";
                last_sec="";
                last_slot = "";
                last_result = "";
                idx = memory_idx;
                continue;
            }
            else{
                if (!last_values.empty()) {
                    last_values = "";
                    last_slot = "";
                    last_sec="";
                    idx = memory_idx++;
                    continue;
                }
                else {
                	last_values = "";
                	last_slot = "";
                	last_sec="";
                	memory_idx++;
				}
            }
        }
        idx++;
    }

    if (!last_slot.empty()) {
        result += last_values + last_slot;
        secstr += last_sec;
        slots += last_slot;
    }

    return pair<string, string>(trim(result), trim(slots));
}

// IntentTree implement end

}
