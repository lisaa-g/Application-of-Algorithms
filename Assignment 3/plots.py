import pandas as pd
import matplotlib.pyplot as plt

# Load the CSV file generated from the C++ code
file_path = "Assignment 3/partA1.csv"
df = pd.read_csv(file_path)

# Plotting the results
plt.figure(figsize=(10, 6))
plt.plot(df['Number of Sets'], df['Time (microseconds)'], color='magenta', label='Linked List Weighted-Union')

# Adding labels and title
plt.xlabel('Number of Sets (n)')
plt.ylabel('Time (seconds)')
plt.title('Time Complexity of Disjoint-Set Operations with Linked List (Weighted-Union)')
plt.legend()
plt.grid(True)

# Show the plot
plt.show()
