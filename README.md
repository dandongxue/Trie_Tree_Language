# SimpleClassify  

 ��Demo��Ҫ�ǻ����ֵ������ݽṹ������ͼ���������й�������������Slot����Intent��  
 1.Slot�����洢��ÿ��slot�ַ��������磺��ð���������һ���ڵ��λ��ָ����Ӧ��slot���֣����磺 :disease  
 2.Intent���������ڴ洢��ÿһ����Ӧ����˳��֮�����磺 :body :feel���������һ���ڵ�λ��ָ����Ӧ��intent���֣����磺 ::Symptom  
 ���ļ����벢�洢��Щ����֮�󣬶�����Ĵ�����ı���������ƥ�伴�ɡ�  
   
 ���̹������ļ���  
 1.main.cc :���ļ�  
 2.trie_set_tree.cc :���ʵ���ļ�  
 3.trie_set_tree.h :���ͷ�ļ�  
 4.�����ļ���rulesĿ¼�£� .slot �� .intent �ļ���Ϊ�ı��ļ�����׺�������֣�

   - xxx.slot �ļ�����Slot�ֵ������������ݣ����Թ�������Slot����
   - xxx.intent ͬ�����Թ�������Intent����

 5.demo.txt������ʾ�����������ݡ�  
 
 ���þ�����
 1.�򿪹����µ�demo.txt�ļ����������˴������ı����ݣ������������
 2.���Ը�����Ҫ��ӻ��޸�rules�ļ�����.slot�ļ���.intent�ļ�,���й������Ӻ͸Ķ�
 3.�������У�������output.txt�п����������
 
 �ٸ����ӣ�
 example.slot
	line 1: θ	:body
	line 2: ��	:feel
	line 3: ����θ̩	:medicine
	
 example.intent
	line 1: :body	:feel	::Symptom
	line 2:	:medicine	::Take
 
 Input plain text:
	�ҵ�θ���ۣ��ó�Щʲôҩ������θ̩������ֹ����

 Slot classification result:
	θ:body ��:feel ����θ̩:medicine ��:feel
	
 Intent classification result:
	::Symptom ::Take
	
 Output:
	::Symptom θ:body ��:feel ::Take ����θ̩:medicine
 
 ![trie set tree](image/trie_set_tree.png)  
