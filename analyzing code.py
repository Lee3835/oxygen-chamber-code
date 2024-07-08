!pip install matplotlib
!pip install numpy
import matplotlib.pyplot as plt
import numpy as np
directory = './data.txt'
read_data = np.genfromtxt(directory, delimiter=',')
t = []
x1 = []
x2 = []
x3 = []
m1 = 0
m2 = 0
m3 = 0
for i in read_data:
    t.append(i[0])
    x1.append(i[1])
    x2.append(i[2])
    x3.append(i[3])
    m1 = max(m1, i[1])
    m2 = max(m2, i[2])
    m3 = max(m3, i[3])
plt.figure(1)
plt.plot(t, x1)
plt.xlabel('time(sec)')
plt.ylabel('concentration(%)')
plt.ylim([0, m1 * 1.2])
plt.figure(2)
plt.plot(t, x2)
plt.xlabel('time(sec)')
plt.ylabel('humidity(%)')
plt.ylim([0, m2 * 1.2])
plt.figure(3)
plt.plot(t, x3)
plt.xlabel('time(sec)')
plt.ylabel('temperature(°C)')
plt.ylim([0, m3 * 1.2])

plt.show()
