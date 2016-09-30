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
    chs2slots.Add("�ǳ�", "body");
    chs2slots.Add("��", "body");
    chs2slots.Add("��", "body");
    chs2slots.Add("��", "body");
    chs2slots.Add("��", "feel");
    chs2slots.Add("��", "feel");
    chs2slots.Add("��", "feel");
    chs2slots.Add("ʹ", "feel");
    chs2slots.Add("���", "hi");
    chs2slots.Add("���������", "ask");
    chs2slots.Add("С��������", "threat");

    //pair<string, string> ret = chs2slots.Translate("abc 456 def ���С���������� ���������789789����������йкʧ�߶������Ľ��Ķ�ͷ���麹���ɬ����");
    pair<string, string> ret = chs2slots.Translate("�Ľ�");
    cout << "Output chs2slots translate result: [ " << ret.first << " ]" << endl;
    cout << "Output chs2slots obtained slots: [ " << ret.second << " ]" << endl;

	return 0;
}
