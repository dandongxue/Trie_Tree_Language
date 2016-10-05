#include <iostream>
#include <set>
#include <utility>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
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
        }
        tree->Add(splitans[i],splitans[i+1]);
	}
    return num;
}

string GetSlotsWord(const vector<string >vecTempSlots,string splittype)
{
    string secStr="";
    for(int i=0;i<vecTempSlots.size();i++)
    {
        vector<string> temp;
        split(vecTempSlots[i], temp,splittype);
        secStr+=temp[0]+" ";
    }
    return secStr;
}

int main(){
    SlotTree chs2slots;
    IntentTree slots2Intent;
    ReadSlotsRules(&chs2slots, "chs2slots.txt", "\t");
    ReadSlotsRules(&slots2Intent, "slots2intent.txt", " ");
    string strToTest="abc def 你好小心我揍你哈喽 哈哈你真棒腰酸脚软五更！心似的！肺衰竭吗？怎么办";

    pair<string, string> ret = chs2slots.Translate(strToTest,strToTest);
    cout<<"Before: [ "<<strToTest<<" ]"<<endl;
    cout << "Output chs2slots translate result: [ " << ret.first << " ]" << endl;

    vector<string> vecTempSlots,vecIntends;
    queue<string> queSlots,queIntends;
    split(ret.first, vecTempSlots," ");
    string secStr=GetSlotsWord(vecTempSlots,":");
    pair<string, string> result = slots2Intent.Translate(ret.second,secStr);
    //cout<<"== "<<secStr<<endl;
    vector<string> vecSlots;
    split(secStr, vecSlots," ");
    for(int i=0;i<vecSlots.size();i++)
    {
        queSlots.push(vecSlots[i]);
    }
    ofile<<result.first<<endl;
    cout<<"======================================================================="<<endl;
    split(result.first, vecIntends," ");
    for(int i=0;i<vecIntends.size();i++)
    {
        queIntends.push(vecIntends[i]);
    }
    string ans="",tempStr="";
    while(!queIntends.empty())
    {
        tempStr = queIntends.front();
        if(tempStr.length()>1 && tempStr[1] == ':')
        {
            tempStr += " "+ans;
            cout<<"Show Ans [ "<<tempStr<<+" ]"<<endl;
            ans = "";
        }
        else
        {
            ans += queSlots.front()+" ";
            //cout<<queSlots.front()<<endl;
            queSlots.pop();
        }
           queIntends.pop();
    }

   // cout << "Output chs2slots obtained slots: [ " << ret.second << "]" << endl << endl;
   // cout << "Output slots2Intent translate result: [ " << result.first << "]" << endl;
   // cout << "Output slots2Intent obtained slots: [ " << result.second << "]" << endl;
	return 0;
}
