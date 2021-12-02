import pandas as pd
import plotly.express as px
import matplotlib.pyplot as plt

vel_df = pd.read_csv('output/raw/heyoka_delta_t_ld_sim.csv')
vel_delta_t_list = [pd.read_csv('output/raw/delta_t_10_1.csv'),
                    pd.read_csv('output/raw/delta_t_10_2.csv'),
                    pd.read_csv('output/raw/delta_t_10_3.csv'),
                    pd.read_csv('output/raw/delta_t_10_4.csv'),
                    pd.read_csv('output/raw/delta_t_10_5.csv'),
                    pd.read_csv('output/raw/delta_t_10_6.csv'),
                    pd.read_csv('output/raw/delta_t_10_7.csv'),
                    pd.read_csv('output/raw/delta_t_10_8.csv')]
plt.plot(vel_df['time'], vel_df['vel_total norm'], label = 'Heyoka')

delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    plt.plot(df['time'], df['velocity norm'], label='delta t: 1e'+ str(exponent))
    delta_t /= 10.
    exponent -= 1

plt.xlabel('t in s')
plt.ylabel('||v|| in km/s')
plt.title('Velocity using different delta t')
plt.legend()
plt.show()

delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    df['v abs error']=list(map(abs, vel_df['vel_total norm'] - df['velocity norm']))
    plt.plot(df['time'], df['v abs error'], label='delta t: 1e'+ str(exponent))
    delta_t /= 10.
    exponent -= 1

plt.xlabel('t in s')
plt.ylabel('Absolute error in km/s')
plt.yscale('log')
plt.title('Absolute velocity error using different delta t')
plt.legend()
plt.show()


delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    df['v rel error']= df['v abs error'] / df['velocity norm']
    plt.plot(df['time'], df['v rel error'], label='delta t: 1e'+ str(exponent))
    delta_t /= 10.
    exponent -= 1

plt.xlabel('t in s')
plt.ylabel('Relative error')
plt.yscale('log')
plt.title('Relative velocity error using different delta t')
plt.legend()
plt.show()

vel_df['E kinetic']= 0.5 * vel_df['vel_total norm'] * vel_df['vel_total norm']
vel_df['E potential']= 1/3.986004407799724e+5 * vel_df['position norm']
vel_df["E total"]= vel_df['E kinetic'] + vel_df['E potential']

delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    df['E kinetic']= 0.5 * df['velocity norm'] * df['velocity norm']
    df['E potential']= 1/3.986004407799724e+5 * df['position norm']
    df["E total"]= df['E kinetic'] + df['E potential']
    df['E total abs error'] = list(map(abs, vel_df['E total'] - df['E total']))
    plt.plot(df['time'], df['E total abs error'], label='delta t: 1e'+ str(exponent))
    delta_t /= 10.
    exponent -= 1

plt.xlabel('t in s')
plt.ylabel('Absolute error in %calculate%')
plt.yscale('log')
plt.title('Absolute energy error using different delta t')
plt.legend()
plt.show()

delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    df['E total rel error']= df['E total abs error'] / df['E total']
    plt.plot(df['time'], df['E total rel error'], label='delta t: 1e'+ str(exponent))
    delta_t /= 10.
    exponent -= 1

plt.xlabel('t in s')
plt.ylabel('Relative error')
plt.yscale('log')
plt.title('Relative energy error using different delta t')
plt.legend()
plt.show()


vel_df = pd.read_csv('output/raw/heyoka_delta_t_short_ld_sim.csv')
vel_delta_t_list = [pd.read_csv('output/raw/delta_t_10_short_1.csv'),
                    pd.read_csv('output/raw/delta_t_10_short_2.csv'),
                    pd.read_csv('output/raw/delta_t_10_short_3.csv'),
                    pd.read_csv('output/raw/delta_t_10_short_4.csv'),
                    pd.read_csv('output/raw/delta_t_10_short_5.csv'),
                    pd.read_csv('output/raw/delta_t_10_short_6.csv'),
                    pd.read_csv('output/raw/delta_t_10_short_7.csv'),
                    pd.read_csv('output/raw/delta_t_10_short_8.csv'),
                    pd.read_csv('output/raw/delta_t_10_short_9.csv')]
plt.plot(vel_df['time'], vel_df['vel_total norm'], label = 'Heyoka')

delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    plt.plot(df['time'], df['velocity norm'], label='delta t: 10^(' + str(exponent) + ')')
    delta_t /= 10.
    exponent -= 1

plt.xlabel('t in s')
plt.ylabel('||v|| in km/s')
plt.title('Velocity using different delta t')
plt.legend()
plt.show()

delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    df['v abs error']=list(map(abs, vel_df['vel_total norm'] - df['velocity norm']))
    plt.plot(df['time'], df['v abs error'], label='delta t: 10^(' + str(exponent) + ')')
    delta_t /= 10.
    exponent -= 1

plt.xlabel('t in s')
plt.ylabel('Absolute error in km/s')
plt.yscale('log')
plt.title('Absolute velocity error using different delta t')
plt.legend()
plt.show()


delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    df['v rel error']= df['v abs error'] / df['velocity norm']
    plt.plot(df['time'], df['v rel error'], label='delta t: 10^(' + str(exponent) + ')')
    delta_t /= 10.
    exponent -= 1

plt.xlabel('t in s')
plt.ylabel('Relative error')
plt.yscale('log')
plt.title('Relative velocity error using different delta t')
plt.legend()
plt.show()

vel_df['E kinetic']= 0.5 * vel_df['vel_total norm'] * vel_df['vel_total norm']
vel_df['E potential']= 1/3.986004407799724e+5 * vel_df['position norm']
vel_df["E total"]= vel_df['E kinetic'] + vel_df['E potential']

delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    df['E kinetic']= 0.5 * df['velocity norm'] * df['velocity norm']
    df['E potential']= 1/3.986004407799724e+5 * df['position norm']
    df["E total"]= df['E kinetic'] + df['E potential']
    df['E total abs error'] = list(map(abs, vel_df['E total'] - df['E total']))
    plt.plot(df['time'], df['E total abs error'], label='delta t: 10^(' + str(exponent) + ')')
    delta_t /= 10.
    exponent -= 1

plt.xlabel('t in s')
plt.ylabel('Absolute error in %calculate%')
plt.yscale('log')
plt.title('Absolute energy error using different delta t')
plt.legend()
plt.show()

delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    df['E total rel error']= df['E total abs error'] / df['E total']
    plt.plot(df['time'], df['E total rel error'], label='delta t: 10^(' + str(exponent) + ')')
    delta_t /= 10.
    exponent -= 1

plt.xlabel('t in s')
plt.ylabel('Relative error')
plt.yscale('log')
plt.title('Relative energy error using different delta t')
plt.legend()
plt.show()


vel_df = pd.read_csv('output/raw/heyoka_delta_t_short_ld_sim.csv')
vel_delta_t_list = [pd.read_csv('output/raw/delta_t_2_short_1.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_2.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_3.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_4.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_5.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_6.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_7.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_8.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_9.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_10.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_11.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_12.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_13.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_14.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_15.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_16.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_17.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_18.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_19.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_20.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_21.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_22.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_23.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_24.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_25.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_26.csv'),
                    pd.read_csv('output/raw/delta_t_2_short_27.csv')]
plt.plot(vel_df['time'], vel_df['vel_total norm'], label = 'Heyoka')

delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    plt.plot(df['time'], df['velocity norm'], label='delta t: 2^(' + str(exponent) + ')')
    delta_t /= 10.
    exponent -= 1

plt.xlabel('t in s')
plt.ylabel('||v|| in km/s')
plt.title('Velocity using different delta t')
plt.legend()
plt.show()

delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    df['v abs error']=list(map(abs, vel_df['vel_total norm'] - df['velocity norm']))
    plt.plot(df['time'], df['v abs error'], label='delta t: 2^(' + str(exponent) + ')')
    delta_t /= 10.
    exponent -= 1

plt.xlabel('t in s')
plt.ylabel('Absolute error in km/s')
plt.yscale('log')
plt.title('Absolute velocity error using different delta t')
plt.legend()
plt.show()


delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    df['v rel error']= df['v abs error'] / df['velocity norm']
    plt.plot(df['time'], df['v rel error'], label='delta t: 2^(' + str(exponent) + ')')
    delta_t /= 10.
    exponent -= 1

plt.xlabel('t in s')
plt.ylabel('Relative error')
plt.yscale('log')
plt.title('Relative velocity error using different delta t')
plt.legend()
plt.show()

vel_df['E kinetic']= 0.5 * vel_df['vel_total norm'] * vel_df['vel_total norm']
vel_df['E potential']= 1/3.986004407799724e+5 * vel_df['position norm']
vel_df["E total"]= vel_df['E kinetic'] + vel_df['E potential']

delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    df['E kinetic']= 0.5 * df['velocity norm'] * df['velocity norm']
    df['E potential']= 1/3.986004407799724e+5 * df['position norm']
    df["E total"]= df['E kinetic'] + df['E potential']
    df['E total abs error'] = list(map(abs, vel_df['E total'] - df['E total']))
    plt.plot(df['time'], df['E total abs error'], label='delta t: 2^(' + str(exponent) + ')')
    delta_t /= 10.
    exponent -= 1

plt.xlabel('t in s')
plt.ylabel('Absolute error in %calculate%')
plt.yscale('log')
plt.title('Absolute energy error using different delta t')
plt.legend()
plt.show()

delta_t = 1.
exponent = 0
for df in vel_delta_t_list:
    df['E total rel error']= df['E total abs error'] / df['E total']
    plt.plot(df['time'], df['E total rel error'], label='delta t: 2^(' + str(exponent) + ')')
    delta_t /= 10.
    exponent -= 1

plt.xlabel('t in s')
plt.ylabel('Relative error')
plt.yscale('log')
plt.title('Relative energy error using different delta t')
plt.legend()
plt.show()