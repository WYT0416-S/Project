import numpy as np
import matplotlib.pyplot as plt

# 提供的实测数据
Delta_R = [-1000, -900, -800, -700, -600, -500, -400, -300, -200, -100, 0, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
Ug_measured = [111.1, 98.897, 86.954, 75.267, 63.827, 52.628, 41.664, 30.925, 20.405, 10.097, 0, 9.9, 19.607, 29.124, 38.461, 47.618, 56.6, 65.42, 74.7, 82.57, 90.9]

# 给定的电压和电阻值
R0 = 1000  # 设定的电阻值 R0 = 1000Ω
Us = 2000  # 电压 Us = 2V

# 计算 delta 和对应的 Ug 理论值
delta = np.array(Delta_R) / R0  # 计算 delta = ΔR / R0
Ug_theory = Us / 4 * delta  # 计算 Ug = Us / 4 * delta

# 绘制散点图
plt.figure(figsize=(8, 6))

# 绘制 Ug 实测
plt.scatter(delta, Ug_measured, color='blue', label='实测 $U_g$', marker='o')

# 绘制 Ug 理论
plt.plot(delta, Ug_theory, color='red', label='理论 $U_g$', linestyle='-', marker='x')

# 设置标题和标签
plt.title('实测与理论桥路电压 $U_g$ 与电阻变化量 $\\delta$ 的关系')
plt.xlabel('电阻变化量 $\\delta$ (相对变化量 $\\Delta R/R_0$)')
plt.ylabel('输出电压 $U_g$ (mV)')

# 添加网格线
plt.grid(True)

# 显示图例
plt.legend()

# 保存图表为高分辨率的 PNG 文件（可以打印）
plt.savefig('Ug_vs_delta_plot.png', dpi=300)  # 高分辨率 300 DPI

# 显示图形
plt.show()
