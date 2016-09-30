#include <iostream>
#include <set>
#include <utility>
#include <string>
#include "trie_set_tree.h"

using namespace std;
using namespace trietree;

int main(){
    TrieTree chs2slots;

    //chs2slots.Add("abc", "english1");
    //chs2slots.Add("def", "english2");
    //chs2slots.Add("123", "number1");
    //chs2slots.Add("456", "number2");
    chs2slots.Add("智齿", "body");
    chs2slots.Add("腰", "body");
    chs2slots.Add("腿", "body");
    chs2slots.Add("脚", "body");
    chs2slots.Add("软", "feel");
    chs2slots.Add("酸", "feel");
    chs2slots.Add("疼", "feel");
    chs2slots.Add("痛", "feel");
    chs2slots.Add("哈喽", "hi");
    chs2slots.Add("问你个问题", "ask");
    chs2slots.Add("小心我揍你", "threat");

    //pair<string, string> ret = chs2slots.Translate("abc 456 def 你好小心我揍你哈喽 哈哈你真棒789789腰酸脚软五更泄泻失眠多梦手心脚心额头冐虚汗舌干涩怕冷");
    pair<string, string> ret = chs2slots.Translate("心脚");
    cout << "Output chs2slots translate result: [ " << ret.first << " ]" << endl;
    cout << "Output chs2slots obtained slots: [ " << ret.second << " ]" << endl;

	return 0;
}
