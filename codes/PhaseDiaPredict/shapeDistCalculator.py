import cv2
import os
import time
from shapeContextLib import shape_context
from shapeContextLib import morphology_utils, data_utils
import multiprocessing
from joblib import Parallel, delayed
import numpy as np
from sklearn.cluster import MiniBatchKMeans
import shutil

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
        imgs.append(gray[70:1001,188:1437])#for binary

mat=np.zeros((datanum,datanum))
starttime=time.time()

sc = shape_context.ShapeContext()
def sc_array(img):

    sp = morphology_utils.shape_points(img, 30)
    bh = sc.compute(sp)

    return bh


num_cores = multiprocessing.cpu_count()
sc_arrays_list  = Parallel(n_jobs=num_cores)(delayed(sc_array)(img) for img in imgs)
sc_arrays = np.array(sc_arrays_list)
np.savetxt("./shapeDistMat.csv",sc_arrays, delimiter=',')
print(sc_arrays)
shoe_clusters = MiniBatchKMeans(init='k-means++', n_clusters=50, batch_size=50,
			                        n_init=3, max_no_improvement=10, verbose=0)
shoe_clusters.fit(sc_arrays)
print(shoe_clusters.labels_)


y=shoe_clusters

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