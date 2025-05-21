import numpy as np

# 分点
x = np.linspace(0, 20, 21)
# 深度数据
h = np.array([9.01, 8.96, 7.96, 7.96, 8.02, 9.05, 10.13, 11.18, 12.26, 13.28, 13.32, 12.61, 11.29, 10.22, 9.15, 7.95, 7.95, 8.86, 9.81, 10.80, 10.93])

# 计算相邻两点间的水平距离
dx = x[1] - x[0]

# 利用弧长公式的近似，使用梯形公式计算弧长
length = 0
for i in range(len(x) - 1):
    # 计算相邻两点的垂直距离变化
    dy = h[i + 1] - h[i]
    # 弧长近似公式：sqrt(dx**2 + dy**2)
    segment_length = np.sqrt(dx ** 2 + dy ** 2)
    length += segment_length

print("通过这条河沟所需光缆长度的近似值为:", length)