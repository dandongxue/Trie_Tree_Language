#coding:utf8
import urllib
import urllib2,Queue
import sys,re
reload(sys)
sys.setdefaultencoding('utf-8')
__author__ = 'gensound'
ansFile=file("dan.txt",'w')
for i in range(1,100):
    print "Cur Page: " +str(i)
    urlAddress=r'http://club.xywy.com/list_all_'+str(i)+'.htm'
    user_agent = 'Mozilla/4.0 (compatible; MSIE 5.5; Windows NT)'
    headers = { 'User-Agent' : user_agent }
    request=urllib2.Request(urlAddress,headers=headers)
    response=urllib2.urlopen(request)
    content=response.read()
    pattern=re.compile(r'</a>]<a target="_blank" href="(.*?)" title=.*? class="btn-a hov_clor">')
    items=re.findall(pattern,content)
    que=Queue.Queue()
    for item in items:
        #print item
        que.put(item)
        request=urllib2.Request(item,headers=headers)
        response=urllib2.urlopen(request)
        content=response.read().decode('gbk')
        content=str(content).replace('\n','')
        pattern=re.compile(r'<h5>.*?</h5>(.*?)</div>|<div class="graydeep User_quecol pt10 mt10" id="qdetailc">(.*?)</div>')
        Items=re.findall(pattern,content)
        for it in Items:
            #print it
            (it1, it2) = it
            findStr = '</h5>'
            idx = it2.find(findStr)
            if (idx > 0):
                idx += len(findStr)
            else:
                idx = 0
            print str(it2[idx:]).strip()
    print "==========================================================================================================="
