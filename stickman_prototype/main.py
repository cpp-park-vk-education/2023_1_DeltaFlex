import pygame as pg
import numpy as np
from stickman import Stickman
from physics import Physics
from pointmass import PointMass
import os
import random
import math
import tensorflow as tf
from time import time
import tensorflow_probability as tfp


os.environ["SDL_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR"] = '0'

WIDTH = 1280
HEIGHT = 720

def updateGraphics(pointmasses: list[PointMass], physics: Physics, color, surface):
    for pm in pointmasses:
        pm.draw(color, surface)
    for c in physics.points:
        c.draw(color, surface)

disp = pg.display.set_mode((WIDTH, HEIGHT), pg.SWSURFACE | pg.DOUBLEBUF, vsync=1)
clock = pg.time.Clock()
pg.display.flip()

M = 1
N = 10
TIME = 10

ph = Physics()

class Y_BEST:
    def __init__(self):
        self.y = 0
    
    def update(self, point):
        self.y += 1/point.y

# class Model():
#     def __init__(self, stickman):
#         self.stickman = stickman
#         model = tf.keras.models.Sequential([
#         tf.keras.layers.Dense(32, activation='relu', input_shape=(10,), name='hidden_layer_1'),
#         tf.keras.layers.Dropout(0.2, name='dropout'),
#         tf.keras.layers.Dense(10, name='hidden_layer_2')
# ])
        
model = tf.keras.models.Sequential([
    tf.keras.layers.Dense(30, activation='relu', input_shape=(11,2,), name='hidden_layer_1'),
    tf.keras.layers.Dropout(0.2, name='dropout'),
    tf.keras.layers.Dense(11, name='hidden_layer_2'),
    tf.keras.layers.Dense(1, activation='sigmoid', name='output_layer')
])


weights = [tf.constant(np.random.uniform(-0.1, 0.1, size=(2, 1)), dtype=tf.float32) for item in range(M)]


for i in range(N):
    stickmans = [Stickman(300*(j+1), 550, 250, ph) for j in range(M)]
    y_best = [Y_BEST() for item in range(M)]
    begin_time = time()
    while True:
        for e in pg.event.get():
            if e.type == pg.QUIT:
                exit(0)
        disp.fill(0)

        for i, stickman in enumerate(stickmans):
            ph.update(clock, stickman.pointmasses, WIDTH, HEIGHT)
        
        for j in range(M):
            data = tf.constant(stickmans[j].get_coords().reshape((1, 11, 2)), dtype=tf.float32)
            result = model.predict(data, 1)
            stickmans[j].move_all(np.array(result).flatten())
            
        for j in range(M):
            y_best[j].update(stickmans[j].pointmasses[0])

        for j in range(M):
            updateGraphics(stickmans[j].pointmasses, ph, pg.Color(255, 255, 255), disp)

        pg.display.set_caption(f'FPS: {clock.get_fps():.2f}')
        pg.display.flip()
        clock.tick(120)
        
        if time() - begin_time > TIME:
            stickmans[0].pointmasses[0].links.clear()
            stickmans[0].pointmasses.clear()
            ph.points.clear()
            break