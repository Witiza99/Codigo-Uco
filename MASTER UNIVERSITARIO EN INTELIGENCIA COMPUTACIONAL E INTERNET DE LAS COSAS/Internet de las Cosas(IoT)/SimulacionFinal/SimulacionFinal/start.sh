#!/bin/bash

#for py_file in $(find *.py)
#do
    #echo "$py_file"
    #gnome-terminal --execute python3.8  "$py_file" 

#done
gnome-terminal --execute python3.8 DispStage1Sensor1.py
sleep 1
gnome-terminal --execute python3.8 DispStage1Sensor2.py
sleep 1
gnome-terminal --execute python3.8 DispStage1Sensor3.py
sleep 1
gnome-terminal --execute python3.8 DispStage2Sensor1.py
sleep 1
gnome-terminal --execute python3.8 DispStage2Sensor2.py
sleep 1
gnome-terminal --execute python3.8 DispStage2Sensor3.py
sleep 1
gnome-terminal --execute python3.8 DispStage3Sensor1.py
sleep 1
gnome-terminal --execute python3.8 DispStage3Sensor2.py
sleep 1
gnome-terminal --execute python3.8 DispStage3Sensor3.py
sleep 1
gnome-terminal --execute python3.8 DispConexNube.py
sleep 1
gnome-terminal --execute python3.8 DispSensor1.py
sleep 1
gnome-terminal --execute python3.8 DispSensor2.py
sleep 1
gnome-terminal --execute python3.8 DispSensor3.py