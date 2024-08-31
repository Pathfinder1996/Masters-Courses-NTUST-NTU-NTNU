"""
Q1-a:
代碼首先讀取CSV文件到DataFrame df 然後逐行遍歷df 使用一個字典data_dict根據Group和Category記錄每個Category的值
代碼遍歷這個字典 構建一系列list 這些list記錄了每個Group是否包含每個Category A到E
基於這些list 創建一個新的DataFrame df_new 其中包含每個Group的Category存在情況 1跟0標記以及每個Category
最後，代碼計算並打印出沒有Category D的Group的數量。
"""

#Q1-b
import pandas as pd

df = pd.read_csv("question.csv")

#使用get_dummies轉換Category列為0跟1
category_dummies = pd.get_dummies(df['Category'])

#原始DataFrame與轉換後的dummies DataFrame合併
df_combined = pd.concat([df, category_dummies], axis=1)

#按Group分組 並對每個Category求和 得到Group中各Category的存在次數
df_grouped = df_combined.groupby('Group').sum()

#計算沒有Category D 的Group的數量
result = (df_grouped['D'] == 0).sum()

print(result)

