#include <iostream>
#include <set>
#include <utility>
#include <string>
#include <fstream>
#include <sstream>
#include "trie_set_tree.h"

using namespace std;
using namespace trietree;
ofstream ofile("dan.txt");
bool ReadSlotsRules(TrieTree* tree,const char* slotfilename, string splittype)
{
   ifstream infile(slotfilename);
   int num=0;
   if(!infile)
   {
     cout<<"Can not open file: "<<slotfilename<<endl;
     return false;
   }
   for(;!infile.eof();num++)
   {
		string str,value,slot;
		getline(infile, str);
        vector<string> splitans;
        split(str, splitans,splittype);
        if(splitans.size()<2)
        {
             cout<<" File format wrong!"<<endl;
             continue;
        }
        unsigned int i;
        for(i=0;i<splitans.size() - 2;i++)
        {
          tree->Add(splitans[i], string());
          //cout<<splitans[i]<<endl;
        }
		//istringstream istr(str);
        //istr>>value;
        //istr>>slot;
        tree->Add(splitans[i],splitans[i+1]);
	}
    return num;
}

int main(){
    SlotTree chs2slots;
    IntentTree slots2Intent;

    ReadSlotsRules(&chs2slots, "chs2slots.txt", "\t");
    ReadSlotsRules(&slots2Intent, "slots2intent.txt", " ");

    pair<string, string> ret = chs2slots.Translate("abc def ��� С���������� ���������789789����������йк������ʱ���������⼸�������Ļţ�˵���������Ƶģ��Ƿ�˥������ô��");
    pair<string, string> result = slots2Intent.Translate(ret.second);
    ofile<<result.first<<endl;
    cout << "Output chs2slots translate result: [ " << ret.first << " ]" << endl;
    cout << "Output chs2slots obtained slots: [ " << ret.second << " ]" << endl << endl;
    cout << "Output chs2slots translate result: [ " << result.first << " ]" << endl;
    cout << "Output chs2slots obtained slots: [ " << result.second << " ]" << endl;

	return 0;
}
