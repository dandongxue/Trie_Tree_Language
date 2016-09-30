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
        int i;
        for(i=0;i<splitans.size() - 2;i++)
        {
          tree->Add(splitans[i], string());
        }
		//istringstream istr(str);
        //istr>>value;
        //istr>>slot;
        tree->Add(splitans[i],splitans[i+1]);
	}
    return num;
}

int main(){
    TrieTree chs2slots;
    TrieTree slotsIntend;

    ReadSlotsRules(&chs2slots, "chs2slots.txt", "\t");
    ReadSlotsRules(&slotsIntend, "slots2intend.txt", " ");

    cout<<"脚丫子"<< sizeof("脚")<< endl;
    pair<string, string> ret = chs2slots.Translate("abc def 你好小心我揍你哈喽 哈哈你真棒789789腰酸脚软五更泄泻！过年时检查出来的这几天总是心慌！说够不着心似的！是肺衰竭吗？怎么办");
    pair<string, string> result = slotsIntend.Translate(ret.second);
    ofile<<result.first<<endl;
    cout << "Output chs2slots translate result: [ " << result.first << " ]" << endl;
    cout << "Output chs2slots obtained slots: [ " << result.second << " ]" << endl;

	return 0;
}
