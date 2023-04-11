import pygame as pg
import numpy as np
gravity = 980


class PointMass:
    x_old, y_old = 0, 0
    x, y = 0, 0
    ax, ay = 0, 0

    mass = 1
    damping = 20

    links = []

    def __init__(self, x=0., y=0.) -> None:
        self.x = x
        self.y = y
        self.x_old = x
        self.y_old = y

    def applyForce(self, fx, fy):
        self.ax += fx / self.mass
        self.ay += fy / self.mass

    def updatePhysics(self, timestep: float):
        self.applyForce(0, self.mass * gravity)

        vx = self.x - self.x_old
        vy = self.y - self.y_old

        vx *= .99
        vy *= .99

        timestep_sq = timestep * timestep

        x_next = self.x + vx + .5 * self.ax * timestep_sq
        y_next = self.y + vy + .5 * self.ay * timestep_sq

        self.x_old = self.x
        self.y_old = self.y

        self.x = x_next
        self.y = y_next

        self.ax = 0
        self.ay = 0

    def solveConstraints(self, width, height):
        for i in range(len(self.links)):
            self.links[i].solve()

        if (self.y < 1):
            self.y = 2 * (1) - self.y
        if (self.y > height - 1):
            self.y = 2 * (height - 1) - self.y

        if (self.x < 1):
            self.x = 2 * (1) - self.x
        if (self.x > width - 1):
            self.x = 2 * (width - 1) - self.x

    def attachTo(self, p, resting_dist: float, stiffness: float, draw_link=True):
        lnk = Link(self, p, resting_dist, stiffness, draw_link)
        self.links.append(lnk)

    def draw(self, color: pg.Color, surface: pg.Surface):
        if (len(self.links) > 0):
            for i in range(len(self.links)):
                self.links[i].draw(color, surface)
        else:
            pg.draw.line(surface, color, (self.x, self.y), (self.x, self.y))


class Link:
    resting_dist = 0
    stiffness = 0
    draw_this = True

    def __init__(self, pm1: PointMass, pm2: PointMass, resting_dist, stiffness, draw_this: bool):
        self.p1 = pm1
        self.p2 = pm2

        self.resting_dist = resting_dist
        self.stiffness = stiffness
        self.draw_this = draw_this

    def solve(self):
        dx = self.p1.x - self.p2.x
        dy = self.p1.y - self.p2.y
        d = np.sqrt(dx * dx + dy * dy)

        difference = (self.resting_dist - d) / d

        im1 = 1 / self.p1.mass
        im2 = 1 / self.p2.mass

        p1_scalar = (im1 / (im1 + im2)) * self.stiffness
        p2_scalar = self.stiffness - p1_scalar

        self.p1.x += dx * p1_scalar * difference
        self.p1.y += dy * p1_scalar * difference

        self.p2.x -= dx * p2_scalar * difference
        self.p2.y -= dy * p2_scalar * difference

    def draw(self, color: pg.Color, surface: pg.Surface):
        if (self.draw_this):
            pg.draw.line(
                surface,
                color,
                (self.p1.x, self.p1.y),
                (self.p2.x, self.p2.y),
                width=5
            )
