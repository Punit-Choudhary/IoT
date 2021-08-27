import json
import tensorflow as tf
from tensorflow.keras.models import load_model
from tensorflow.keras.models import model_from_json


# Mode reconstruction from JSON file
with open("Intelligent Entry System for Covid Security\FaceMask_Detection_model_architecture.json", 'r') as f:
    model = model_from_json(f.read())

# Load weights into new model
model.load_weights("Intelligent Entry System for Covid Security\FaceMask_Detection_model_weights.h5")

#model.summary()

# Testing Model
import cv2
import numpy as np

label = {0: "With Mask", 1: "Without Mask"}
color_label = {0: (0,255,0), 1: (0,0,255)}

cap = cv2.VideoCapture(0)
cascade = cv2.CascadeClassifier("Intelligent Entry System for Covid Security\haarcascade_frontalface_default.xml")

while True:
    rval, frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
    faces = cascade.detectMultiScale(gray, 1.1)

    for x,y,w,h in faces:
        face_image = frame[y:y+h, x:x+w]
        resize_img = cv2.resize(face_image, (150,150))
        normalized = resize_img / 255.0
        reshape = np.reshape(normalized, (1,150,150,3))
        
        result = model.predict(reshape)
        result = result[0][0]

        if result <= 0.5:
            # Wearing Mask
            cv2.rectangle(frame, (x,y), (x+w, y+h), color_label[0], 3)
            cv2.rectangle(frame, (x,y-50), (x+w,y), color_label[0], -1)
            cv2.putText(frame, label[0], (x,y-10), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)
        elif result > 0.5:
            # Not wearing mask
            cv2.rectangle(frame, (x,y), (x+w, y+h), color_label[1], 3)
            cv2.rectangle(frame, (x,y-50), (x+w, y), color_label[1], -1)
            cv2.putText(frame, label[1], (x,y-10), cv2.FONT_HERSHEY_SIMPLEX, 1, (255, 255, 255), 2)

        cv2.imshow("LIVE", frame)

        key = cv2.waitKey(1)
        if key == 81:
            break

cap.release()
cv2.destroyAllWindows()
