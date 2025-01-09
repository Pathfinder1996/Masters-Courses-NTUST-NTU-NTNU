import numpy as np
import pandas as pd

import matplotlib.pyplot as plt

df = pd.read_csv('family_data.csv')
print(df)

df.info()

nan_check = df.isna().any()
print(nan_check)

loc_check = df.loc[df.duplicated()]
print(loc_check)

data_copy = df.copy()

#檢查df收入跟花費有無0或負值
filter_data_copy = data_copy[data_copy['Income'] <= -1]
print('\n[INFO] 收入有無負值\n', filter_data_copy)
filter2_data_copy = data_copy[data_copy['Spend'] <= -1]
print('\n[INFO] 花費有無負值\n', filter2_data_copy)

#只有小孩或是只有大人的df 
child_df = df[df['Member'].str.contains('Child')]
adult_df = df[df['Member'].str.contains('Adult')]

#檢查小孩收入跟花費有無異常
child_filter = child_df[child_df['Income'] >= 1]
print('\n[INFO] 小孩收入有無 > 1\n', child_filter)
child_filter2 = child_df[child_df['Spend'] <= 1]
print('\n[INFO] 小孩花費有無 < 1\n', child_filter2)

#檢查成人收入跟花費有無異常
adult_filter = adult_df[adult_df['Income'] <= 1]
print('\n[INFO] 成人收入有無 < 1\n', adult_filter)
adult_filter2 = adult_df[adult_df['Spend'] <= 1]
print('\n[INFO] 成人花費有無 < 1\n', adult_filter2)

df = pd.DataFrame(data_copy)

#df新增欄位 1.總收入 2.總花費 3.收入-花費  
df['Total Income'] = df.groupby('Family')['Income'].transform('sum')
df['Total Spend'] = df.groupby('Family')['Spend'].transform('sum')
df['Income Minus Spend'] = df['Total Income'] - df['Total Spend']

#檢查有無收入減去花費會小於1
minus_filter = df[df['Income Minus Spend'] <= 1]
print(minus_filter)

#另建一個df2 看家庭總收入+花費
only_family_df = ['Family', 'Total Income', 'Total Spend', 'Income Minus Spend']
only_family_df2 = df[only_family_df].copy()
df2 = pd.DataFrame(only_family_df2)
print(only_family_df2)

#砍掉新建df2的重複行 只會剩下100行(100個家庭)
check1 = df2.loc[df2.duplicated()]
drop1 = df2.drop_duplicates(inplace=True)
print(df2)

#顏色 藍 橘 綠 粉 有點綠 亮天藍
my_color = ['#1f77b4', '#ff7f0e', '#2ca02c', '#F4BFBF', '#9EB23B', '#87CEFA'] 

#回答Q1 最高收入家庭
x = df2.groupby(['Family'])['Total Income'].max().reset_index().sort_values(by='Total Income', ascending=False).head(5)
print('\n[INFO] 收入最多的前五家庭\n', x)

max_income = df2.sort_values(by='Total Income', ascending=False).head(5)

plt.figure(figsize=(10, 8))
bar_width = 0.20
r1 = np.arange(len(max_income))
r2 = [x + bar_width for x in r1]
plt.bar(r1, max_income['Total Income'], color=my_color[5], width=bar_width, edgecolor='grey', label='Total Income')
plt.bar(r2, max_income['Total Spend'], color=my_color[1], width=bar_width, edgecolor='grey', label='Total Spend')
plt.plot(max_income['Family'], max_income['Income Minus Spend'], color='red', marker='o', label='Income Minus Spend')

for i, txt in enumerate(max_income['Income Minus Spend']):
    plt.text(r1[i], max_income['Total Income'].iloc[i], f"{max_income['Total Income'].iloc[i]:,.0f}", ha='center', va='bottom', fontsize=10)
    plt.text(r1[i], txt, f"{txt:,.0f}", ha='left', va='bottom', fontsize=8)

plt.legend()
plt.title('Family', fontweight='bold')
plt.xticks([r + bar_width for r in range(len(r1))], max_income['Family'])
plt.ylabel('Dollar', fontweight='bold')
plt.show()

#回答Q1 最低收入家庭
y = df2.groupby(['Family'])['Total Income'].min().reset_index().sort_values(by='Total Income', ascending=True).head(5)
print('\n[INFO] 收入最少的前五家庭\n', y)

min_income = df2.sort_values(by='Total Income', ascending=True).head(5)

plt.figure(figsize=(10, 8))
bar_width = 0.20
r1 = np.arange(len(max_income))
r2 = [x + bar_width for x in r1]
plt.bar(r1, min_income['Total Income'], color=my_color[3], width=bar_width, edgecolor='grey', label='Total Income')
plt.bar(r2, min_income['Total Spend'], color=my_color[4], width=bar_width, edgecolor='grey', label='Total Spend')
plt.plot(min_income['Family'], min_income['Income Minus Spend'], color='red', marker='o', label='Income Minus Spend')

for i, txt in enumerate(min_income['Income Minus Spend']):
    plt.text(r1[i], min_income['Total Income'].iloc[i], f"{min_income['Total Income'].iloc[i]:,.0f}", ha='center', va='bottom', fontsize=10)
    plt.text(r1[i], txt, f"{txt:,.0f}", ha='left', va='bottom', fontsize=8)

plt.legend()
plt.title('Family', fontweight='bold')
plt.xticks([r + bar_width for r in range(len(r1))], min_income['Family'])
plt.ylabel('Dollar', fontweight='bold')
plt.show()

#回答Q2 有無入不敷出的家庭
filter1 = df2[df2['Total Spend'] > df2['Total Income']]
print('\n[INFO] 有無入不敷出的家庭\n', filter1)

#回答Q3 有無單親或無子女家庭
#新增大人小孩欄位 回傳布林值
df['Adult'] = df['Member'].str.contains('Adult')
df['Child'] = df['Member'].str.contains('Child')
print(df)

#計算家庭成員數量
member_count = df.groupby('Family').agg({'Adult': 'sum', 'Child': 'sum'})
print(member_count)
df3 = pd.DataFrame(member_count)

#單親家庭
filter_single_parent = df3[df3['Adult'] <= 1].reset_index()
print('\n[INFO] 單親家庭\n', filter_single_parent, '\n\n 資料形狀:', filter_single_parent.shape)

#無子女家庭
filter_0_Child = df3[df3['Child'] == 0].reset_index()
print('\n[INFO] 無子女家庭\n', filter_0_Child, '\n\n 資料形狀:', filter_0_Child.shape)
