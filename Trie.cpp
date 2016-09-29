#include<iostream>
#include <set>
using namespace std;
struct TrieNode{
                set<struct TrieNode> tnode_set;
                bool isStr;
                int tnode_value;
                int tnode_type;
				};
bool operator<(const TrieNode & lhs, const TrieNode & rhs)//over load operator '<' for set
{
    return lhs.tnode_value<rhs.tnode_value;
}
TrieNode& CreateNode()
{
   static TrieNode temp;
   temp.tnode_type=-1;
   temp.tnode_value=0;
   temp.isStr=false;
   return temp;
}
TrieNode& CreateNode(int tnode_value)
{
   static TrieNode temp;
   temp.tnode_type=-1;
   temp.tnode_value=tnode_value;
   temp.isStr=false;
   return temp;
}

bool FindFromCurNode(TrieNode *p,int id,TrieNode *&tnode)
{
   set<struct TrieNode>::iterator iter;
   for(iter=p->tnode_set.begin();iter!=p->tnode_set.end();iter++)
   {
       if((*iter).tnode_value == id)
           {
               tnode=const_cast<struct TrieNode *>(&(*iter));
               return true;
           }
   }
    return false;
}
bool SearchNode(TrieNode &temp,char *ch)
{
   bool Flag = false;
   int id;
   TrieNode *pTemp;
   TrieNode* p=&temp;
   while(*ch)
   {
    id=*ch;
    /*if(p->isStr == true)
    {
      cout<<"find it "<<endl;
      break;
    }*/
    if(!FindFromCurNode(p,id,pTemp))
    {
      cout<<"not find it:"<<(char)id<<endl;
      break;
    }
    else
    {
        p=pTemp;
        cout<<"search:"<<(char)p->tnode_value<<endl;

    }
       ch++;
   }
return Flag;
}

void InsertNode(TrieNode &temp,char *ch)
{
   int id;
   set<struct TrieNode>::iterator iter;
  TrieNode *p=&temp;
   TrieNode *tnode,tde;
   while(*ch)
   {
        id=*ch;
        if(!FindFromCurNode(p,id,tnode))
        {
            tde = CreateNode(id);
            (p->tnode_set).insert(tde);
            iter=(p->tnode_set).find(tde);
            p = const_cast<struct TrieNode *>(&(*iter));
            cout<<"InsertNode "<<*ch<<endl;
           //Find it exit node
        }
        else
            p = tnode;
        ch++;
   }
   p->isStr=true;
}
void DisplayTree(const TrieNode *p,unsigned int curlevel) //Print the tree on the screen
{
    //if(curlevel!=0)cout<<curlevel;
    for(int i=0;i<curlevel;i++)
        cout<<"-";
    cout <<(char)p->tnode_value << " "<<endl;
    set<struct TrieNode>::iterator iter;
    for(iter=p->tnode_set.begin();iter!=p->tnode_set.end();iter++)
    {
        DisplayTree(&(*iter),curlevel+1);
    }

}
int main(){
	int count=1;
	TrieNode root=CreateNode();
	InsertNode(root,"xdfdktt");
	InsertNode(root,"xdfduyy");
	InsertNode(root,"zbty");
	InsertNode(root,"yjty");
	cout<<"================="<<endl;
    cout<<SearchNode(root,"xktu")<<endl;
    DisplayTree(&root,0);
	bool flag=true;
	return 0;
}
