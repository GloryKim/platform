#!/usr/bin/env python3
#-*- coding: utf-8 -*-
import requests #240624_1633_glory : node web server로 값을 보내기 위한
import rospy
from std_msgs.msg import Int8MultiArray, Float32MultiArray
import numpy as np
import sys
import cv2 as cv
import os
from datetime import datetime  # 240624_1631_glory : 시간타임으로 구분을 하기위한 추가된 부분
BASE_DIR = os.path.dirname(os.path.abspath(__file__))
ROOT_DIR = os.path.dirname(BASE_DIR)
sys.path.append(BASE_DIR + '/lib')

from MODet_Tracking.msg import tracking, test

import ros_utils as r_utils

import matching


class Matching_node():
    def __init__(self):
        ROI = rospy.get_param("ROI")
        input_topic_name = rospy.get_param("matching_input_topic_name", '/total_msg')

        self.map_pub = []
        self.ROI = ROI
        self.matcher = []
        self.server_url = "http://***.***.***.***:***/******"  # URL 변경
        for i in range(len(ROI[0])):
            
            rospy.Subscriber(f'{input_topic_name}_{i}', test, self.matching_callback, i, queue_size=10)
            self.matcher.append(matching.Matcher())
            # self.map_pub.append(rospy.Publisher(f'matching_{i}', OccupancyGrid, queue_size=1000))
            
            
#glory
    def matching_callback(self, total_msg, idx):
        print(' < matching Generation >')
        r_utils.tic()
        matcher = self.matcher[idx]
        # 트래킹 정보 취득
        tracks = total_msg.tracks
        obj_info = list()
        for trk in tracks:
            trk_id = trk.tracking_id
            x = trk.x
            y = trk.y
            z = trk.z
            velocity = trk.velocity
            angle = trk.angle
            current_time = datetime.now().strftime('%Y-%m-%d %H:%M:%S.%f')[:-3]
            
            # 서버로 전송할 데이터 형식 변경
            lidar_data = {
                "timestamp": int(datetime.now().timestamp() * 1000),
                "message": f"glory tracking:{trk_id}\t x:{x}\t y:{y}\t z:{z}\t velocity:{velocity}m/s \t angle:{angle} deg"
            }
            
            # 서버로 데이터 전송
            try:
                response = requests.post(self.server_url, json=lidar_data)
                if response.status_code != 200:
                    print(f"Failed to send data to server. Status code: {response.status_code}")
            except requests.exceptions.RequestException as e:
                print(f"Error sending data to server: {e}")

            obj_info.append([trk_id, x, y, z, velocity, angle])