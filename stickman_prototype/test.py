import tensorflow as tf
import tensorflow_probability as tfp
import numpy as np

model = tf.keras.models.Sequential([
    tf.keras.layers.Dense(30, activation='relu', input_shape=(11,2,), name='hidden_layer_1'),
    tf.keras.layers.Dropout(0.2, name='dropout'),
    tf.keras.layers.Dense(11, name='hidden_layer_2')
])

tf.keras.utils.plot_model(model, show_shapes=True)



tfp.optimizer.differential_evolution_one_step(
    objective_function,
    population,
    population_values=None,
    differential_weight=0.5,
    crossover_prob=0.9,
    seed=None,
    name=None
)