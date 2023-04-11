from point import Point
from pointmass import PointMass
from time import time

class Physics:
    timePrev = time() * 1000
    timeCur = 0
    fixedDeltaTime = 0
    fixedDeltaTimeSeconds = 0
    leftOverDeltaTime = 0
    constraintAccuracy = 0
    points = []

    def __init__(self):
        self.fixedDeltaTime = 16
        self.fixedDeltaTimeSeconds = self.fixedDeltaTime / 1000
        self.leftOverDeltaTime = 0
        self.constraintAccuracy = 3

    def update(self, pointmasses: list[PointMass], width, height):
        self.timeCur = time() * 1000
        deltaTimeMS = self.timeCur - self.timePrev

        self.timePrev = self.timeCur

        timeStepAmt = int((deltaTimeMS + self.leftOverDeltaTime) / self.fixedDeltaTime)

        timeStepAmt = min(timeStepAmt, 5)

        self.leftOverDeltaTime = int(deltaTimeMS) - (timeStepAmt * self.fixedDeltaTime)

        for _ in range(timeStepAmt):
            for _ in range(self.constraintAccuracy):
                for i in range(len(pointmasses)):
                    pointmasses[i].solveConstraints(width, height)
                for i in range(len(self.points)):
                    self.points[i].solveConstraints(width, height)

            for i in range(len(pointmasses)):
                pointmasses[i].updatePhysics(self.fixedDeltaTimeSeconds)

    def addPoint(self, c: Point):
        self.points.append(c)

    def removePoint(self, c: Point):
        self.points.remove(c)
