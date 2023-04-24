import numpy as np
import pygame as pg
from math import sin, cos, radians, tanh

from point import Point
from physics import Physics
from pointmass import PointMass

ARM_JOINT_DIST = 50
LEG_LENGTH = 60

from random import uniform

LEFT_RANGE = -10
RIGHT_RANGE = 10

class Stickman:
    def __init__(self, x, y, bodyHeight, physics: Physics) -> None:
        headLength = bodyHeight / 7.5
        headWidth = headLength * .75

        self.head = PointMass(x + uniform(LEFT_RANGE, RIGHT_RANGE), y + uniform(LEFT_RANGE, RIGHT_RANGE))
        self.head.mass = 4

        self.shoulder = PointMass(x + uniform(LEFT_RANGE, RIGHT_RANGE), y + uniform(LEFT_RANGE, RIGHT_RANGE))
        self.shoulder.mass = 26

        self.head.attachTo(self.shoulder, 5/4*headLength, 1)

        self.elbowL = PointMass(x + uniform(LEFT_RANGE, RIGHT_RANGE), y + uniform(LEFT_RANGE, RIGHT_RANGE))
        self.elbowR = PointMass(x + uniform(LEFT_RANGE, RIGHT_RANGE), y + uniform(LEFT_RANGE, RIGHT_RANGE))
        self.elbowL.mass = 2
        self.elbowR.mass = 2
        self.elbowL.attachTo(self.shoulder, headLength*3/2, 1)
        self.elbowR.attachTo(self.shoulder, headLength*3/2, 1)

        self.handL = PointMass(x + uniform(LEFT_RANGE, RIGHT_RANGE), y + uniform(LEFT_RANGE, RIGHT_RANGE))
        self.handR = PointMass(x + uniform(LEFT_RANGE, RIGHT_RANGE), y + uniform(LEFT_RANGE, RIGHT_RANGE))
        self.handL.mass = 2
        self.handR.mass = 2
        self.handL.attachTo(self.elbowL, headLength*2, 1)
        self.handR.attachTo(self.elbowR, headLength*2, 1)

        self.pelvis = PointMass(x + uniform(LEFT_RANGE, RIGHT_RANGE), y + uniform(LEFT_RANGE, RIGHT_RANGE))
        self.pelvis.mass = 15
        self.pelvis.attachTo(self.shoulder, headLength*3.5, 0.8)
        self.pelvis.attachTo(self.head, headLength*4.75, 0.02, draw_link=False)

        self.kneeL = PointMass(x + uniform(LEFT_RANGE, RIGHT_RANGE), y + uniform(LEFT_RANGE, RIGHT_RANGE))
        self.kneeR = PointMass(x + uniform(LEFT_RANGE, RIGHT_RANGE), y + uniform(LEFT_RANGE, RIGHT_RANGE))
        self.kneeL.mass = 10
        self.kneeR.mass = 10
        self.kneeL.attachTo(self.pelvis, headLength*2, 1)
        self.kneeR.attachTo(self.pelvis, headLength*2, 1)

        self.footL = PointMass(x + uniform(LEFT_RANGE, RIGHT_RANGE), y + uniform(LEFT_RANGE, RIGHT_RANGE))
        self.footR = PointMass(x + uniform(LEFT_RANGE, RIGHT_RANGE), y + uniform(LEFT_RANGE, RIGHT_RANGE))
        self.footL.mass = 5
        self.footR.mass = 5
        self.footL.attachTo(self.kneeL, headLength*2, 1)
        self.footR.attachTo(self.kneeR, headLength*2, 1)

        self.footL.attachTo(self.shoulder, headLength*7.5, 1e-3, draw_link=False)
        self.footR.attachTo(self.shoulder, headLength*7.5, 1e-3, draw_link=False)

        self.headCircle = Point(headLength * .75, (40, 40))
        self.headCircle.attachToPointMass(self.head)

        physics.addPoint(self.headCircle)
        
        self.pointmasses = []
        self.pointmasses.append(self.head)        
        self.pointmasses.append(self.shoulder)
        self.pointmasses.append(self.pelvis)
        self.pointmasses.append(self.elbowL)
        self.pointmasses.append(self.elbowR)
        self.pointmasses.append(self.handL)
        self.pointmasses.append(self.handR)
        self.pointmasses.append(self.kneeL)
        self.pointmasses.append(self.kneeR)
        self.pointmasses.append(self.footL)
        self.pointmasses.append(self.footR)
        
    def move(self, limb, angle):
        if limb == 1:
            return
        
        normal_angle = radians(tanh(angle)/10)
        
        x = self.pointmasses[limb].x
        y = self.pointmasses[limb].y
        
        point_c = None
        for link in self.pointmasses[0].links:
            if link.p1 == self.pointmasses[limb]:
                point_c = link.p2
                break
        
        x_c = point_c.x
        y_c = point_c.y
        
        self.pointmasses[limb].x = cos(normal_angle) * (x - x_c) - sin(normal_angle) * (y - y_c) + x_c
        self.pointmasses[limb].y = sin(normal_angle) * (x - x_c) + cos(normal_angle) * (y - y_c) + y_c
    
    def move_all(self, angles):
        for i, angle in enumerate(angles):
            self.move(i, angle)
    
    def get_coords(self):
        coords = []
        for point in self.pointmasses:
            coords.append([point.x, point.y])
        return np.array(coords, dtype=np.float32)