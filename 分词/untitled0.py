
#处理文档获得字典
#去掉多余字符
def string_process(x):    #处理字符串
    a=re.sub(r'\d{8}-\d{2}-\d{3}-\d{3}/m|[/a-z！。”“，、——\[\]（）：《》……A-Z？]', "", x)
#前面时间的正则表达式,后面部分删掉字母和其他符号
    b=a.replace("  "," ")
    return b.rstrip()

#处理得到字典
def file_process():
    s=""
    with open('词性标注@人民日报199801.txt','r',encoding='UTF-8') as f:
        for line1 in f:
            a=string_process(line1)
            a=string_process(a)
            s+=a+"\n"
    f.close()
    with open("process_1.txt",'w',encoding='UTF-8') as w:
        w.write(s)
 
    w.close()

