import time
import urllib.request
import random
from matParser import searchParser,resultParser

startPoint=1 #页码开始
nop = 2069 #页码结束


if __name__ == '__main__':
    log = open("./log.txt", 'a',encoding="utf-8") #存储log
    index = open("./output/index.txt",'a', encoding="utf-8")#存储文件名至内容的映射
    #读取第一页
    # url = "https://materials.springer.com/search?searchTerm=Phase+Diagram&pageNumber=1&autoRedirectTextSearch=false&datasourceFacet=sm_isp&substanceId="
    header = {'User-Agent': 'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.96 Safari/537.36'}
    # req = urllib.request.Request(url,None,header)
    # response = urllib.request.urlopen(req)
    # content = response.read().decode('utf-8')
    #print(content)

    for i in range(startPoint,nop+1):
        #读取其它页
        url = "https://materials.springer.com/search?searchTerm=Phase+Diagram&pageNumber="+str(i)+"&autoRedirectTextSearch=false&datasourceFacet=sm_isp&substanceId="
        req = urllib.request.Request(url, None, header)
        response = urllib.request.urlopen(req)
        content = response.read().decode('utf-8')
        print("opened page " + str(i))
        log.write("opened page " + str(i))
        sParser = searchParser()
        sParser.feed(content)
        time.sleep(random.uniform(5, 10))
        print("get " + str(sParser.numOfResult) + " results.")
        log.write("get "+str(sParser.numOfResult)+" results.\n")
        print(sParser.result)
        count=0 #每页第几个任务
        for desc in sParser.result:
            count += 1
            print(desc + " is started")
            url2="https://materials.springer.com"+sParser.result[desc]
            req2 = urllib.request.Request(url2, None, header)
            response2 = urllib.request.urlopen(req2)
            content2 = response2.read().decode('utf-8')
            rParser = resultParser()
            rParser.feed(content2)
            filename = str(i).zfill(4) + str(count).zfill(2)
            urllib.request.urlretrieve(rParser.link, "./output/"+filename+".png")
            print(index.write("\""+filename+"\""+",\""+desc+"\"\n"))
            time.sleep(random.uniform(10,20))
            print("finished page " + str(i) + " task " +filename + ":" + desc)
            log.write("finished page " + str(i) + " task " +filename + ":" + desc+'\n')
            log.flush()
            index.flush()

        print("finished page" + str(i) + ", downloaded " + str(count) + " pngs in total now")
        log.write("finished page" + str(i) + ", downloaded " + str(count) + " pngs in total now"+'\n')
        time.sleep(300)
