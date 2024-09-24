import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('Assignment 2/bst_results.csv')

plt.figure(figsize=(10, 6))
plt.plot(data['n'], data['average_build_time'])
plt.title('Average Build Time vs Number of Nodes')
plt.xlabel('Number of nodes')
plt.ylabel('Average Build Time (microseconds)')
plt.grid(True)
plt.savefig('Assignment 2/build_time_plot.png')
plt.show()

plt.figure(figsize=(10, 6))
plt.plot(data['n'], data['average_destroy_time'])
plt.title('Average Destroy Time vs Number of Nodes')
plt.xlabel('Number of nodes')
plt.ylabel('Average Destroy Time (microseconds)')
plt.grid(True)
plt.savefig('Assignment 2/destroy_time_plot.png')
plt.show()

plt.figure(figsize=(10, 6))
plt.plot(data['n'], data['average_height'])
plt.title('Average Height vs Number of Nodes')
plt.xlabel('Number of nodes')
plt.ylabel('Average Height')
plt.grid(True)
plt.savefig('Assignment 2/height_plot.png')
plt.show()
