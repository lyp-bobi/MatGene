import cv2
import os
import shutil
list = os.listdir("./output")


for i in range(0,len(list)):
    path=os.path.join("./output",list[i])
    path= os.path.abspath(path)
    print(path)
    if(os.path.isfile(path)) and path.find(".png")!=-1:
        img = cv2.imread(path)
        if(img.shape[1]==1627):
            shutil.copy(path,"./output/binDia")
        elif(img.shape[1]==1312):
            shutil.copy(path, "./output/triDia")
