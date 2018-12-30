import cv2
import os
from sklearn import datasets
from sklearn.cluster import AgglomerativeClustering
import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix
import pandas as pd
import numpy as np
import time
list = os.listdir("./diagrams")

# Deprecated
imgs=[]
kps=[]
dess=[]

for i in range(0,len(list)):
    path=os.path.join("./diagrams",list[i])
    path= os.path.abspath(path)
    print(path)
    if(os.path.isfile(path)) and path.find(".png")!=-1:
        img = cv2.imread(path)
        gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        sift = cv2.xfeatures2d.SIFT_create()
        kp, des = sift.detectAndCompute(gray, None)
        #imgs.append(img)
        #kps.append(kp)
        dess.append(des)
#print(dess)

mat=np.zeros((len(list),len(list)))

# BFMatcher with default params
# bf = cv2.BFMatcher()
# matches = bf.match(dess[0], dess[1])

# # Apply ratio test
# good = []
# for m, n in matches:
#     if m.distance < 0.75 * n.distance:
#         good.append([m])
# create BFMatcher object
bf = cv2.BFMatcher()

for m in range(769,len(list)-1):#-1 stand for the index.txt
    print(str(m) + "started")
    for n in range(len(list)-1):#please DON'T store other files in ./diagrams folder

        # Match descriptors.
        matches = bf.match(dess[m],dess[n])

        # Sort them in the order of their distance.
        matches = sorted(matches, key = lambda x:x.distance)

        # Draw first 10 matches.
        #img3 = cv2.drawMatches(imgs[m],kps[m],imgs[n],kps[n],matches[:50],None, flags=2)

        #plt.imshow(img3),plt.show()

        dist = 0
        for i in range(50):
            dist+=matches[0].distance
        #print("distance between "+str(m)+str(n)+" is "+str(dist))
        mat[m,n]=dist
                # img = cv2.drawKeypoints(gray, kps, img)
                #
                # cv2.imshow("img", img)
                #
                # k = cv2.waitKey(0)
                # if k & 0xff == 27:
                #     cv2.destroyAllWindows()

    np.savetxt("./distMat.csv",mat, delimiter=',')
print(mat)