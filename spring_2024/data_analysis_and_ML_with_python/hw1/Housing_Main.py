import pandas as pd

import matplotlib.pyplot as plt
import seaborn as sns

from mpl_toolkits.mplot3d import Axes3D
from matplotlib.colors import LinearSegmentedColormap, BoundaryNorm

df = pd.read_csv('housing_data.csv')
print(df)

df.info()

nan_check = df.isna().any()
print(nan_check)

loc_check = df.loc[df.duplicated()]
print(loc_check)

data_copy = df.copy()

#製作三個地區的df
print('DataFrame....')
df = pd.DataFrame(data_copy)
Rural_df = df[df['Location'] == 'Rural']
Suburb_df = df[df['Location'] == 'Suburb']
City_Center_df = df[df['Location'] == 'City Center']
print(Rural_df," \n", Suburb_df, "\n", City_Center_df)

#打印三個地區的describe
print(" \n[INFO] Rural describe...")
x = Rural_df.describe()
print(x)
print(" \n[INFO] Suburb describe...")
y = Suburb_df.describe()
print(y)
print(" \n[INFO] City Center describe...")
z = City_Center_df.describe()
print(z)

#視覺化三個地區的describe
fig, axs = plt.subplots(2, 3, figsize=(15, 10))
sns.boxplot(y='Area', hue='Location', data=df, ax=axs[0, 0])
sns.boxplot(y='No. of Rooms', hue='Location', data=df, ax=axs[0, 1])
sns.boxplot(y='No. of Bathrooms', hue='Location', data=df, ax=axs[0, 2])
sns.boxplot(y='Miles (dist. between school and house)', hue='Location', data=df, ax=axs[1, 0])
sns.boxplot(y='Rent Price per Month', hue='Location', data=df, ax=axs[1, 1])
sns.boxplot(y='Sell Price', hue='Location', data=df, ax=axs[1, 2])

plt.tight_layout()
plt.show()

#回答Q3 部分
filter_Rural_df = Rural_df[Rural_df['Miles (dist. between school and house)'] <= 50]
filter_Suburb_df = Suburb_df[Suburb_df['Miles (dist. between school and house)'] <= 50]
filter_City_Center_df = City_Center_df[City_Center_df['Miles (dist. between school and house)'] <= 50]

filter2_Rural_df = filter_Rural_df[Rural_df['Rent Price per Month'] <= 10000]
filter2_Suburb_df = filter_Suburb_df[Suburb_df['Rent Price per Month'] <= 10000]
filter2_City_Center_df = filter_City_Center_df[City_Center_df['Rent Price per Month'] <= 10000]

#顏色 藍 橘 綠
my_color = ['#1f77b4', '#ff7f0e', '#2ca02c']

fig = plt.figure(figsize=(10, 5))

ax1 = fig.add_subplot(131, projection='3d')
ax1.scatter(filter2_Rural_df['Area'], filter2_Rural_df['Miles (dist. between school and house)'], filter2_Rural_df['Rent Price per Month'], color=my_color[0])
ax1.set_title('Rural')
ax1.set_xlabel('Area')
ax1.set_xticks([1000, 2000, 3000])
ax1.set_ylabel('Miles (dist. between school and house)')
ax1.set_yticks([10, 20, 30, 50])
ax1.set_zlabel('Rent Price per Month')
ax1.set_zticks([10000, 9000, 8000, 7000])

ax2 = fig.add_subplot(132, projection='3d')
ax2.scatter(filter2_Suburb_df['Area'], filter2_Suburb_df['Miles (dist. between school and house)'], filter2_Suburb_df['Rent Price per Month'], color=my_color[1])
ax2.set_title('Suburb')
ax2.set_xlabel('Area')
ax2.set_xticks([1000, 2000, 3000])
ax2.set_ylabel('Miles (dist. between school and house)')
ax2.set_yticks([10, 20, 30, 50])
ax2.set_zlabel('Rent Price per Month')
ax2.set_zticks([10000, 9000, 8000, 7000])

ax3 = fig.add_subplot(133, projection='3d')
ax3.scatter(filter2_City_Center_df['Area'], filter2_City_Center_df['Miles (dist. between school and house)'], filter2_City_Center_df['Rent Price per Month'], color=my_color[2])
ax3.set_title('City Center')
ax3.set_xlabel('Area')
ax3.set_xticks([1000, 2000, 3000])
ax3.set_ylabel('Miles (dist. between school and house)')
ax3.set_yticks([10, 20, 30, 50])
ax3.set_zlabel('Rent Price per Month')
ax3.set_zticks([10000, 9000, 8000, 7000])

plt.tight_layout(pad=3)
plt.show()

print(" \n[INFO] City Center 符合租房條件的房子...")
print(filter2_City_Center_df)
print(" \n[INFO] Suburb 符合租房條件的房子...")
print(filter2_Suburb_df)
print(" \n[INFO] Rural 符合租房條件的房子...")
print(filter2_Rural_df)

#回答Q4
filter3_Rural_df = Rural_df[Rural_df['Miles (dist. between school and house)'] <= 50]
filter3_Suburb_df = Suburb_df[Suburb_df['Miles (dist. between school and house)'] <= 50]
filter3_City_Center_df = City_Center_df[City_Center_df['Miles (dist. between school and house)'] <= 50]

filter4_Rural_df = filter3_Rural_df[Rural_df['Area'] >= 2300]
filter4_Suburb_df = filter3_Suburb_df[Suburb_df['Area'] >= 2300]
filter4_City_Center_df = filter3_City_Center_df[City_Center_df['Area'] >= 2300]

filter5_Rural_df = filter4_Rural_df[Rural_df['No. of Rooms'] >= 2]
filter5_Suburb_df = filter4_Suburb_df[Suburb_df['No. of Rooms'] >= 2]
filter5_City_Center_df = filter4_City_Center_df[City_Center_df['No. of Rooms'] >= 2]

fig1 = plt.figure(figsize=(5, 5))
ax1 = fig1.add_subplot(111, projection='3d')
sc1 = ax1.scatter(filter5_Rural_df['Miles (dist. between school and house)'],
                  filter5_Rural_df['No. of Rooms'],
                  filter5_Rural_df['Area'],
                  c=filter5_Rural_df['Sell Price'], cmap='rainbow')
ax1.set_title('Rural')
ax1.set_xlabel('Miles (dist. between school and house)')
ax1.set_xticks([10, 30, 50])
ax1.set_ylabel('No. of Rooms')
ax1.set_yticks([2, 3])
ax1.set_zlabel('Area')
ax1.set_zticks([2300, 2600, 3000])
cbar1 = fig1.colorbar(sc1)
cbar1.set_label('Sell Price')

fig2 = plt.figure(figsize=(5, 5))
ax2 = fig2.add_subplot(111, projection='3d')
sc2 = ax2.scatter(filter5_Suburb_df['Miles (dist. between school and house)'],
                  filter5_Suburb_df['No. of Rooms'],
                  filter5_Suburb_df['Area'],
                  c=filter5_Suburb_df['Sell Price'], cmap='rainbow')
ax2.set_title('Suburb')
ax2.set_xlabel('Miles (dist. between school and house)')
ax2.set_xticks([10, 30, 50])
ax2.set_ylabel('No. of Rooms')
ax2.set_yticks([2, 3])
ax2.set_zlabel('Area')
ax2.set_zticks([2300, 2600, 3000])
cbar2 = fig2.colorbar(sc2)
cbar2.set_label('Sell Price')

fig3 = plt.figure(figsize=(5, 5))
ax3 = fig3.add_subplot(111, projection='3d')
sc3 = ax3.scatter(filter5_City_Center_df['Miles (dist. between school and house)'],
                  filter5_City_Center_df['No. of Rooms'],
                  filter5_City_Center_df['Area'],
                  c=filter5_City_Center_df['Sell Price'], cmap='rainbow')
ax3.set_title('City Center')
ax3.set_xlabel('Miles (dist. between school and house)')
ax3.set_xticks([10, 30, 50])
ax3.set_ylabel('No. of Rooms')
ax3.set_yticks([2, 3])
ax3.set_zlabel('Area')
ax3.set_zticks([2300, 2600, 3000])
cbar3 = fig3.colorbar(sc3)
cbar3.set_label('Sell Price')

plt.tight_layout(pad=3)
plt.show()

print(" \n[INFO] City Center 符合買房條件的房子...")
print(filter5_City_Center_df)
print(" \n[INFO] Suburb 符合買房條件的房子...")
print(filter5_Suburb_df)
print(" \n[INFO] Rural 符合買房條件的房子...")
print(filter5_Rural_df)

#回答Q5 高房價
filter6_Rural_df = Rural_df[Rural_df['Sell Price'] >= 7e+07]
filter6_Suburb_df = Suburb_df[Suburb_df['Sell Price'] >= 7e+07]
filter6_City_Center_df = City_Center_df[City_Center_df['Sell Price'] >= 7e+07]

boundaries = [7e+07, 7.5e+07, 7.8e+07, 8e+07]
colors = ['gray', 'blue', 'red']

cmap = LinearSegmentedColormap.from_list('custom_cmap', colors)
norm = BoundaryNorm(boundaries, cmap.N, clip=True)

def plot_3d_scatter(ax, df, title, cmap, norm):
    sc = ax.scatter(df['Miles (dist. between school and house)'],
                    df['No. of Rooms'],
                    df['Area'],
                    c=df['Sell Price'], cmap=cmap, norm=norm)
    ax.set_title(title)
    ax.set_xlabel('Miles (dist. between school and house)')
    ax.set_ylabel('No. of Rooms')
    ax.set_yticks([1, 2, 3])
    ax.set_zlabel('Area')
    ax.set_zticks([1000, 2000, 3000])
    cbar = fig.colorbar(sc, ax=ax, boundaries=boundaries[:-1], ticks=boundaries[:-1])
    cbar.set_label('Sell Price')
    return sc

fig = plt.figure(figsize=(5, 5))
ax = fig.add_subplot(111, projection='3d')
plot_3d_scatter(ax, Rural_df, 'Rural', cmap, norm)

fig = plt.figure(figsize=(5, 5))
ax = fig.add_subplot(111, projection='3d')
plot_3d_scatter(ax, Suburb_df, 'Suburb', cmap, norm)

fig = plt.figure(figsize=(5, 5))
ax = fig.add_subplot(111, projection='3d')
plot_3d_scatter(ax, City_Center_df, 'City Center', cmap, norm)

plt.tight_layout()
plt.show()

#回答Q5 低房價
filter7_Rural_df = Rural_df[Rural_df['Sell Price'] <= 9.99e+06]
filter7_Suburb_df = Suburb_df[Suburb_df['Sell Price'] <= 9.99e+06]
filter7_City_Center_df = City_Center_df[City_Center_df['Sell Price'] <= 9.99e+06]

boundaries = [6e+06, 7e+06, 1e+07]
colors = [my_color[0], my_color[1]]

cmap = LinearSegmentedColormap.from_list('custom_cmap', colors)
norm = BoundaryNorm(boundaries, cmap.N, clip=True)

def plot_3d_scatter(ax, df, title, cmap, norm):
    sc = ax.scatter(df['Miles (dist. between school and house)'],
                    df['No. of Rooms'],
                    df['Area'],
                    c=df['Sell Price'], cmap=cmap, norm=norm)
    ax.set_title(title)
    ax.set_xlabel('Miles (dist. between school and house)')
    ax.set_ylabel('No. of Rooms')
    ax.set_yticks([1, 2, 3])
    ax.set_zlabel('Area')
    ax.set_zticks([1000, 2000, 3000])
    cbar = fig.colorbar(sc, ax=ax, boundaries=boundaries[:-1], ticks=boundaries[:-1])
    cbar.set_label('Sell Price')
    return sc

fig = plt.figure(figsize=(5, 5))
ax = fig.add_subplot(111, projection='3d')
plot_3d_scatter(ax, Rural_df, 'Rural', cmap, norm)

fig = plt.figure(figsize=(5, 5))
ax = fig.add_subplot(111, projection='3d')
plot_3d_scatter(ax, Suburb_df, 'Suburb', cmap, norm)

fig = plt.figure(figsize=(5, 5))
ax = fig.add_subplot(111, projection='3d')
plot_3d_scatter(ax, City_Center_df, 'City Center', cmap, norm)

plt.tight_layout()
plt.show()

#回答Q5 高房租
filter8_Rural_df = Rural_df[Rural_df['Rent Price per Month'] >= 16630]
filter8_Suburb_df = Suburb_df[Suburb_df['Rent Price per Month'] >= 16630]
filter8_City_Center_df = City_Center_df[City_Center_df['Rent Price per Month'] >= 16630]

boundaries = [16000, 18000, 19000, 20000]
colors = ['gray', 'blue', 'red']

cmap = LinearSegmentedColormap.from_list('custom_cmap', colors)
norm = BoundaryNorm(boundaries, cmap.N, clip=True)

def plot_3d_scatter(ax, df, title, cmap, norm):
    sc = ax.scatter(df['Miles (dist. between school and house)'],
                    df['No. of Rooms'],
                    df['Area'],
                    c=df['Rent Price per Month'], cmap=cmap, norm=norm)
    ax.set_title(title)
    ax.set_xlabel('Miles (dist. between school and house)')
    ax.set_ylabel('No. of Rooms')
    ax.set_yticks([1, 2, 3])
    ax.set_zlabel('Area')
    ax.set_zticks([1000, 2000, 3000])
    cbar = fig.colorbar(sc, ax=ax, boundaries=boundaries[:-1], ticks=boundaries[:-1])
    cbar.set_label('Rent Price per Month')
    return sc

fig = plt.figure(figsize=(5, 5))
ax = fig.add_subplot(111, projection='3d')
plot_3d_scatter(ax, Rural_df, 'Rural', cmap, norm)

fig = plt.figure(figsize=(5, 5))
ax = fig.add_subplot(111, projection='3d')
plot_3d_scatter(ax, Suburb_df, 'Suburb', cmap, norm)

fig = plt.figure(figsize=(5, 5))
ax = fig.add_subplot(111, projection='3d')
plot_3d_scatter(ax, City_Center_df, 'City Center', cmap, norm)

plt.tight_layout()
plt.show()

#回答Q5 低房租
filter9_Rural_df = Rural_df[Rural_df['Rent Price per Month'] <= 8000]
filter9_Suburb_df = Suburb_df[Suburb_df['Rent Price per Month'] <= 8000]
filter9_City_Center_df = City_Center_df[City_Center_df['Rent Price per Month'] <= 8000]

boundaries = [6000, 6500, 7000, 8000]
colors = ['red', 'blue', 'gray']

cmap = LinearSegmentedColormap.from_list('custom_cmap', colors)
norm = BoundaryNorm(boundaries, cmap.N, clip=True)

def plot_3d_scatter(ax, df, title, cmap, norm):
    sc = ax.scatter(df['Miles (dist. between school and house)'],
                    df['No. of Rooms'],
                    df['Area'],
                    c=df['Rent Price per Month'], cmap=cmap, norm=norm)
    ax.set_title(title)
    ax.set_xlabel('Miles (dist. between school and house)')
    ax.set_ylabel('No. of Rooms')
    ax.set_yticks([1, 2, 3])
    ax.set_zlabel('Area')
    ax.set_zticks([1000, 2000, 3000])
    cbar = fig.colorbar(sc, ax=ax, boundaries=boundaries[:-1], ticks=boundaries[:-1])
    cbar.set_label('Rent Price per Month')
    return sc

fig = plt.figure(figsize=(5, 5))
ax = fig.add_subplot(111, projection='3d')
plot_3d_scatter(ax, Rural_df, 'Rural', cmap, norm)

fig = plt.figure(figsize=(5, 5))
ax = fig.add_subplot(111, projection='3d')
plot_3d_scatter(ax, Suburb_df, 'Suburb', cmap, norm)

fig = plt.figure(figsize=(5, 5))
ax = fig.add_subplot(111, projection='3d')
plot_3d_scatter(ax, City_Center_df, 'City Center', cmap, norm)

plt.tight_layout()
plt.show()