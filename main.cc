#include <iostream>
#include <set>
#include <utility>
#include <string>
#include "trie_set_tree.h"

using namespace std;
using namespace trietree;

int main(){
    TrieTree chs2slots;
    
    chs2slots.Add("abc", "english1");
    chs2slots.Add("def", "english2");
    chs2slots.Add("123", "number1");
    chs2slots.Add("456", "number2");
    chs2slots.Add("你说呢", "ask");
    chs2slots.Add("你好", "hi");
    chs2slots.Add("哈喽", "hi");
    chs2slots.Add("问你个问题", "ask");
    chs2slots.Add("小心我揍你", "threat");
    
    pair<string, string> ret = chs2slots.Translate("abc 456 def 你好 小心我揍你 哈喽 哈哈 你真棒 你 问个问题 问下 哦 ghawogh 157925192");
    cout << "Output chs2slots translate result: [ " << ret.first << " ]" << endl;
    cout << "Output chs2slots obtained slots: [ " << ret.second << " ]" << endl;

	return 0;
}
