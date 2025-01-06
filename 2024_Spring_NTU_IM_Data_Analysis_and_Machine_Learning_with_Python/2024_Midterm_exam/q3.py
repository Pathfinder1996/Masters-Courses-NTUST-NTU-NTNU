import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy import stats

data = {
    "Motor ID": range(1, 11),
    "Lifespan (hours)": [980, 1050, 990, 1100, 1000, 980, 1020, 990, 950, 1020]
}

df = pd.DataFrame(data)
print(df)

#Q3-a 計算電池平均壽命 將每個Lifespan (hours)加總後平均
mean_lifespan = df['Lifespan (hours)'].mean()
print(f"這批電池的平均壽命: {mean_lifespan} 小時")

#Q3-b 繪製電池壽命的直方圖
plt.figure(figsize=(8, 6))
plt.hist(df['Lifespan (hours)'], bins=5, edgecolor='black')
plt.title('Motor Lifespans')
plt.xlabel('Lifespan (hours)')
plt.ylabel('Number of Motors')
plt.grid(axis='y', alpha=0.75)
plt.show()

#Q3-c 計算達到或超過預期壽命1000的Motor有幾顆
max_lifespan = 1000
motors_exceeding_expected = df[df['Lifespan (hours)'] >= max_lifespan].shape[0]
print(f"達到或超過預期壽命的Motor: {motors_exceeding_expected}")

#Q3-d 計算Motor壽命的標準差
std_deviation = df['Lifespan (hours)'].std()
print(f"Motor壽命的標準差為: {std_deviation} 小時")

#Q3-e 檢查是否符合正態分 並根據Shapiro Wilk test的結果來解釋
w, pvalue = stats.shapiro(df['Lifespan (hours)'])

if pvalue > 0.05:
    print(f"Shapiro-Wilk檢驗結果: W={w}, p值={pvalue}")
    print("這批Motor的壽命遵循正態分佈。")
else:
    print(f"Shapiro-Wilk檢驗結果: W={w}, p值={pvalue}")
    print("這批Motor的壽命沒有遵循正態分佈。")

