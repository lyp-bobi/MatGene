import cv2
import os
import time
import matplotlib.pyplot as plt
import math

import numpy as np


#this function is used to remove the characters from gray picture
def checkAround(simg,i,j):
    radius = 10
    if simg.shape[0]<=i+radius or simg.shape[1]<=j+radius or i<=radius or j<=radius:
        return False
    part = simg[i-radius:i+radius,j-radius:j+radius].flatten().tolist()
    flag1 = 0
    flag2 = 0
    # print("mhee")
    thres = radius*radius/5
    for pixel in part[0]:
        if pixel==255:
            flag1 += 1
        if pixel==210:
            flag2 += 1
    if flag1>thres and flag2>thres:
        return True
    else:
        return False

#get the around
def getContext(simg,i,j):
    radius = 10
    if simg.shape[0]<=i+radius or simg.shape[1]<=j+radius or i<=radius or j<=radius:
        return (False,False,False,False,False,False,False,False)
    cut1 = math.floor(radius/3.0)
    cut2 = math.ceil(radius*2.0/3.0)
    part = simg[i - radius:i + radius, j - radius:j + radius]
    # print(i,j,part.shape)
    n = part[0, cut1:cut2].tolist()
    s = part[-1, cut1:cut2].tolist()
    w = part[cut1:cut2, 0].tolist()
    e = part[0, cut1:cut2].tolist()
    nw = part[0, 0:cut1].tolist() + part[0:cut1, 0].tolist()
    ne = part[0, cut2:radius - 1].tolist() + part[0:cut1, radius - 1].tolist()
    sw = part[cut2:radius - 1, 0].tolist() + part[radius - 1, 0:cut1].tolist()
    se = part[radius - 1, cut2:radius - 1].tolist() + part[cut2:radius - 1, radius - 1].tolist()
    context=(n.count(0)>0,ne.count(0)>0,e.count(0)>0,se.count(0)>0,s.count(0)>0,sw.count(0)>0,w.count(0)>0,nw.count(0)>0)

    return context


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
        # print(gray)
        imgs.append(np.mat(gray)[68:1003, 187:1439].copy())#for binary
mat=np.zeros((datanum,datanum))
starttime=time.time()
features=[]
for id in range(datanum):
    time.sleep(1)
    kernel=np.array([[0, 0, 0, 0, 0],
       [0, 0, 1, 0, 0],
       [0, 1, 1, 1, 0],
       [0, 0, 1, 0, 0],
       [0, 0, 0, 0, 0]], dtype="uint8")
    ero=cv2.dilate(imgs[id],kernel=cv2.getStructuringElement(cv2.MORPH_CROSS,(5,5)))
    lap = cv2.Laplacian(ero, cv2.CV_64F,ksize=1)  # 拉普拉斯边缘检测
    lap = np.uint8(np.absolute(lap))  ##对lap去绝对值
    # print(lap)
    ret, shape=cv2.threshold(lap,5,255, cv2.THRESH_BINARY_INV)
    # print(shape)
    # plt.imshow(shape),plt.title("shape1"),plt.show()
    # np.savetxt("./shape.csv", shape, delimiter=',')
    # print(shape)
    for i in range(len(shape)):
        for j in range(len(shape[0])):
            if(shape[i][j]==0):
                if(not checkAround(imgs[id],i,j)):
                    # print(i,j)
                    shape[i][j]=255

    # print(shape)

    # plt.imshow(shape),plt.title("shape2"),plt.show()
    np.savetxt("./shape.csv",shape, delimiter=',')
    harris=cv2.cornerHarris(shape, 5, 11, 0.04)
    max = harris.max()
    # print(max)
    ret, corner = cv2.threshold(harris, 0.1*max, 1, cv2.THRESH_BINARY)
    # print(corner.shape)
    feature = set()
    for i in range(len(shape)):
        for j in range(len(shape[0])):
            if (corner[i, j] == 1):
                feature.add(getContext(shape, i, j))
    features.append(feature)
    print(len(feature))
    # plt.imshow(corner),plt.show()
    # np.savetxt("./corner.csv",corner, delimiter=',')

mat=np.zeros((datanum,datanum))
for i in range(datanum):
    for j in range(datanum):
        mat[i][j]=len(features[i]^features[j])

np.savetxt("./distMat.csv",mat, delimiter=',')