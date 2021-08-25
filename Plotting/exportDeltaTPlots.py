import pandas as pd
import plotly.express as px
import matplotlib.pyplot as plt
import plotly.graph_objects as go

config = {'staticPlot': True}
vel_delta_t_list = [pd.read_csv('output/processed/delta_t_10_short_1.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_10_short_2.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_10_short_3.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_10_short_4.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_10_short_5.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_10_short_6.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_10_short_7.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_10_short_8.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_10_short_9.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_10_short_10.csv', engine='c', float_precision='high')]
fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 1e-4:
        fig.add_trace(go.Scatter(x=df['time'], y=df['abs v err ave'], name='delta t: 1e'+ str(exponent), line_shape='linear'))
    delta_t /= 10.
    exponent -= 1
fig.update_yaxes(type="log", exponentformat='e', title_text='Average absolute velocity component error in km/s')
fig.update_xaxes(title_text='time in s')
#fig.show(config=config)
fig.write_image("../figures/abs_err_short_10.png")

fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 1e-4:
        fig.add_trace(go.Scatter(x=df['time'], y=df['rel v err ave'], name='delta t: 1e'+ str(exponent), line_shape='linear'))
    delta_t /= 10.
    exponent -= 1
fig.update_yaxes(type="log", exponentformat='e', title_text='Average relative velocity component error in km/s')
fig.update_xaxes(title_text='time in s')
#fig.show(config=config)
fig.write_image("../figures/rel_err_short_10.png")

fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 1e-4:
        fig.add_trace(go.Scatter(x=df['time'], y=df['abs v err x'], name='delta t: 1e'+ str(exponent), line_shape='linear'))
    delta_t /= 10.
    exponent -= 1
fig.update_yaxes(type="log", exponentformat='e', title_text='Absolute velocity x component error in km/s')
fig.update_xaxes(title_text='time in s')
#fig.show(config=config)
fig.write_image("../figures/abs_x_err_short_10.png")

fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 1e-4:
        fig.add_trace(go.Scatter(x=df['time'], y=df['rel v err x'], name='delta t: 1e'+ str(exponent), line_shape='linear'))
    delta_t /= 10.
    exponent -= 1
fig.update_yaxes(type="log", exponentformat='e', title_text='Relative velocity x component error')
fig.update_xaxes(title_text='time in s')
#fig.show(config=config)
fig.write_image("../figures/rel_x_err_short_10.png")

fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 1e-4:
        fig.add_trace(go.Scatter(x=df['time'], y=df['abs v err y'], name='delta t: 1e'+ str(exponent), line_shape='linear'))
    delta_t /= 10.
    exponent -= 1
fig.update_yaxes(type="log", exponentformat='e', title_text='Absolute velocity y component error in km/s')
fig.update_xaxes(title_text='time in s')
#fig.show(config=config)
fig.write_image("../figures/abs_y_err_short_10.png")

fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 1e-4:
        fig.add_trace(go.Scatter(x=df['time'], y=df['rel v err y'], name='delta t: 1e'+ str(exponent), line_shape='linear'))
    delta_t /= 10.
    exponent -= 1
fig.update_yaxes(type="log", exponentformat='e', title_text='Relative velocity y component error')
fig.update_xaxes(title_text='time in s')
#fig.show(config=config)
fig.write_image("../figures/rel_y_err_short_10.png")

fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 1e-4:
        fig.add_trace(go.Scatter(x=df['time'], y=df['abs v err z'], name='delta t: 1e'+ str(exponent), line_shape='linear'))
    delta_t /= 10.
    exponent -= 1
fig.update_yaxes(type="log", exponentformat='e', title_text='Absolute velocity z component error in km/s')
fig.update_xaxes(title_text='time in s')
#fig.show(config=config)
fig.write_image("../figures/abs_z_err_short_10.png")

fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 1e-4:
        fig.add_trace(go.Scatter(x=df['time'], y=df['rel v err z'], name='delta t: 1e'+ str(exponent), line_shape='linear'))
    delta_t /= 10.
    exponent -= 1
fig.update_yaxes(type="log", exponentformat='e', title_text='Relative velocity z component error')
fig.update_xaxes(title_text='time in s')
#fig.show(config=config)
fig.write_image("../figures/rel_z_err_short_10.png")


vel_delta_t_list = [pd.read_csv('output/processed/delta_t_10_1.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_10_2.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_10_3.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_10_4.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_10_5.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_10_6.csv', engine='c', float_precision='high')]
fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 1e-4:
        fig.add_trace(go.Scatter(x=df['time'], y=df['abs v err ave'], name='delta t: 1e'+ str(exponent), line_shape='linear'))
    delta_t /= 10.
    exponent -= 1
fig.update_yaxes(type="log", exponentformat='e', title_text='Average absolute velocity component error in km/s')
fig.update_xaxes(title_text='time in s')
#fig.show(config=config)
fig.write_image("../figures/abs_err_10.png")

fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 1e-4:
        fig.add_trace(go.Scatter(x=df['time'], y=df['rel v err ave'], name='delta t: 1e'+ str(exponent), line_shape='linear'))
    delta_t /= 10.
    exponent -= 1
fig.update_yaxes(type="log", exponentformat='e', title_text='Average relative velocity component error in km/s')
fig.update_xaxes(title_text='time in s')
#fig.show(config=config)
fig.write_image("../figures/abs_err_10.png")

fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 1e-4:
        fig.add_trace(go.Scatter(x=df['time'], y=df['abs v err x'], name='delta t: 1e'+ str(exponent), line_shape='linear'))
    delta_t /= 10.
    exponent -= 1
fig.update_yaxes(type="log", exponentformat='e', title_text='Absolute velocity x component error in km/s')
fig.update_xaxes(title_text='time in s')
#fig.show(config=config)
fig.write_image("../figures/abs_x_err_10.png")

fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 1e-4:
        fig.add_trace(go.Scatter(x=df['time'], y=df['rel v err x'], name='delta t: 1e'+ str(exponent), line_shape='linear'))
    delta_t /= 10.
    exponent -= 1
fig.update_yaxes(type="log", exponentformat='e', title_text='Relative velocity x component error')
fig.update_xaxes(title_text='time in s')
#fig.show(config=config)
fig.write_image("../figures/rel_x_err_10.png")

fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 1e-4:
        fig.add_trace(go.Scatter(x=df['time'], y=df['abs v err y'], name='delta t: 1e'+ str(exponent), line_shape='linear'))
    delta_t /= 10.
    exponent -= 1
fig.update_yaxes(type="log", exponentformat='e', title_text='Absolute velocity y component error in km/s')
fig.update_xaxes(title_text='time in s')
#fig.show(config=config)
fig.write_image("../figures/abs_y_err_10.png")

fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 1e-4:
        fig.add_trace(go.Scatter(x=df['time'], y=df['rel v err y'], name='delta t: 1e'+ str(exponent), line_shape='linear'))
    delta_t /= 10.
    exponent -= 1
fig.update_yaxes(type="log", exponentformat='e', title_text='Relative velocity y component error')
fig.update_xaxes(title_text='time in s')
#fig.show(config=config)
fig.write_image("../figures/rel_y_err_10.png")

fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 1e-4:
        fig.add_trace(go.Scatter(x=df['time'], y=df['abs v err z'], name='delta t: 1e'+ str(exponent), line_shape='linear'))
    delta_t /= 10.
    exponent -= 1
fig.update_yaxes(type="log", exponentformat='e', title_text='Absolute velocity z component error in km/s')
fig.update_xaxes(title_text='time in s')
#fig.show(config=config)
fig.write_image("../figures/abs_z_err_10.png")

fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 1e-4:
        fig.add_trace(go.Scatter(x=df['time'], y=df['rel v err z'], name='delta t: 1e'+ str(exponent), line_shape='linear'))
    delta_t /= 10.
    exponent -= 1
fig.update_yaxes(type="log", exponentformat='e', title_text='Relative velocity z component error')
fig.update_xaxes(title_text='time in s')
#fig.show(config=config)
fig.write_image("../figures/rel_z_err_10.png")


vel_delta_t_list = [pd.read_csv('output/processed/delta_t_2_short_1.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_2.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_3.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_4.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_5.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_6.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_7.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_8.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_9.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_10.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_11.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_12.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_13.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_14.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_15.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_16.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_17.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_18.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_19.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_20.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_21.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_22.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_23.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_24.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_25.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_26.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_27.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_28.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_29.csv', engine='c', float_precision='high'),
                    pd.read_csv('output/processed/delta_t_2_short_30.csv', engine='c', float_precision='high')]
fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 1e-6:
        fig.add_trace(go.Scatter(x=df['time'], y=df['abs v err ave'], name='delta t: 2^('+ str(exponent) + ')', line_shape='linear'))
    delta_t /= 2.
    exponent -= 1
fig.update_yaxes(type="log", exponentformat='e', title_text='Average absolute velocity component error in km/s')
fig.update_xaxes(title_text='time in s')
#fig.show(config=config)
fig.write_image("../figures/abs_err_short_2.png")

fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 1e-6:
        fig.add_trace(go.Scatter(x=df['time'], y=df['rel v err ave'], name='delta t: 2^('+ str(exponent) + ')', line_shape='linear'))
    delta_t /= 2.
    exponent -= 1
fig.update_yaxes(type="log", exponentformat='e', title_text='Average relative velocity component error')
fig.update_xaxes(title_text='time in s')
#fig.show(config=config)
fig.write_image("../figures/rel_err_short_2.png")

fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 1e-6:
        fig.add_trace(go.Scatter(x=df['time'], y=df['abs v err x'], name='delta t: 1e'+ str(exponent), line_shape='linear'))
    delta_t /= 2.
    exponent -= 1
fig.update_yaxes(type="log", exponentformat='e', title_text='Absolute velocity x component error in km/s')
fig.update_xaxes(title_text='time in s')
#fig.show(config=config)
fig.write_image("../figures/abs_x_err_short_2.png")

fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 1e-6:
        fig.add_trace(go.Scatter(x=df['time'], y=df['rel v err x'], name='delta t: 1e'+ str(exponent), line_shape='linear'))
    delta_t /= 2.
    exponent -= 1
fig.update_yaxes(type="log", exponentformat='e', title_text='Relative velocity x component error')
fig.update_xaxes(title_text='time in s')
#fig.show(config=config)
fig.write_image("../figures/rel_x_err_short_2.png")

fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 1e-6:
        fig.add_trace(go.Scatter(x=df['time'], y=df['abs v err y'], name='delta t: 1e'+ str(exponent), line_shape='linear'))
    delta_t /= 2.
    exponent -= 1
fig.update_yaxes(type="log", exponentformat='e', title_text='Absolute velocity y component error in km/s')
fig.update_xaxes(title_text='time in s')
#fig.show(config=config)
fig.write_image("../figures/abs_y_err_short_2.png")

fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 1e-6:
        fig.add_trace(go.Scatter(x=df['time'], y=df['rel v err y'], name='delta t: 1e'+ str(exponent), line_shape='linear'))
    delta_t /= 2.
    exponent -= 1
fig.update_yaxes(type="log", exponentformat='e', title_text='Relative velocity y component error')
fig.update_xaxes(title_text='time in s')
#fig.show(config=config)
fig.write_image("../figures/rel_y_err_short_2.png")

fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 1e-6:
        fig.add_trace(go.Scatter(x=df['time'], y=df['abs v err z'], name='delta t: 1e'+ str(exponent), line_shape='linear'))
    delta_t /= 2.
    exponent -= 1
fig.update_yaxes(type="log", exponentformat='e', title_text='Absolute velocity z component error in km/s')
fig.update_xaxes(title_text='time in s')
#fig.show(config=config)
fig.write_image("../figures/abs_z_err_short_2.png")

fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 1e-6:
        fig.add_trace(go.Scatter(x=df['time'], y=df['rel v err z'], name='delta t: 1e'+ str(exponent), line_shape='linear'))
    delta_t /= 2.
    exponent -= 1
fig.update_yaxes(type="log", exponentformat='e', title_text='Relative velocity z component error')
fig.update_xaxes(title_text='time in s')
#fig.show(config=config)
fig.write_image("../figures/rel_z_err_short_2.png")
