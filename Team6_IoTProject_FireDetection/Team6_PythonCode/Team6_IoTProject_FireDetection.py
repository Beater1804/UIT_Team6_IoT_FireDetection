#University of Information Technology
#Team6_IoTSolutionForFireDetection
#Member
#Nguyễn Thanh Dũng - 19521397
#Huỳnh Quốc Huy - 19520594
#Võ Phú Thịnh - 19522289
#Trịnh Duy Khương - 19521715

from asyncio.windows_events import NULL
import numpy as np
import cv2
import serial
import time

from paho.mqtt import client as mqtt_client
#//

broker = '172.31.250.214'
port = 1883
topic = "fire"
client_id = f'lens_LuvZtKVpEfi2JlPAZuaaMUSAygZ'
username = ''
password = ''

def connect_mqtt():
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)
    # Set Connecting Client ID
    client = mqtt_client.Client(client_id)
    client.username_pw_set(username, password)
    client.on_connect = on_connect
    client.connect(broker, port)
    return client

def publishS(client):
    msg="s"
    result = client.publish(topic, msg)

        

def publishP(client):
    msg = "p"
    result = client.publish(topic, msg)

        


fire_cascade = cv2.CascadeClassifier('team6_fire_detection.xml')
#fire_detection.xml file & this code should be in the same folder while running the code
client = connect_mqtt()

cap = cv2.VideoCapture(0)
ccc = cv2.VideoWriter_fourcc(*"MJPG")
out = cv2.VideoWriter('abc.avi',-1,20.0,(640,480))
while 1:
    client.loop_start()

    ret, img = cap.read()
    #cv2.imshow('imgorignal',img)

    # out.write(img)

    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
    fire = fire_cascade.detectMultiScale(img, 1.2, 5)
    
    for (x,y,w,h) in fire:
        cv2.rectangle(img,(x,y),(x+w,y+h),(0,0,255),2)
        roi_gray = gray[y:y+h, x:x+w]
        roi_color = img[y:y+h, x:x+w]
        print('Fire is detected..!')
        
        publishP(client)
        # ser1.write(str.encode('p'))
        time.sleep(0.1)
        
    cv2.imshow('img',img)
    publishS(client)
    # ser1.write(str.encode('s'))
    
    k = cv2.waitKey(30) & 0xff
    if k == 27:
        break

cap.release()
cv2.destroyAllWindows()
