import numpy as np
import matplotlib.pyplot as plt
import sklearn.cluster
import math
import os
import cv2
import shutil
import time

distMat = np.loadtxt(open("./distMat.csv","rb"), delimiter=",", skiprows=0)
mylist=distMat.flatten()
mylist.sort()
thres=mylist[int(mylist.size/20)]
#agglomerative with complete linkage seems to be the best one

#y=sklearn.cluster.DBSCAN(eps=thres,min_samples=30,metric='precomputed').fit(distMat)
y=sklearn.cluster.AgglomerativeClustering(n_clusters=min(int(distMat.shape[0]/5),50),affinity='precomputed',linkage="complete").fit(distMat)
#y=sklearn.cluster.AffinityPropagation(affinity='precomputed').fit(distMat)
print(y.labels_)

clusternum=max(y.labels_)+1

os.mkdir("./clustered")
for i in range(clusternum):
    os.mkdir("./clustered/cluster"+str(i))

list = os.listdir("./diagrams")
imgs=[]
datanum=len(list)-1

for i in range(datanum):
    path=os.path.join("./diagrams",list[i])
    path= os.path.abspath(path)
    shutil.copy(path,"./clustered/cluster"+str(y.labels_[i]))