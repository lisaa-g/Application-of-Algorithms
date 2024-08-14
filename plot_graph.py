import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('results.csv')
df.columns = df.columns.str.strip()

#Exclude rows where Recursive SMM is zero for Recursive SMM plotting
df_filtered_non_zero_recursive = df[df['Recursive SMM'] != 0]

plt.figure(figsize=(10, 6))
plt.plot(df['Matrix Dimension'], df['Classical SMM'], label='Classical SMM', color="hotpink")
plt.plot(df_filtered_non_zero_recursive['Matrix Dimension'], df_filtered_non_zero_recursive['Recursive SMM'], label='Recursive SMM', color="seagreen")
plt.plot(df['Matrix Dimension'], df['Strassen SMM'], label='Strassen SMM', color='royalblue')
plt.xlabel('Matrix Dimension')
plt.ylabel('Time (seconds)')
plt.title('Matrix Multiplication Times')
plt.legend()
plt.grid(True)
plt.show()

start_matrix_size = 512
df_filtered = df[df['Matrix Dimension'] >= start_matrix_size].copy()

#compute time ratios for classical and strassen 
ratios_normal = df_filtered['Classical SMM'].shift(-1) / df_filtered['Classical SMM']
ratios_strassen = df_filtered['Strassen SMM'].shift(-1) / df_filtered['Strassen SMM']

ratios_normal = ratios_normal[:-1]
ratios_strassen = ratios_strassen[:-1]
matrix_sizes_ratio = df_filtered['Matrix Dimension'][:-1]

#plot ratios of time vs matrix dimension
plt.figure(figsize=(10, 6))
plt.plot(matrix_sizes_ratio, ratios_normal, 'o-', label='Classical SMM Ratios', color="hotpink")
plt.plot(matrix_sizes_ratio, ratios_strassen, 'o-', label="Strassen SMM Ratios", color='royalblue')
plt.xlabel('Matrix Dimension')
plt.ylabel('Time Ratio')
plt.title('Time Ratios vs Matrix Dimension (From 512x512 Onwards)')
plt.legend()
plt.grid(True)
plt.show()