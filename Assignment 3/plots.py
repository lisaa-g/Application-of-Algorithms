import pandas as pd
import matplotlib.pyplot as plt

# Load the CSV file generated from the C++ code
file_path = "Assignment 3/partA1.csv"
df = pd.read_csv(file_path)
file_path2 = "Assignment 3/partA2.csv"
df2 = pd.read_csv(file_path2)

# Plotting the results
plt.figure(figsize=(10, 6))
plt.plot(df['Number of Sets'], df['Time (microseconds)'], color='magenta', label='Linked List Weighted-Union')
plt.plot(df2['Number of Sets'], df2['Time (microseconds)'], color='skyblue', label='Union-by-Rank and Path Compression')

# Adding labels and title
plt.xlabel('Number of Sets (n)')
plt.ylabel('Average Time (microseconds)')
plt.title('Time Complexity of Disjoint-Set Operations')
plt.legend()
plt.grid(True)

# Show the plot
plt.show()