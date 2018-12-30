import cv2
import os
import time

import numpy as np
list = os.listdir("./diagrams")
imgs=[]
datanum=len(list)

sumOfPngs=0
for i in range(datanum):
    if(list[i].find(".png")!=-1):
        sumOfPngs+=1
datanum=sumOfPngs
print("we have "+str(sumOfPngs) + " pictures")

print("start at"+str(time.time()))
for i in range(datanum):
    path=os.path.join("./diagrams",list[i])
    path= os.path.abspath(path)
    #print(path)
    if(os.path.isfile(path)) and path.find(".png")!=-1:
        img = cv2.imread(path)
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        imgs.append(np.mat(gray)[70:1001,188:1437])#for binary

mat=np.zeros((datanum,datanum))
starttime=time.time()
for m in range(datanum):#-1 stand for the index.txt
    print(str(m) + "started")
    # rotate imgs[m]
    mR = imgs[m].copy()

    col = mR.shape[1]
    for i in range(mR.shape[0]):
        for j in range(col // 2):
            mR[i,j], mR[i,col - 1 - j] =  mR[i,col - 1 - j],mR[i,j]
    for n in range(datanum):#please DON'T store other files in ./diagrams folder
        dist=0
        d1=np.sum(imgs[m]-imgs[n])
        d2=np.sum(mR-imgs[n])
        min=0
        if d1<=d2:
            min=d1
        else:
            min=d2

        mat[m,n]=min
    print(str(m) + "finished, about"+str((time.time()-starttime)/(m+1)*(datanum-m-1))+" sec. left")
    if m%100==0:
        np.savetxt("./distMat.csv",mat[0:m,0:m], delimiter=',')
print(mat)
np.savetxt("./distMat.csv",mat[0:m,0:m], delimiter=',')