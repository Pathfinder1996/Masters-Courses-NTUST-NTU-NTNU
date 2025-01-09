import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('titanic.csv')
df_head = df.head(10)

df['Sex_Code'] = df['Sex'].map({'female':1, 'male':0}).astype('int')
df['Sex'] = df['Sex_Code']
df['Age'] = df['Age'].fillna(df['Age'].min())
df_label = df
print("\n[INFO] 將男女標示為0跟1\n", df_label)

X = df[["Pclass", "Sex", "Age", "SibSp", "Parch"]]
y = df["Survived"]

#Q2-a 以下為預測生存的八種模型及其結果以print顯示
# LogisticRegression
print("\n[INFO] 使用LogisticRegression預測")
from sklearn.linear_model import LogisticRegression
clf = LogisticRegression()
clf.fit(X,y)
Jack = clf.predict([[3, 0, 20.0, 0, 0]])
print("Jack", Jack)
Rose = clf.predict([[1, 1, 17.0, 0, 1]])
print("Rose", Rose)

# K-NN
print("\n[INFO] 使用K-NN預測")
from sklearn import neighbors
clf = neighbors.KNeighborsClassifier()
clf.fit(X,y)
Jack = clf.predict([[3, 0, 20.0, 0, 0]])
print("Jack", Jack)
Rose = clf.predict([[1, 1, 17.0, 0, 1]])
print("Rose", Rose)

# SVC
print("\n[INFO] 使用SVC預測")
from sklearn import svm
clf = svm.SVC()
clf.fit(X,y)
Jack = clf.predict([[3, 0, 20.0, 0, 0]])
print("Jack", Jack)
Rose = clf.predict([[1, 1, 17.0, 0, 1]])
print("Rose", Rose)

# Gaussian Naive bayes
print("\n[INFO] 使用Gaussian Naive bayes預測")
from sklearn.naive_bayes import GaussianNB
clf = GaussianNB()
clf.fit(X,y)
Jack = clf.predict([[3, 0, 20.0, 0, 0]])
print("Jack", Jack)
Rose = clf.predict([[1, 1, 17.0, 0, 1]])
print("Rose", Rose)

# Multinomail Naive bayes
print("\n[INFO] 使用Multinomail Naive bayes預測")
from sklearn.naive_bayes import MultinomialNB
clf = MultinomialNB()
clf.fit(X,y)
Jack = clf.predict([[3, 0, 20.0, 0, 0]])
print("Jack", Jack)
Rose = clf.predict([[1, 1, 17.0, 0, 1]])
print("Rose", Rose)

# Decision Tree
print("\n[INFO] 使用Decision Tree預測")
from sklearn import tree
clf = tree.DecisionTreeClassifier()
clf.fit(X,y)
Jack = clf.predict([[3, 0, 20.0, 0, 0]])
print("Jack", Jack)
Rose = clf.predict([[1, 1, 17.0, 0, 1]])
print("Rose", Rose)

# Random Forest
print("\n[INFO] 使用Random Forest預測")
from sklearn.ensemble import RandomForestClassifier
clf = RandomForestClassifier()
clf.fit(X,y)
Jack = clf.predict([[3, 0, 20.0, 0, 0]])
print("Jack", Jack)
Rose = clf.predict([[1, 1, 17.0, 0, 1]])
print("Rose", Rose)

# XGBoost
print("\n[INFO] 使用XGBoost預測")
from xgboost.sklearn import XGBClassifier
clf = XGBClassifier()
clf.fit(X,y)
two = {"Pclass":[3,1], "Sex":[0,1], "Age":[23.0,20.0], "SibSp":[0,0], "Parch":[0,1]}
df1 = pd.DataFrame(two)
Jack = clf.predict(df1.iloc[0:1])
print("Jack", Jack)
Rose = clf.predict(df1.iloc[1:2])
print("Rose", Rose)

"""
Q2-b:
是的 有預測結果不同的模型: SVC 結果為 Jack [0] Rose [0]
其餘7種皆為 Jack [0] Rose [1]
"""

"""
Q2-c:
我覺得造成預測結果不同的可能因有以下幾點
1.模型參數設定 
SVC模型有許多參數可以調整
如果這些參數沒有被適當地調整以適應數據集 可能會導致性能不佳或不同於其他模型的結果

2.資料預處理
如果沒有對特徵進行適當的標準化或正規化 可能會導致模型表現不如預期

3.特徵空間的解釋性
SVC在高維空間中尋找超平面來分隔不同類別的數據
如果特徵之間的關係是非線性的 而SVC的kernel又設置為線性 則無法捕捉這些非線性關係

4.類別不平衡
如果數據集中的類別是不平衡的 SVC可能會偏向於多數類
特別是沒有進行適當處理（如權重調整）時

5.數據過擬合或欠擬合
由於SVC模型的複雜度較高 如果訓練數據量不足 可能會導致過擬合
同時 如果模型過於簡單 又可能無法捕捉數據的複雜性 導致欠擬合
"""
