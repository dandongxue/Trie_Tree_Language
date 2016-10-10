#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include "trie_set_tree.h"

using namespace std;
using namespace trietree;

ofstream ofile("output.txt");
SlotTree chs2slots;
IntentTree slots2Intent;

void ConvertLine2UnixFmt(string& str)
{
    int index = str.rfind('\r');
    if (index != string::npos)
        str.erase(index);
}

bool ReadSlotsRules(TrieTree* tree,const char* slotfilename, string splittype = "\t")//Read rules from files
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
			
    	ConvertLine2UnixFmt(str);
    	
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

void GetIntendsSlots(string strToTest)//Input sentence and get results
{
    ConvertLine2UnixFmt(strToTest);
    string ans="",tempStr="";
    vector<string> vecTempSlots,vecIntends,vecSlots;
    queue<string> queSlots,queIntends;

    pair<string, string> ret = chs2slots.Translate(strToTest, strToTest);
    cout<<"Original Str: [ "<<strToTest<<" ]"<<endl;
    ofile<<"Original Str: [ "<<strToTest<<" ]"<<endl;
    split(ret.first, vecTempSlots," ");
    string secStr=GetSlotsWord(vecTempSlots,":");//Split words:slot
    pair<string, string> result = slots2Intent.Translate(ret.second,secStr);
    split(secStr, vecSlots," ");
    for(int i=0;i<vecSlots.size();i++)
    {
        queSlots.push(vecSlots[i]);
    }
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
	    	ofile<<"Ans [" <<tempStr<<" ]"<<endl;
            cout<<"Ans [ "<<tempStr<<+" ]"<<endl;
            ans = "";
        }
        else
        {
            ans += queSlots.front()+" ";
            queSlots.pop();
        }
           queIntends.pop();
    }
}
bool TestStrFrmFiles(const char *filename)// Read Files And Test The Functions
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
       if (str.empty())
           break;
           
       ConvertLine2UnixFmt(str);
       ofile << "======================================================================="<<endl;
       cout << "======================================================================="<<endl;
       GetIntendsSlots(str);
   }
   return true;
}
int main(){
	// Read slots and intents rules from files
    ReadSlotsRules(&chs2slots, "rules/chs.slot");
    ReadSlotsRules(&chs2slots, "rules/disease.slot");
    ReadSlotsRules(&chs2slots, "rules/medication.slot");
    ReadSlotsRules(&slots2Intent, "rules/all.intent");
    
    // Test files
    TestStrFrmFiles("demo.txt");

	return 0;
}
