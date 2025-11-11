import numpy as np

# 提供的实测数据
Delta_R = [-200,-180,-160,-140,-120,-100,-80,-60,-40,-20,0,20,40,60,80,100,120,140,160,180,200]
Ug_measured = [111.1,98.9,86.96,75.271,63.834,52.627,41.665,30.927,20.41,10.106,0,9.895,19.6,29.117,38.45,47.61,56.59,65.41,74.06,82.553,90.892]
# 给定的电压和电阻值
R0 = 1000  # 设定的电阻值 R0 = 1000Ω
Us = 2000 # 电压 Us = 2V

# 计算 delta 和对应的 Ug 理论值
delta = np.array(Delta_R) / R0  # 计算 delta = ΔR / R0
Ug_theory = Us / 4 * delta  # 计算 Ug = Us / 4 * delta

# 计算 Ug 理论的绝对值
Ug_theory_abs = np.abs(Ug_theory)

# 计算误差并转换为百分比
error_percent = np.abs(Ug_theory_abs - Ug_measured) / Ug_theory_abs * 100

# 输出理论值和误差百分比
print("理论值 Ug：", Ug_theory_abs)
print("每个点的误差（百分比）：", error_percent)
