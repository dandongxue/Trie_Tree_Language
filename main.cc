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
//ofstream ofile("dan.txt");
SlotTree chs2slots;
IntentTree slots2Intent;

void convert_line_to_linux(string& str)
{
    int index = str.rfind('\r');
    if (index != string::npos)
        str.replace(index, 1, 1, '\0');
}

bool ReadSlotsRules(TrieTree* tree,const char* slotfilename, string splittype)
{
   ifstream infile(slotfilename);
   int num=1;
   if(!infile)
   {
     cout<<"Can not open file: "<<slotfilename<<endl;
     return false;
   }
   cout << "Start reading slots from : " << slotfilename << endl;
   for(;;num++)
   {
		string str,value,slot;
		getline(infile, str);
		if (str.empty())
			break;
			
    	convert_line_to_linux(str);
    	
        vector<string> splitans;
        split(str, splitans,splittype);
        if(splitans.size()<2)
        {
             cout<<"Format Error: " << "line " << num << " " <<  str <<endl;
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

void GetIntendsSlots(string strToTest)
{
    convert_line_to_linux(strToTest);
    string ans="",tempStr="";
    vector<string> vecTempSlots,vecIntends,vecSlots;
    queue<string> queSlots,queIntends;

    pair<string, string> ret = chs2slots.Translate(strToTest,strToTest);
    cout<<"Origin Str: [ "<<strToTest<<" ]"<<endl;
    split(ret.first, vecTempSlots," ");
    string secStr=GetSlotsWord(vecTempSlots,":");//Split words:slot
    pair<string, string> result = slots2Intent.Translate(ret.second,secStr);
    //cout<<" secStr == "<<secStr<<endl;
    split(secStr, vecSlots," ");
    for(int i=0;i<vecSlots.size();i++)
    {
        queSlots.push(vecSlots[i]);
    }
    //ofile<<result.first<<endl;
/*
    cout << "Output chs2slots translate result: [ " << ret.first << " ]" << endl;
    cout << "Output chs2slots obtained slots: [ " << ret.second << "]" << endl << endl;
    cout << "Output slots2Intent translate result: [ " << result.first << "]" << endl;
    cout << "Output slots2Intent obtained slots: [ " << result.second << "]" << endl;
*/
    split(result.first, vecIntends," ");
    for(int i=0;i<vecIntends.size();i++)
    {
        queIntends.push(vecIntends[i]);
    }
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
}
bool TestStr(const char *filename)
{
   ifstream infile(filename);
   int num=0;
   if(!infile)
   {
     cout<<"Can not open file: "<<filename<<endl;
     return false;
   }
   for(;!infile.eof();num++)
   {
       string str;
       getline(infile, str);
       convert_line_to_linux(str);
       cout<<"======================================================================="<<endl;
       GetIntendsSlots(str);
   }
   return true;
}
int main(){

    ReadSlotsRules(&chs2slots, "trie_set_tree/chs2slots.txt", "\t");
    ReadSlotsRules(&slots2Intent, "trie_set_tree/slots2intent.txt", " ");
    ReadSlotsRules(&chs2slots, "trie_set_tree/disease2slots.txt", "\t");
    ReadSlotsRules(&chs2slots, "trie_set_tree/medication2slots.txt", "\t");
    TestStr("trie_set_tree/demo.txt");
    cout<<"======================================================================="<<endl;
    string strToTest="abc def 你好小心我揍你哈喽 哈哈你真棒腰酸脚软五更！心似的！肺衰竭吗？怎么办";
    GetIntendsSlots(strToTest);
    cout<<"======================================================================="<<endl;
    GetIntendsSlots("腰酸脚软，五更泄泻，失眠多梦，手心脚心额头冐虚汗，舌干涩，怕冷");

	return 0;
}
