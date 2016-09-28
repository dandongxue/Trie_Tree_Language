#include<iostream>
#include <set>
using namespace std;
struct tirenode{
                set<struct tirenode> tnode_set;
                bool isStr;
                int value;
                int type;
				};
bool operator<(const tirenode & lhs, const tirenode & rhs)
{
    return lhs.value<rhs.value;
}
tirenode& newnode()
{
   static tirenode temp;
   temp.type=-1;
   temp.value=0;
   temp.isStr=false;//标记位记录二叉树到这个节点是否构成了一个字符串，搜索是否需要终止
   return temp;
}
tirenode& newnode(int value)
{
   static tirenode temp;
   temp.type=-1;
   temp.value=value;
   temp.isStr=false;//标记位记录二叉树到这个节点是否构成了一个字符串，搜索是否需要终止
   return temp;
}

bool FindFromCurNode(tirenode *p,int id,tirenode *&tnode)
{
   set<struct tirenode>::iterator iter;
   for(iter=p->tnode_set.begin();iter!=p->tnode_set.end();iter++)
   {
       if((*iter).value == id)
           {
               tnode=const_cast<struct tirenode *>(&(*iter));
               return true;
           }
   }
    return false;
}
bool Search(tirenode &temp,char *ch)
{
   bool Flag = false;
   int id;
   tirenode *pTemp;
   tirenode* p=&temp;
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
        cout<<"search:"<<(char)p->value<<endl;

    }
       ch++;
   }
return Flag;
}

void Insert(tirenode &temp,char *ch)
{
   int id;
   set<struct tirenode>::iterator iter;
  tirenode *p=&temp;
   tirenode *tnode,tde;
   while(*ch)
   {
        id=*ch;
        if(!FindFromCurNode(p,id,tnode))
        {
            tde = newnode(id);
            (p->tnode_set).insert(tde);
            iter=(p->tnode_set).find(tde);
            p = const_cast<struct tirenode *>(&(*iter));
            cout<<"Insert "<<*ch<<endl;
           //Find it exit node
        }
        else
            p = tnode;
        ch++;
   }
   p->isStr=true;
}

/*
void Del(tirenode *p)
{
  int i;
  for(i=0;i<2;i++)
  {
    if(p->next[i]!=NULL)
       Del(p->next[i]);
  }
free(p);
}*/
int main(){
	int count=1;
	tirenode root=newnode();
	Insert(root,"xkt");
	Insert(root,"xkty");
	cout<<"================="<<endl;
    cout<<Search(root,"xktu")<<endl;
	bool flag=true;
	return 0;
}
