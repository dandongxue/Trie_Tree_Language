# SimpleClassify  

 该Demo主要是基于字典树数据结构（见下图），工程中共建立两棵树：Slot树和Intent树  
 1.Slot树：存储完每个slot字符串（例如：感冒）后，在最后一个节点的位置指明对应的slot名字，例如： :disease  
 2.Intent树：则是在存储完每一个对应规则顺序之后（例如： :body :feel），在最后一个节点位置指明对应的intent名字，例如： ::Symptom  
 从文件读入并存储这些规则之后，对输入的待检测文本进行搜索匹配即可。  
   
 工程共三个文件：  
 1.main.cc :主文件  
 2.trie_set_tree.cc :类的实现文件  
 3.trie_set_tree.h :类的头文件  
 4.规则文件在rules目录下（ .slot 与 .intent 文件均为文本文件，后缀用于区分）

   - xxx.slot 文件用作Slot字典树的输入数据，用以构建整棵Slot树。
   - xxx.intent 同理，用以构建整棵Intent树。

 5.demo.txt中是演示所用输入数据。  
 
 试用举例：
 1.打开工程下的demo.txt文件，里面存放了待检测的文本数据，可以自由添加
 2.可以根据需要添加或修改rules文件夹下.slot文件和.intent文件,进行规则的添加和改动
 3.编译运行，即可再output.txt中看到输出内容
 
 举个例子：
 example.slot
	line 1: 胃	:body
	line 2: 疼	:feel
	line 3: 三九胃泰	:medicine
	
 example.intent
	line 1: :body	:feel	::Symptom
	line 2:	:medicine	::Take
 
 Input plain text:
	我的胃好疼，该吃些什么药，三九胃泰能立即止疼吗？

 Slot classification result:
	胃:body 疼:feel 三九胃泰:medicine 疼:feel
	
 Intent classification result:
	::Symptom ::Take
	
 Output:
	::Symptom 胃:body 疼:feel ::Take 三九胃泰:medicine
 
 ![trie set tree](image/trie_set_tree.png)  
