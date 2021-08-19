import pandas as pd
import plotly.express as px
import matplotlib.pyplot as plt

vel_df = pd.read_csv('output/raw/heyoka_delta_t_sim.csv')
vel_delta_t_list = [pd.read_csv('output/raw/delta_t1.csv'), pd.read_csv('output/raw/delta_t2.csv'),
                    pd.read_csv('output/raw/delta_t3.csv'), pd.read_csv('output/raw/delta_t4.csv'),
                    pd.read_csv('output/raw/delta_t5.csv'), pd.read_csv('output/raw/delta_t6.csv'),
                    pd.read_csv('output/raw/delta_t7.csv'), pd.read_csv('output/raw/delta_t8.csv'),
                    pd.read_csv('output/raw/delta_t9.csv'), pd.read_csv('output/raw/delta_t10.csv'),
                    pd.read_csv('output/raw/delta_t11.csv'), pd.read_csv('output/raw/delta_t12.csv'),
                    pd.read_csv('output/raw/delta_t13.csv'), pd.read_csv('output/raw/delta_t14.csv'),
                    pd.read_csv('output/raw/delta_t15.csv'), pd.read_csv('output/raw/delta_t16.csv'),
                    pd.read_csv('output/raw/delta_t17.csv'), pd.read_csv('output/raw/delta_t18.csv'),
                    pd.read_csv('output/raw/delta_t19.csv'), pd.read_csv('output/raw/delta_t20.csv')]
plt.plot(vel_df['time'], vel_df['vel_total norm'], label = 'Heyoka')

delta_t = 1.
denominator = 1
for df in vel_delta_t_list:
    plt.plot(df['time'], df['velocity norm'], label='delta t: 1/' + str(denominator))
    delta_t /= 2.
    denominator *= 2

plt.xlabel('t in s')
plt.ylabel('||v|| in km/s')
plt.title('Velocity using different delta t')
plt.legend()
plt.show()

delta_t = 1.
denominator = 1
for df in vel_delta_t_list:
    df['v abs error']=list(map(abs, vel_df['vel_total norm'] - df['velocity norm']))
    plt.plot(df['time'], df['v abs error'], label='delta t: 1/' + str(denominator))
    delta_t /= 2.
    denominator *= 2

plt.xlabel('t in s')
plt.ylabel('Absolute error in km/s')
plt.title('Absolute velocity error using different delta t')
plt.legend()
plt.show()


delta_t = 1.
denominator = 1
for df in vel_delta_t_list:
    df['v rel error']= df['v abs error'] / df['velocity norm']
    plt.plot(df['time'], df['v rel error'], label='delta t: 1/' + str(denominator))
    delta_t /= 2.
    denominator *= 2

plt.xlabel('t in s')
plt.ylabel('Relative error')
plt.title('Relative velocity error using different delta t')
plt.legend()
plt.show()

