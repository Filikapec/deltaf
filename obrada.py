
import cv2
import numpy as np

def Obradi(video) :
    img = cv2.cvtColor(video, cv2.COLOR_BGR2HSV) # Converting BGR image to HSV format

    lower = np.array([58, 0, 98])
    upper = np.array([144,255,255])
    mask = cv2.inRange(img, lower, upper) # Masking the image to find our color

    mask_contours, hierarchy = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE) # Finding contours in mask image

    # Finding position of all contours
    if len(mask_contours) != 0:
        for mask_contour in mask_contours:
            if cv2.contourArea(mask_contour) > 500:
                x, y, w, h = cv2.boundingRect(mask_contour)
                wpixprenos = w
                hpixprenos = h
                cv2.rectangle(video, (x, y), (x + w, y + h), (0, 0, 255), 3) #drawing rectangle
                cv2.circle(video, (int(x+w/2), int(y+h/2)), 15, (50,255, 20))
