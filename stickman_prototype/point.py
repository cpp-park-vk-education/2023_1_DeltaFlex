from pointmass import PointMass
import pygame as pg

class Point:
    radius = 0
    
    def __init__(self, radius, pmLoc: tuple):
        self.radius = radius
        self.attachedPointMass = PointMass(*pmLoc)
    
    def solveConstraints(self, width, height):
        x = self.attachedPointMass.x
        y = self.attachedPointMass.y

        if (y < self.radius):
            y = 2 * self.radius - y
        if (y > height - self.radius):
            y = 2 * (height - self.radius) - y

        if (x < self.radius):
            x = 2 * self.radius - x
        if (x > width - self.radius):
            x = 2 * (width - self.radius) - x

        self.attachedPointMass.x = x
        self.attachedPointMass.y = y

    def attachToPointMass(self, p: PointMass):
        self.attachedPointMass = p

    def draw(self, color: pg.Color, surface: pg.Surface):
        pg.draw.circle(surface, color, (self.attachedPointMass.x, self.attachedPointMass.y), self.radius)
