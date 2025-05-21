import numpy as np
import matplotlib.pyplot as plt

# 分点
x = np.linspace(0, 20, 21)
# 深度数据
h = np.array([9.01, 8.96, 7.96, 7.96, 8.02, 9.05, 10.13, 11.18, 12.26, 13.28, 13.32, 12.61, 11.29, 10.22, 9.15, 7.95, 7.95, 8.86, 9.81, 10.80, 10.93])

# 进行二次多项式拟合
coefficients = np.polyfit(x, h, 2)
# 生成拟合多项式函数
poly_func = np.poly1d(coefficients)

# 生成更多的点用于绘制平滑曲线
x_fine = np.linspace(0, 20, 100)
y_fine = poly_func(x_fine)

# 绘制原始数据点
plt.scatter(x, h, label='Original Data')
# 绘制拟合曲线
plt.plot(x_fine, y_fine, label='Fitted Curve', color='r')
plt.xlabel('Position')
plt.ylabel('Depth')
plt.title('Fitted Curve for Cable Laying')
plt.legend()
plt.show()