import pygame as pg
import numpy as np
from stickman import Stickman
from physics import Physics
from pointmass import PointMass

WIDTH = 1280
HEIGHT = 720

def updateGraphics(pointmasses: list[PointMass], physics: Physics, color, surface):
    for pm in pointmasses:
        pm.draw(color, surface)
    for c in physics.points:
        c.draw(color, surface)

disp = pg.display.set_mode((WIDTH, HEIGHT), vsync=1)
clock = pg.time.Clock()
pg.display.flip()

i = 0
ph = Physics()
pointmasses = []
sm = Stickman(50, 50, 200, ph, pointmasses)

while True:
    for e in pg.event.get():
        if e.type == pg.QUIT:
            exit(0)
    disp.fill(0)

    ph.update(clock, pointmasses, WIDTH, HEIGHT)
    pointmasses[5].x, pointmasses[5].y = pg.mouse.get_pos()
    updateGraphics(pointmasses, ph, pg.Color(255, 255, 255), disp)

    pg.display.set_caption(f'FPS: {clock.get_fps():.2f}')
    pg.display.flip()
    clock.tick(120)
    
    
