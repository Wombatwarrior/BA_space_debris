import pandas as pd
import plotly.express as px
import matplotlib.pyplot as plt

acc_df = pd.read_csv('../test_files/test_output_acc.csv')
acc_df1 = acc_df[acc_df.index % 3 == 0]
acc_df2 = acc_df[acc_df.index % 3 == 1]
acc_df3 = acc_df[acc_df.index % 3 == 2]
plt.plot(acc_df3['time'], acc_df1['acc_total norm'], label = 'TOTAL')
plt.xlabel('time in s')
plt.ylabel('|a| in kms^(-2)')
# Set a title of the current axes.
plt.title('Acceleration of particle 1')
plt.legend()
plt.show()

plt.plot(acc_df2['time'], acc_df1['acc_j2 norm'], label = 'J2')
plt.xlabel('time in s')
plt.ylabel('|a| in kms^(-2)')
# Set a title of the current axes.
plt.title('Acceleration of particle 1')
plt.legend()
plt.show()

plt.plot(acc_df3['time'], acc_df1['acc_c22 norm'], label = 'C22')
plt.xlabel('time in s')
plt.ylabel('|a| in kms^(-2)')
# Set a title of the current axes.
plt.title('Acceleration of particle 1')
plt.legend()
plt.show()

plt.plot(acc_df1['time'], acc_df1['acc_s22 norm'], label = 'S22')
plt.xlabel('time in s')
plt.ylabel('|a| in kms^(-2)')
# Set a title of the current axes.
plt.title('Acceleration of particle 1')
plt.legend()
plt.show()

plt.plot(acc_df2['time'], acc_df1['acc_sol norm'], label = 'SOL')
plt.xlabel('time in s')
plt.ylabel('|a| in kms^(-2)')
# Set a title of the current axes.
plt.title('Acceleration of particle 1')
plt.legend()
plt.show()

plt.plot(acc_df3['time'], acc_df1['acc_lun norm'], label = 'LUN')
plt.xlabel('time in s')
plt.ylabel('|a| in kms^(-2)')
# Set a title of the current axes.
plt.title('Acceleration of particle 1')
plt.legend()
plt.show()

plt.plot(acc_df1['time'], acc_df1['acc_srp norm'], label = 'SRP')
plt.xlabel('time in s')
plt.ylabel('|a| in kms^(-2)')
# Set a title of the current axes.
plt.title('Acceleration of particle 1')
plt.legend()
plt.show()

plt.plot(acc_df2['time'], acc_df1['acc_drag norm'], label = 'DRAG')
plt.xlabel('time in s')
plt.ylabel('|a| in kms^(-2)')
# Set a title of the current axes.
plt.title('Acceleration of particle 1')
plt.legend()
plt.show()
