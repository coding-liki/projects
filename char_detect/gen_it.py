import numpy as np
import cv2
img = np.zeros((50,100,3), np.uint8)
np=np+255
cv2.putText(img,"go",(0,30),cv2.FONT_HERSHEY_SIMPLEX, 3, 0)
cv2.imshow('image',img)
cv2.waitKey(0)
cv2.destroyAllWindows()