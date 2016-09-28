#include<iostream>
using namespace std;
struct tirenode{
				struct tirenode *next[2];//只有01两种情况所以就设置了两个子节点
				bool isStr;
				};
char str[20];
bool flag;
tirenode* newnode()
{
   tirenode *temp=new tirenode;
   for(int m=0;m<2;m++)
        temp->next[m]=NULL;
   temp->isStr=false;//标记位记录二叉树到这个节点是否构成了一个字符串，搜索是否需要终止
   return temp;
}
bool Search(tirenode *p,char *ch)
{
   bool Fla=false;
   int id;
   while(*ch)
   {
    id=*ch-'0';
    if(p->isStr==true)
    {
     //cout<<"find it"<<endl;
      break;
    }
    if(p->next[id]==NULL)
    {
      Fla=true;//true ,not findit;
        break;
    }
    else p=p->next[id];
       ch++;
   }
return Fla;
}
void Insert(tirenode *p,char *ch)
{
   int id;
   while(*ch)
   {
    id=*ch-'0';
    if(p->next[id]==NULL)
    p->next[id]=newnode();
    p=p->next[id];
    ch++;
   }
   p->isStr=true;
}
void Del(tirenode *p)
{
  int i;
  for(i=0;i<2;i++)
  {
    if(p->next[i]!=NULL)
       Del(p->next[i]);
  }
free(p);
}
int main(){
	int count=1;
	tirenode *root=newnode();
	flag=true;
	while(scanf("%s",str)!=EOF)
	{
	   if(str[0]=='9')
	   {
			if(flag)
			   printf("Set %d is immediately decodable\n",count++);
			else
			   printf("Set %d is not immediately decodable\n",count++);
			Del(root);
			tirenode *root=newnode();
			flag=true;
			continue;
		   // break;
	   }
	   else if(flag)
	   {
		 if(Search(root,str))
			Insert(root,str);
		 else
			 flag=false;//fing bug;
	   }
	}
	return 0;
}
