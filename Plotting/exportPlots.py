import pandas as pd
import plotly.express as px
import matplotlib.pyplot as plt
import plotly.graph_objects as go
import math
config = {'staticPlot': True}
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
                    pd.read_csv('output/processed/delta_t_2_short_29.csv', engine='c', float_precision='high')]
fig = go.Figure()
delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    if delta_t <= 0.5e-6 and delta_t >= 0.5e-8:
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
    if delta_t <= 0.5e-6 and delta_t >= 0.5e-8:
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
errors = {'delta_t':[],'abs v err ave':[],'rel v err ave':[],}
for df in vel_delta_t_list:
    if exponent <= -4:
        errors['delta_t'].append(delta_t)
        errors['abs v err ave'].append(df['abs v err ave'][df.index[-1]])
        errors['rel v err ave'].append(df['rel v err ave'][df.index[-1]])
    delta_t /= 2.
    exponent -= 1

fig.add_trace(go.Scatter(x=errors['delta_t'], y=errors['abs v err ave'], line_shape='linear'))
fig.update_yaxes(type="log", exponentformat='e', title_text='Average absolute velocity component error')
fig.update_xaxes(type="log", exponentformat='e', title_text='delta t in s')
#fig.show(config=config)
fig.write_image("../figures/abs_err_delta_t.png")

fig = go.Figure()
fig.add_trace(go.Scatter(x=errors['delta_t'], y=errors['rel v err ave'], line_shape='linear'))
fig.update_yaxes(type="log", exponentformat='e', title_text='Average relative velocity component error')
fig.update_xaxes(type="log", exponentformat='e', title_text='delta t in s')
#fig.show(config=config)
fig.write_image("../figures/rel_err_delta_t.png")

#i = 0
#x=3740.16
#y=3740.16
#z=3740.16
#while i <= 200:
#    v = math.sqrt(398600.5/math.sqrt(x*x+y*y+z*z))
#    v = v/math.sqrt(6)
#    print("debris=" + str(x) + "," + str(y) + "," + str(z) + "|" + str(v) +"," + str(v) + "," + str(-2*v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(y) + "," + str(z) + "|" + str(-2*v) +"," + str(v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(y) + "," + str(z) + "|" + str(v) +"," + str(-2*v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(y) + "," + str(-z) + "|" + str(v) +"," + str(v) + "," + str(-2*v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(y) + "," + str(-z) + "|" + str(-2*v) +"," + str(v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(y) + "," + str(-z) + "|" + str(v) +"," + str(-2*v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(-y) + "," + str(z) + "|" + str(v) +"," + str(v) + "," + str(-2*v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(-y) + "," + str(z) + "|" + str(-2*v) +"," + str(v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(-y) + "," + str(z) + "|" + str(v) +"," + str(-2*v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(-y) + "," + str(-z) + "|" + str(v) +"," + str(v) + "," + str(-2*v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(-y) + "," + str(-z) + "|" + str(-2*v) +"," + str(v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(-y) + "," + str(-z) + "|" + str(v) +"," + str(-2*v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(y) + "," + str(z) + "|" + str(v) +"," + str(v) + "," + str(-2*v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(y) + "," + str(z) + "|" + str(-2*v) +"," + str(v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(y) + "," + str(z) + "|" + str(v) +"," + str(-2*v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(y) + "," + str(-z) + "|" + str(v) +"," + str(v) + "," + str(-2*v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(y) + "," + str(-z) + "|" + str(-2*v) +"," + str(v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(y) + "," + str(-z) + "|" + str(v) +"," + str(-2*v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(-y) + "," + str(z) + "|" + str(v) +"," + str(v) + "," + str(-2*v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(-y) + "," + str(z) + "|" + str(-2*v) +"," + str(v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(-y) + "," + str(z) + "|" + str(v) +"," + str(-2*v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(-y) + "," + str(-z) + "|" + str(v) +"," + str(v) + "," + str(-2*v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(-y) + "," + str(-z) + "|" + str(-2*v) +"," + str(v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(-y) + "," + str(-z) + "|" + str(v) +"," + str(-2*v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    x += 50*math.sqrt(3)
#    y += 50*math.sqrt(3)
#    z += 50*math.sqrt(3)
#    i += 1
#
#while i <= 40:
#    v = math.sqrt(398600.5/math.sqrt(x*x+y*y+z*z))
#    v = v/math.sqrt(6)
#    print("debris=" + str(x) + "," + str(y) + "," + str(z) + "|" + str(v) +"," + str(v) + "," + str(-2*v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(y) + "," + str(z) + "|" + str(-2*v) +"," + str(v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(y) + "," + str(z) + "|" + str(v) +"," + str(-2*v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(y) + "," + str(-z) + "|" + str(v) +"," + str(v) + "," + str(-2*v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(y) + "," + str(-z) + "|" + str(-2*v) +"," + str(v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(y) + "," + str(-z) + "|" + str(v) +"," + str(-2*v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(-y) + "," + str(z) + "|" + str(v) +"," + str(v) + "," + str(-2*v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(-y) + "," + str(z) + "|" + str(-2*v) +"," + str(v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(-y) + "," + str(z) + "|" + str(v) +"," + str(-2*v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(-y) + "," + str(-z) + "|" + str(v) +"," + str(v) + "," + str(-2*v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(-y) + "," + str(-z) + "|" + str(-2*v) +"," + str(v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(-y) + "," + str(-z) + "|" + str(v) +"," + str(-2*v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(y) + "," + str(z) + "|" + str(v) +"," + str(v) + "," + str(-2*v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(y) + "," + str(z) + "|" + str(-2*v) +"," + str(v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(y) + "," + str(z) + "|" + str(v) +"," + str(-2*v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(y) + "," + str(-z) + "|" + str(v) +"," + str(v) + "," + str(-2*v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(y) + "," + str(-z) + "|" + str(-2*v) +"," + str(v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(y) + "," + str(-z) + "|" + str(v) +"," + str(-2*v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(-y) + "," + str(z) + "|" + str(v) +"," + str(v) + "," + str(-2*v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(-y) + "," + str(z) + "|" + str(-2*v) +"," + str(v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(-y) + "," + str(z) + "|" + str(v) +"," + str(-2*v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(-y) + "," + str(-z) + "|" + str(v) +"," + str(v) + "," + str(-2*v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(-y) + "," + str(-z) + "|" + str(-2*v) +"," + str(v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(-y) + "," + str(-z) + "|" + str(v) +"," + str(-2*v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    x += 500*math.sqrt(3)
#    y += 500*math.sqrt(3)
#    z += 500*math.sqrt(3)
#    i += 1
#
#while i <= 200:
#    v = math.sqrt(398600.5/math.sqrt(x*x+y*y+z*z))
#    v = v/math.sqrt(6)
#    print("debris=" + str(x) + "," + str(y) + "," + str(z) + "|" + str(v) +"," + str(v) + "," + str(-2*v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(y) + "," + str(z) + "|" + str(-2*v) +"," + str(v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(y) + "," + str(z) + "|" + str(v) +"," + str(-2*v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(y) + "," + str(-z) + "|" + str(v) +"," + str(v) + "," + str(-2*v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(y) + "," + str(-z) + "|" + str(-2*v) +"," + str(v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(y) + "," + str(-z) + "|" + str(v) +"," + str(-2*v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(-y) + "," + str(z) + "|" + str(v) +"," + str(v) + "," + str(-2*v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(-y) + "," + str(z) + "|" + str(-2*v) +"," + str(v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(-y) + "," + str(z) + "|" + str(v) +"," + str(-2*v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(-y) + "," + str(-z) + "|" + str(v) +"," + str(v) + "," + str(-2*v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(-y) + "," + str(-z) + "|" + str(-2*v) +"," + str(v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(x) + "," + str(-y) + "," + str(-z) + "|" + str(v) +"," + str(-2*v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(y) + "," + str(z) + "|" + str(v) +"," + str(v) + "," + str(-2*v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(y) + "," + str(z) + "|" + str(-2*v) +"," + str(v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(y) + "," + str(z) + "|" + str(v) +"," + str(-2*v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(y) + "," + str(-z) + "|" + str(v) +"," + str(v) + "," + str(-2*v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(y) + "," + str(-z) + "|" + str(-2*v) +"," + str(v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(y) + "," + str(-z) + "|" + str(v) +"," + str(-2*v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(-y) + "," + str(z) + "|" + str(v) +"," + str(v) + "," + str(-2*v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(-y) + "," + str(z) + "|" + str(-2*v) +"," + str(v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(-y) + "," + str(z) + "|" + str(v) +"," + str(-2*v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(-y) + "," + str(-z) + "|" + str(v) +"," + str(v) + "," + str(-2*v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(-y) + "," + str(-z) + "|" + str(-2*v) +"," + str(v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    print("debris=" + str(-x) + "," + str(-y) + "," + str(-z) + "|" + str(v) +"," + str(-2*v) + "," + str(v) + "|0,0,0|0,0,0|2e-5|0.05")
#    x += 50*math.sqrt(3)
#    y += 50*math.sqrt(3)
#    z += 50*math.sqrt(3)
#    i += 1

orbit_df = pd.read_csv('output/raw/orbit_comparison.csv', engine='c', float_precision='high')
orbit_acc_df = pd.read_csv('output/raw/orbit_comparison_acc.csv', engine='c', float_precision='high')
df = orbit_df.merge(orbit_acc_df, left_index=True, right_index=True)

fig = go.Figure()
fig.add_trace(go.Scatter(x=df['position norm'], y=df['acc_kep norm'], line_shape='linear'))
fig.update_yaxes(title_text='Kep acceleration')
fig.update_xaxes(title_text='|x|')
fig.write_image("../figures/acc_kep.png")

fig = go.Figure()
fig.add_trace(go.Scatter(x=df['position norm'], y=df['acc_j2 norm'], line_shape='linear'))
fig.update_yaxes(title_text='J2 acceleration')
fig.update_xaxes(title_text='|x|')
fig.write_image("../figures/acc_j2.png")

fig = go.Figure()
fig.add_trace(go.Scatter(x=df['position norm'], y=df['acc_s22 norm'], line_shape='linear'))
fig.update_yaxes(title_text='S22 acceleration')
fig.update_xaxes(title_text='|x|')
fig.write_image("../figures/acc_s22.png")

fig = go.Figure()
fig.add_trace(go.Scatter(x=df['position norm'], y=df['acc_c22 norm'], line_shape='linear'))
fig.update_yaxes(title_text='C22 acceleration')
fig.update_xaxes(title_text='|x|')
fig.write_image("../figures/acc_c22.png")

fig = go.Figure()
fig.add_trace(go.Scatter(x=df['position norm'], y=df['acc_sol norm'], line_shape='linear'))
fig.update_yaxes(title_text='Sol acceleration')
fig.update_xaxes(title_text='|x|')
fig.write_image("../figures/acc_sun.png")

fig = go.Figure()
fig.add_trace(go.Scatter(x=df['position norm'], y=df['acc_lun norm'], line_shape='linear'))
fig.update_yaxes(title_text='Lun acceleration')
fig.update_xaxes(title_text='|x|')
fig.write_image("../figures/acc_lun.png")

fig = go.Figure()
fig.add_trace(go.Scatter(x=df['position norm'], y=df['acc_srp norm'], line_shape='linear'))
fig.update_yaxes(title_text='SRP acceleration')
fig.update_xaxes(title_text='|x|')
fig.write_image("../figures/acc_srp.png")

fig = go.Figure()
fig.add_trace(go.Scatter(x=df['position norm'], y=df['acc_drag norm'], line_shape='linear'))
fig.update_yaxes(type="log", exponentformat='e', title_text='Drag acceleration')
fig.update_xaxes(title_text='|x|')
fig.write_image("../figures/acc_drag.png")

#ave_df = {'index' : range((4824//24)),
#          'position norm' : [.0]*(4824//24),
#          'acc_kep norm' : [.0]*(4824//24),
#          'acc_j2 norm' : [.0]*(4824//24),
#          'acc_s22 norm' : [.0]*(4824//24),
#          'acc_c22 norm' : [.0]*(4824//24),
#          'acc_sol norm' : [.0]*(4824//24),
#          'acc_lun norm' : [.0]*(4824//24),
#          'acc_srp norm' : [.0]*(4824//24),
#          'acc_drag norm' : [.0]*(4824//24)}
#ave_df = pd.DataFrame.from_dict(ave_df)
#for i in range(366//7):
#    print(i*7)
#    orbit_df = pd.read_csv('output/raw/orbit_comparison' + str(i*7) + '.csv', engine='c', float_precision='high')
#    orbit_acc_df = pd.read_csv('output/raw/orbit_comparison' + str(i) + '_acc.csv', engine='c', float_precision='high')
#    df = orbit_df.merge(orbit_acc_df, left_index=True, right_index=True)
#    for j in df['index_x']:
#        ave_df['position norm'][j//24]+=df['position norm'][j]/(24*365//7)
#        ave_df['acc_kep norm'][j//24]+=df['acc_kep norm'][j]/(24*365//7)
#        ave_df['acc_j2 norm'][j//24]+=df['acc_j2 norm'][j]/(24*365//7)
#        ave_df['acc_s22 norm'][j//24]+=df['acc_s22 norm'][j]/(24*365//7)
#        ave_df['acc_c22 norm'][j//24]+=df['acc_c22 norm'][j]/(24*365//7)
#        ave_df['acc_sol norm'][j//24]+=df['acc_sol norm'][j]/(24*365//7)
#        ave_df['acc_lun norm'][j//24]+=df['acc_lun norm'][j]/(24*365//7)
#        ave_df['acc_srp norm'][j//24]+=df['acc_srp norm'][j]/(24*365//7)
#        ave_df['acc_drag norm'][j//24]+=df['acc_drag norm'][j]/(24*365//7)
ave_df = pd.read_csv('output/processed/week_ave_orbit_comparison.csv', engine='c', float_precision='high')
ave_df['sun acc norm'] = ave_df['acc_kep norm']\
                        +ave_df['acc_j2 norm']\
                        +ave_df['acc_s22 norm']\
                        +ave_df['acc_c22 norm']\
                        +ave_df['acc_sol norm']\
                        +ave_df['acc_lun norm']\
                        +ave_df['acc_srp norm']\
                        +ave_df['acc_drag norm']
ave_df['acc_kep percent'] = ave_df['acc_kep norm'] / ave_df['sun acc norm']
ave_df['acc_j2 percent']  = ave_df['acc_j2 norm'] / ave_df['sun acc norm']
ave_df['acc_s22 percent'] = ave_df['acc_s22 norm'] / ave_df['sun acc norm']
ave_df['acc_c22 percent'] = ave_df['acc_c22 norm'] / ave_df['sun acc norm']
ave_df['acc_sol percent'] = ave_df['acc_sol norm'] / ave_df['sun acc norm']
ave_df['acc_lun percent'] = ave_df['acc_lun norm'] / ave_df['sun acc norm']
ave_df['acc_srp percent'] = ave_df['acc_srp norm'] / ave_df['sun acc norm']
ave_df['acc_drag percent'] = ave_df['acc_drag norm'] / ave_df['sun acc norm']

print(ave_df)
ave_df.to_csv('output/processed/week_ave_orbit_comparison.csv')

fig = go.Figure()
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_kep percent'], name='Kep', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_j2 percent'], name='J2', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_c22 percent'], name='C22', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_s22 percent'], name='S22', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_lun percent'], name='Lun', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_sol percent'], name='Sol', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_srp percent'], name='SRP', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_drag percent'], name='Drag', line_shape='linear'))
fig.update_yaxes(title_text='Accelerations relative to each other')
fig.update_xaxes(title_text='|x|')
fig.write_image("../figures/week_ave_acc_rel.png")

fig = go.Figure()
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_kep percent'], name='Kep', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_j2 percent'], name='J2', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_c22 percent'], name='C22', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_s22 percent'], name='S22', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_lun percent'], name='Lun', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_sol percent'], name='Sol', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_srp percent'], name='SRP', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_drag percent'], name='Drag', line_shape='linear'))
fig.update_yaxes(type="log", title_text='Accelerations relative to each other')
fig.update_xaxes(title_text='|x|')
fig.write_image("../figures/week_ave_acc_rel_log.png")

fig = go.Figure()
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_kep percent'], name='Kep', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_j2 percent'], name='J2', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_c22 percent'], name='C22', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_s22 percent'], name='S22', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_lun percent'], name='Lun', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_sol percent'], name='Sol', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_srp percent'], name='SRP', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_drag percent'], name='Drag', line_shape='linear'))
fig.update_yaxes(title_text='Accelerations relative to each other')
fig.update_xaxes(type="log", title_text='|x|')
fig.write_image("../figures/week_ave_acc_rel_log_pos.png")

fig = go.Figure()
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_kep percent'], name='Kep', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_j2 percent'], name='J2', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_c22 percent'], name='C22', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_s22 percent'], name='S22', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_lun percent'], name='Lun', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_sol percent'], name='Sol', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_srp percent'], name='SRP', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_drag percent'], name='Drag', line_shape='linear'))
fig.update_yaxes(type="log", title_text='Accelerations relative to each other')
fig.update_xaxes(type="log", title_text='|x|')
fig.write_image("../figures/week_ave_acc_rel_log_log_pos.png")

fig = go.Figure()
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_j2 percent'], name='J2', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_c22 percent'], name='C22', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_s22 percent'], name='S22', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_lun percent'], name='Lun', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_sol percent'], name='Sol', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_srp percent'], name='SRP', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_drag percent'], name='Drag', line_shape='linear'))
fig.update_yaxes(title_text='Accelerations relative to each other without Kepler')
fig.update_xaxes(title_text='|x|')
fig.write_image("../figures/week_ave_acc_rel_no_kep.png")

fig = go.Figure()
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_j2 percent'], name='J2', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_c22 percent'], name='C22', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_s22 percent'], name='S22', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_lun percent'], name='Lun', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_sol percent'], name='Sol', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_srp percent'], name='SRP', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_drag percent'], name='Drag', line_shape='linear'))
fig.update_yaxes(type="log", title_text='Accelerations relative to each other without Kepler')
fig.update_xaxes(title_text='|x|')
fig.write_image("../figures/week_ave_acc_rel_no_kep_log.png")

fig = go.Figure()
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_j2 percent'], name='J2', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_c22 percent'], name='C22', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_s22 percent'], name='S22', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_lun percent'], name='Lun', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_sol percent'], name='Sol', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_srp percent'], name='SRP', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_drag percent'], name='Drag', line_shape='linear'))
fig.update_yaxes(title_text='Accelerations relative to each other without Kepler')
fig.update_xaxes(type="log", title_text='|x|')
fig.write_image("../figures/week_ave_acc_rel_no_kep_log_pos.png")

fig = go.Figure()
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_j2 percent'], name='J2', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_c22 percent'], name='C22', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_s22 percent'], name='S22', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_lun percent'], name='Lun', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_sol percent'], name='Sol', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_srp percent'], name='SRP', line_shape='linear'))
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_drag percent'], name='Drag', line_shape='linear'))
fig.update_yaxes(type="log", title_text='Accelerations relative to each other without Kepler')
fig.update_xaxes(type="log", title_text='|x|')
fig.write_image("../figures/week_ave_acc_rel_no_kep_log_log_pos.png")

fig = go.Figure()
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_kep norm'], line_shape='linear'))
fig.update_yaxes(title_text='Kep acceleration')
fig.update_xaxes(title_text='|x|')
fig.write_image("../figures/week_ave_acc_kep.png")

fig = go.Figure()
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_j2 norm'], line_shape='linear'))
fig.update_yaxes(title_text='J2 acceleration')
fig.update_xaxes(title_text='|x|')
fig.write_image("../figures/week_ave_acc_j2.png")

fig = go.Figure()
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_s22 norm'], line_shape='linear'))
fig.update_yaxes(title_text='S22 acceleration')
fig.update_xaxes(title_text='|x|')
fig.write_image("../figures/week_ave_acc_s22.png")

fig = go.Figure()
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_c22 norm'], line_shape='linear'))
fig.update_yaxes(title_text='C22 acceleration')
fig.update_xaxes(title_text='|x|')
fig.write_image("../figures/week_ave_acc_c22.png")

fig = go.Figure()
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_sol norm'], line_shape='linear'))
fig.update_yaxes(title_text='Sol acceleration')
fig.update_xaxes(title_text='|x|')
fig.write_image("../figures/week_ave_acc_sun.png")

fig = go.Figure()
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_lun norm'], line_shape='linear'))
fig.update_yaxes(title_text='Lun acceleration')
fig.update_xaxes(title_text='|x|')
fig.write_image("../figures/week_ave_acc_lun.png")

fig = go.Figure()
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_srp norm'], line_shape='linear'))
fig.update_yaxes(title_text='SRP acceleration')
fig.update_xaxes(title_text='|x|')
fig.write_image("../figures/week_ave_acc_srp.png")

fig = go.Figure()
fig.add_trace(go.Scatter(x=ave_df['position norm'], y=ave_df['acc_drag norm'], line_shape='linear'))
fig.update_yaxes(type="log", exponentformat='e', title_text='Drag acceleration')
fig.update_xaxes(title_text='|x|')
fig.write_image("../figures/week_ave_acc_drag.png")
