import numpy as np
import matplotlib.pyplot as plt
from scipy.interpolate import make_interp_spline, Rbf
from statsmodels.nonparametric.smoothers_lowess import lowess

# 设置中文字体
plt.rcParams["font.family"] = ["SimHei", "WenQuanYi Micro Hei", "Heiti TC"]

# 分点
x = np.linspace(0, 20, 21)
# 深度数据
h = np.array([9.01, 8.96, 7.96, 7.96, 8.02, 9.05, 10.13, 11.18, 12.26, 13.28,
              13.32, 12.61, 11.29, 10.22, 9.15, 7.95, 7.95, 8.86, 9.81, 10.80, 10.93])

# 三次样条插值
x_smooth = np.linspace(0, 20, 100)
spline = make_interp_spline(x, h, k=3)
h_spline = spline(x_smooth)

# 绘制对比图
plt.figure(figsize=(12, 8))
plt.scatter(x, h, c='black', label='原始数据点')
plt.plot(x_smooth, h_spline, 'r-', label='三次样条插值')
plt.legend()
plt.grid(True)
plt.title('不同拟合方法对比')
plt.xlabel('位置(米)')
plt.ylabel('深度(米)')
plt.show()
