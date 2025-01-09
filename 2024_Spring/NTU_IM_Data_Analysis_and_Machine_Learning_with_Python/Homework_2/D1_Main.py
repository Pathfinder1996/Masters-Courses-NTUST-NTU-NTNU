import pandas as pd
import pickle
import numpy as np

from sklearn.metrics import (accuracy_score, precision_score, confusion_matrix,
                            recall_score, f1_score, roc_curve, auc)
from sklearn.model_selection import train_test_split

import matplotlib.pyplot as plt
import seaborn as sns

df = pd.read_csv('maintenance_prediction.csv')
df

#檢查有無缺失或重複值
df.info()

df.isna().any()

df.loc[df.duplicated()]

dup_rows = df.duplicated().sum()
print(f'\n重複的行數: {dup_rows}')

df.describe()

#回答Q1
device_unique_count = df['device'].nunique()
print(f'有{device_unique_count}種裝置')

#回答Q2
normal_device = df[df['failure'] == 0].value_counts().count()
abnormal_device = df[df['failure'] == 1].value_counts().count()
print(f'正常運作: {normal_device}\n發生故障: {abnormal_device}')

#製作工作日+月份+星期幾欄位
df['date'] = pd.to_datetime(df['date'], format='mixed')

df['activedays']=df.date-df.date[0]

df['month'] = df['date'].apply(lambda i : i.month)
month_label = {1.0 : 'Jan', 2.0 : 'Feb', 3.0 : 'Mar', 4.0 : 'Apr', 5.0 : 'May', 6.0 : 'Jun', 
               7.0 : 'Jul', 8.0 : 'Aug', 9.0 : 'Sep', 10.0 : 'Oct', 11 : 'Nov', 12 : 'Dec'}

df['day'] = df['date'].dt.day_of_week + 1

#顯示每個月裝置的狀態
plt.figure(figsize=(10, 5))
sns.countplot(x='month', hue='failure', data=df)
plt.xlabel('month')
plt.ylabel('count')
plt.tight_layout()
plt.show()

#製作每個月裝置failure=0的df
df2 = df[df['failure'] == 0]

df2.describe()

#製作每個月裝置failure=1的df
df3 = df[df['failure'] == 1]

df3.describe()

#顯示每個月故障的裝置
plt.figure(figsize=(10, 5))
sns.countplot(x='month', hue='failure', data=df3, palette='Oranges')
plt.xlabel('month')
plt.ylabel('count')
plt.tight_layout()
plt.show()

#每日裝置活動量
device_counts = df.groupby(['activedays'])['device'].count()

plt.figure(figsize=(10, 5))
device_counts.plot(kind='bar', color='skyblue')
plt.xlabel('Days')
plt.xticks([0, 100, 200, 310], rotation=45)
plt.ylabel('Device Count')
plt.show()

#繪製9個指標+failure相關性熱度
df_corr = df.drop(columns=['date', 'device', 'activedays', 'month', 'day'])
corr = df_corr.corr()

plt.figure(figsize=(10, 10))
sns.heatmap(corr, annot=True)
plt.title('Correlation Heatmap')
plt.show()

#繪製指標7跟8的散點圖
plt.figure(figsize=(5, 5))
plt.scatter(df['metric7'], df['metric8'])
plt.title('Scatter Plot')
plt.xlabel('Metric7')
plt.ylabel('Metric8')
plt.show()

#確認各個裝置型號數量 只取前四個字元
df["device_type"] = df["device"].apply(lambda x : x[:4])
device_type_counts = df["device_type"].value_counts()

plt.figure(figsize=(10, 6))
sns.barplot(x=device_type_counts.values, y=device_type_counts.index, hue=device_type_counts.index, palette="tab10", legend=False)
plt.xlabel("Count")
plt.ylabel("Device Type")
plt.title("Device Type")
plt.show()

#最多故障的型號
df_failure = df[df["failure"] == 1].copy()
df_failure["device_type"] = df_failure["device"].apply(lambda x : x[:4])
device_failure_counts = df_failure["device_type"].value_counts()

plt.figure(figsize=(10, 6))
sns.barplot(x=device_failure_counts.values, y=device_failure_counts.index, hue=device_failure_counts.index, palette="tab10", legend=False)
plt.xlabel("Count")
plt.ylabel("Device Type")
plt.title("failure Device Type")
plt.show()

#製作訓練模型的特徵與標籤
X = df.drop(['date', 'device', 'failure', 'activedays', 'month', 'day', 'device_type'], axis=1)
y = df['failure']

#平衡資料集

from imblearn.over_sampling import SMOTE
from collections import Counter

smo = SMOTE(random_state=42)
X_smo, y_smo = smo.fit_resample(X, y)
print(Counter(y_smo))

'''
以下開始尋找8個模型最佳解 並儲存模型
'''

#模型1: Decision Tree

from sklearn import tree

ratio = 100
ratiovalues = [i for i in range(10, ratio, 10)]
depth = 21
depthvalues = [i for i in range(1, depth)]
leaf = 10
leafvalues = [i for i in range(1, leaf)]
relative_best_train_score = 0
relative_best_test_score = 0
relative_best_ratio = 0
relative_best_depth = 0
relative_best_leaf = 0
relative_best_f1_score = 0
relative_best_recall = 0
relative_best_precision = 0
relative_best_roc_auc = 0

for k in ratiovalues:
    X_train, X_test, y_train, y_test = train_test_split(X_smo, y_smo, test_size=k/100, random_state=42)
    for i in depthvalues:
        for j in leafvalues:
            clf = tree.DecisionTreeClassifier(random_state=42, max_depth=i, min_samples_leaf=j)
            clf.fit(X_train, y_train)
            y_pred_test = clf.predict(X_test)
            test_acc = accuracy_score(y_test, y_pred_test)

            fpr, tpr, _ = roc_curve(y_test, clf.predict_proba(X_test)[:, 1])
            roc_auc = auc(fpr, tpr)

            if roc_auc > relative_best_roc_auc:
                relative_best_train_score = accuracy_score(y_train, clf.predict(X_train))
                relative_best_test_score = test_acc
                relative_best_ratio = k
                relative_best_depth = i
                relative_best_leaf = j
                relative_best_f1_score = f1_score(y_test, y_pred_test, average='weighted')
                relative_best_recall = recall_score(y_test, y_pred_test, average='weighted')
                relative_best_precision = precision_score(y_test, y_pred_test, average='weighted', zero_division=1)
                relative_best_roc_auc = roc_auc
                best_fpr, best_tpr = fpr, tpr 
                best_cm = confusion_matrix(y_test, y_pred_test) 
                best_clf = clf

print("best ratio of testing data:", relative_best_ratio, 
        "\nbest depth:", relative_best_depth, 
        "\nbest min_sample_leaf:", relative_best_leaf,
        "\nTraining score:", relative_best_train_score, 
        "\nTesting score:", relative_best_test_score,      
        "\nF1 score:", relative_best_f1_score,
        "\nRecall:", relative_best_recall,
        "\nPrecision:", relative_best_precision,
        "\nROC AUC:", relative_best_roc_auc,
        "\n\nConfusion Matrix:\n", best_cm)     


with open('best_decision_tree_model.pkl', 'wb') as file:
    pickle.dump(best_clf, file)
    
#模型2: KNN

from sklearn import neighbors

ratio = 100
ratiovalues = [i for i in range(10, ratio, 10)]
neighbor = 10
neighborvalues = [i for i in range(1, neighbor)]
p = 3
pvalues = [i for i in range(1, p)]
relative_best_train_score = 0
relative_best_test_score = 0
relative_best_ratio = 0
relative_best_neighbor = 0
relative_best_p = 0
relative_best_f1_score = 0
relative_best_recall = 0
relative_best_precision = 0
relative_best_roc_auc = 0

for k in ratiovalues:
    X_train, X_test, y_train, y_test = train_test_split(X_smo, y_smo, test_size=k/100, random_state=42)
    for i in neighborvalues:
        for j in pvalues:
            clf = neighbors.KNeighborsClassifier(n_neighbors=i, p=j)
            clf.fit(X_train, y_train)
            y_pred_test = clf.predict(X_test)
            test_acc = accuracy_score(y_test, y_pred_test)

            fpr, tpr, _ = roc_curve(y_test, clf.predict_proba(X_test)[:, 1])
            roc_auc = auc(fpr, tpr)

            if roc_auc > relative_best_roc_auc:
                relative_best_train_score = accuracy_score(y_train, clf.predict(X_train))
                relative_best_test_score = test_acc
                relative_best_ratio = k
                relative_best_neighbor = i
                relative_best_p = j
                relative_best_f1_score = f1_score(y_test, y_pred_test, average='weighted')
                relative_best_recall = recall_score(y_test, y_pred_test, average='weighted')
                relative_best_precision = precision_score(y_test, y_pred_test, average='weighted', zero_division=1)
                relative_best_roc_auc = roc_auc
                best_fpr, best_tpr = fpr, tpr
                best_cm = confusion_matrix(y_test, y_pred_test)
                best_clf = clf

print("best ratio of testing data:", relative_best_ratio, 
        "\nbest neighbors:", relative_best_neighbor, 
        "\nbest p:", relative_best_p,
        "\nTraining score:", relative_best_train_score, 
        "\nTesting score:", relative_best_test_score, 
        "\nF1 score:", relative_best_f1_score,
        "\nRecall:", relative_best_recall,
        "\nPrecision:", relative_best_precision,
        "\nROC AUC:", relative_best_roc_auc,
        "\n\nconfusion matrix:\n", best_cm) 

with open('best_knn_model.pkl', 'wb') as file:
    pickle.dump(best_clf, file)

#模型3: RandomForest

from sklearn.ensemble import RandomForestClassifier

ratio = 100
ratiovalues = [i for i in range(10, ratio, 10)]
n_estimator = 250
n_estimatorvalues = [i for i in range(100, n_estimator, 50)]
depth = 8
depthvalues = [i for i in range(1, depth)]
leaf = 5
leafvalues = [i for i in range(1, leaf)]
relative_best_train_score = 0
relative_best_test_score = 0
relative_best_ratio = 0
relative_best_estimators = 0
relative_best_depth = 0
relative_best_leaf = 0
relative_best_f1_score = 0
relative_best_recall = 0
relative_best_precision = 0
relative_best_roc_auc = 0

for k in ratiovalues:
    X_train, X_test, y_train, y_test = train_test_split(X_smo, y_smo, test_size=k/100, random_state=71)
    for l in n_estimatorvalues:
        for i in depthvalues:
            for j in leafvalues:
                clf = RandomForestClassifier(random_state=71, n_estimators=l, max_depth=i, min_samples_leaf=j)
                clf.fit(X_train, y_train)
                y_pred_test = clf.predict(X_test)
                test_acc = accuracy_score(y_test, y_pred_test)

                fpr, tpr, _ = roc_curve(y_test, clf.predict_proba(X_test)[:, 1])
                roc_auc = auc(fpr, tpr)

                if roc_auc > relative_best_roc_auc:
                    relative_best_train_score = accuracy_score(y_train, clf.predict(X_train))
                    relative_best_test_score = test_acc
                    relative_best_ratio = k
                    relative_best_estimators = l
                    relative_best_depth = i
                    relative_best_leaf = j
                    relative_best_f1_score = f1_score(y_test, y_pred_test, average='weighted')
                    relative_best_recall = recall_score(y_test, y_pred_test, average='weighted')
                    relative_best_precision = precision_score(y_test, y_pred_test, average='weighted', zero_division=1)
                    relative_best_roc_auc = roc_auc
                    best_fpr, best_tpr = fpr, tpr
                    best_cm = confusion_matrix(y_test, y_pred_test)
                    best_clf = clf

print("best ratio of testing data:", relative_best_ratio, 
        "\nbest no. of estimators:", relative_best_estimators, 
        "\nbest depth:", relative_best_depth, 
        "\nbest min_sample_leaf:", relative_best_leaf,
        "\nTraining score:", relative_best_train_score, 
        "\nTesting score:", relative_best_test_score,
        "\nF1 score:", relative_best_f1_score,
        "\nRecall:", relative_best_recall,
        "\nPrecision:", relative_best_precision,
        "\nROC AUC:", relative_best_roc_auc,
        "\n\nconfusion matrix:\n", best_cm)

with open('best_random_forest_model.pkl', 'wb') as file:
    pickle.dump(best_clf, file)

#模型4: XGBoost

from xgboost.sklearn import XGBClassifier

ratio = 100
ratiovalues = [i for i in range(10, ratio, 10)]
n_estimator = 250
n_estimatorvalues = [i for i in range(100, n_estimator, 50)]
depth = 8
depthvalues = [i for i in range(1, depth)]
rate = 3
ratevalues = [i for i in range(1, rate)]
relative_best_train_score = 0
relative_best_test_score = 0
relative_best_ratio = 0
relative_best_estimators = 0
relative_best_depth = 0
relative_best_rate = 0
relative_best_f1_score = 0
relative_best_recall = 0
relative_best_precision = 0
relative_best_roc_auc = 0

for k in ratiovalues:
    X_train, X_test, y_train, y_test = train_test_split(X_smo, y_smo, test_size=k/100, random_state=42)
    for l in n_estimatorvalues:
        for i in depthvalues:
            for j in ratevalues:
                clf = XGBClassifier(random_state=42, n_estimators=l, max_depth=i, learning_rate=j)
                clf.fit(X_train, y_train)
                y_pred_test = clf.predict(X_test)
                test_acc = accuracy_score(y_test, y_pred_test)

                fpr, tpr, _ = roc_curve(y_test, clf.predict_proba(X_test)[:, 1])
                roc_auc = auc(fpr, tpr)

                if roc_auc > relative_best_roc_auc:
                    relative_best_train_score = accuracy_score(y_train, clf.predict(X_train))
                    relative_best_test_score = test_acc
                    relative_best_ratio = k
                    relative_best_estimators = l
                    relative_best_depth = i
                    relative_best_rate = j
                    relative_best_f1_score = f1_score(y_test, y_pred_test, average='weighted')
                    relative_best_recall = recall_score(y_test, y_pred_test, average='weighted')
                    relative_best_precision = precision_score(y_test, y_pred_test, average='weighted', zero_division=1)
                    relative_best_roc_auc = roc_auc
                    best_fpr, best_tpr = fpr, tpr
                    best_cm = confusion_matrix(y_test, y_pred_test)
                    best_clf = clf

print("best ratio of testing data:", relative_best_ratio,
        "\nbest no. of estimators:", relative_best_estimators,
        "\nbest depth:", relative_best_depth,
        "\nbest learning_rate:", relative_best_rate,
        "\nTraining score:", relative_best_train_score,
        "\nTesting score:", relative_best_test_score,
        "\nF1 score:", relative_best_f1_score,
        "\nRecall:", relative_best_recall,
        "\nPrecision:", relative_best_precision,
        "\nROC AUC:", relative_best_roc_auc,
        "\n\nconfusion matrix:\n", best_cm)

with open('best_xgboost_model.pkl', 'wb') as file:
    pickle.dump(best_clf, file)

#模型5: LogisticRegression

from sklearn.linear_model import LogisticRegression

ratio = 100
ratio_values = [i for i in range(10, ratio, 10)]
C_values = [0.001, 0.01, 0.1, 1, 10, 100]
class_weight_values = [None, 'balanced']
solver_values = ['newton-cg', 'lbfgs', 'liblinear', 'sag', 'saga']

best_train_score = 0
best_test_score = 0
best_ratio = 0
best_C = 0
best_class_weight = ''
best_solver = ''
best_f1_score = 0
best_recall = 0
best_precision = 0
best_roc_auc = 0

for k in ratio_values:
    X_train, X_test, y_train, y_test = train_test_split(X_smo, y_smo, test_size=k/100, random_state=42)
    for i in C_values:
        for j in class_weight_values:
            for r in solver_values:
                clf = LogisticRegression(C=i, class_weight=j, solver=r, max_iter=1000)
                clf.fit(X_train, y_train)
                y_pred_test = clf.predict(X_test)
                test_acc = accuracy_score(y_test, y_pred_test)

                fpr, tpr, _ = roc_curve(y_test, clf.predict_proba(X_test)[:, 1])
                roc_auc = auc(fpr, tpr)

                if roc_auc > best_roc_auc:
                    best_train_score = accuracy_score(y_train, clf.predict(X_train))
                    best_test_score = test_acc
                    best_ratio = k
                    best_C = i
                    best_class_weight = j
                    best_solver = r
                    best_f1_score = f1_score(y_test, y_pred_test, average='weighted')
                    best_recall = recall_score(y_test, y_pred_test, average='weighted')
                    best_precision = precision_score(y_test, y_pred_test, average='weighted', zero_division=1)
                    best_roc_auc = roc_auc
                    best_fpr, best_tpr = fpr, tpr
                    best_cm = confusion_matrix(y_test, y_pred_test)
                    best_clf = clf

print("best ratio of testing data:", best_ratio,
        "\nbest C:", best_C,
        "\nbest class weight:", best_class_weight,
        "\nbest solver:", best_solver,
        "\nTraining score:", best_train_score,
        "\nTesting score:", best_test_score,
        "\nF1 score:", best_f1_score,
        "\nRecall:", best_recall,
        "\nPrecision:", best_precision,
        "\nROC AUC:", best_roc_auc,
        "\n\nconfusion matrix:\n", best_cm)

with open('best_logistic_regression_model.pkl', 'wb') as file:
    pickle.dump(best_clf, file)

#模型6: Gaussian Naive bayes

from sklearn.naive_bayes import GaussianNB

ratio = 100
ratiovalues = [i for i in range(10, ratio, 10)]
relative_best_train_score = 0
relative_best_test_score = 0
relative_best_ratio = 0
relative_best_f1_score = 0
relative_best_recall = 0
relative_best_precision = 0
relative_best_roc_auc = 0

for k in ratiovalues:
    X_train, X_test, y_train, y_test = train_test_split(X_smo, y_smo, test_size=k/100, random_state=42)
    clf = GaussianNB()
    clf.fit(X_train, y_train)
    y_pred_test = clf.predict(X_test)
    test_acc = accuracy_score(y_test, y_pred_test)

    fpr, tpr, _ = roc_curve(y_test, clf.predict_proba(X_test)[:, 1])
    roc_auc = auc(fpr, tpr)

    if roc_auc > relative_best_roc_auc:
        relative_best_train_score = accuracy_score(y_train, clf.predict(X_train))
        relative_best_test_score = test_acc
        relative_best_ratio = k
        relative_best_f1_score = f1_score(y_test, y_pred_test, average='weighted')
        relative_best_recall = recall_score(y_test, y_pred_test, average='weighted')
        relative_best_precision = precision_score(y_test, y_pred_test, average='weighted', zero_division=1)
        relative_best_roc_auc = roc_auc
        best_fpr, best_tpr = fpr, tpr
        best_cm = confusion_matrix(y_test, y_pred_test)
        best_clf = clf

print("best ratio of testing data:", relative_best_ratio,
        "\nTraining score:", relative_best_train_score,
        "\nTesting score:", relative_best_test_score,
        "\nF1 score:", relative_best_f1_score,
        "\nRecall:", relative_best_recall,
        "\nPrecision:", relative_best_precision,
        "\nROC AUC:", relative_best_roc_auc,
        "\n\nconfusion matrix:\n", best_cm)


with open('best_gaussian_nb_model.pkl', 'wb') as file:
    pickle.dump(best_clf, file)

#模型7: Multinomail Naive bayes

from sklearn.naive_bayes import MultinomialNB

ratio = 100
ratiovalues = [i for i in range(10, ratio, 10)]
alpha_values = [0.001, 0.01, 0.1, 1, 10, 100]
fit_prior_values = [True, False]
class_prior_values = [None, [0.1, 0.9], [0.2, 0.8], [0.3, 0.7], [0.4, 0.6], [0.5, 0.5]]

relative_best_train_score = 0
relative_best_test_score = 0
relative_best_ratio = 0
relative_best_alpha = 0
relative_best_fit_prior = True
relative_best_class_prior = None
relative_best_f1_score = 0
relative_best_recall = 0
relative_best_precision = 0
relative_best_roc_auc = 0

for k in ratiovalues:
    X_train, X_test, y_train, y_test = train_test_split(X_smo, y_smo, test_size=k/100, random_state=42)
    for i in alpha_values:
        for j in fit_prior_values:
            for r in class_prior_values:
                clf = MultinomialNB(alpha=i, fit_prior=j, class_prior=r)
                clf.fit(X_train, y_train)
                y_pred_test = clf.predict(X_test)
                test_acc = accuracy_score(y_test, y_pred_test)

                fpr, tpr, _ = roc_curve(y_test, clf.predict_proba(X_test)[:, 1])
                roc_auc = auc(fpr, tpr)

                if roc_auc > relative_best_roc_auc:
                    relative_best_train_score = accuracy_score(y_train, clf.predict(X_train))
                    relative_best_test_score = test_acc
                    relative_best_ratio = k
                    relative_best_alpha = i
                    relative_best_fit_prior = j
                    relative_best_class_prior = r
                    relative_best_f1_score = f1_score(y_test, y_pred_test, average='weighted')
                    relative_best_recall = recall_score(y_test, y_pred_test, average='weighted')
                    relative_best_precision = precision_score(y_test, y_pred_test, average='weighted', zero_division=1)
                    relative_best_roc_auc = roc_auc
                    best_fpr, best_tpr = fpr, tpr
                    best_cm = confusion_matrix(y_test, y_pred_test)
                    best_clf = clf

print("best ratio of testing data:", relative_best_ratio,
        "\nbest alpha:", relative_best_alpha,
        "\nbest fit_prior:", relative_best_fit_prior,
        "\nbest class_prior:", relative_best_class_prior,
        "\nTraining score:", relative_best_train_score,
        "\nTesting score:", relative_best_test_score,
        "\nF1 score:", relative_best_f1_score,
        "\nRecall:", relative_best_recall,
        "\nPrecision:", relative_best_precision,
        "\nROC AUC:", relative_best_roc_auc,
        "\n\nconfusion matrix:\n", best_cm)

with open('best_multinomial_nb_model.pkl', 'wb') as file:
    pickle.dump(best_clf, file)

#模型8 SVM

from sklearn import svm
from sklearn.model_selection import GridSearchCV

kernel_values = ["rbf", "poly"]
gamma_values = ["scale"]
param_grid = {'kernel': kernel_values, 'gamma': gamma_values,}

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)
svc = svm.SVC(random_state=42, probability=True)
grid = GridSearchCV(svc, param_grid, refit=True, cv=3, scoring='roc_auc', n_jobs=-1)
grid.fit(X_train, y_train)

best_model = grid.best_estimator_
y_pred_test = best_model.predict(X_test)

fpr, tpr, _ = roc_curve(y_test, best_model.predict_proba(X_test)[:, 1])
roc_auc = auc(fpr, tpr)
best_cm = confusion_matrix(y_test, y_pred_test)

print("Best parameters found:", grid.best_params_,
      "\nROC AUC:", roc_auc,
      "\n\nconfusion matrix:\n", best_cm)

with open('best_svm_model.pkl', 'wb') as file:
    pickle.dump(best_model, file)

#回答Q3

data = pd.read_csv('maintenance_prediction.csv')
X = data[['metric1', 'metric2', 'metric3', 'metric4', 'metric5', 'metric6', 'metric7', 'metric8', 'metric9']]
y = data['failure']

model_files = [
    'best_xgboost_model.pkl',
    'best_decision_tree_model.pkl',
    'best_gaussian_nb_model.pkl',
    'best_knn_model.pkl',
    'best_logistic_regression_model.pkl',
    'best_multinomial_nb_model.pkl',
    'best_random_forest_model.pkl',
    'best_svm_model.pkl']

performance_data = []

fig, axes = plt.subplots(4, 2, figsize=(10, 20)) 
axes = axes.flatten()

roc_fig, roc_ax = plt.subplots(figsize=(5, 5))

for i, model_file in enumerate(model_files):
    with open(model_file, 'rb') as file:
        model = pickle.load(file)

    model_name = model_file.replace('best_', '').replace('_model.pkl', '')

    predictions = model.predict(X)
    probas = model.predict_proba(X)[:, 1]
    fpr, tpr, _ = roc_curve(y, probas)
    roc_auc = auc(fpr, tpr)

    roc_ax.plot(fpr, tpr, lw=2, label=f'{model_name} (Area = {roc_auc:.7f})')
    
    cm = confusion_matrix(y, predictions)
    sns.heatmap(cm, annot=True, fmt="d", cmap="Blues", ax=axes[i])
    axes[i].set_title(model_name, fontsize=15, color='red')
    axes[i].set_xlabel('Predicted Label')
    axes[i].set_ylabel('True Label')
    
    accuracy = accuracy_score(y, predictions)
    f1 = f1_score(y, predictions, average='weighted')
    recall = recall_score(y, predictions, average='weighted')
    precision = precision_score(y, predictions, average='weighted')
    
    print(f"Model: {model_name}")
    print("Accuracy:", accuracy)
    print("F1 Score:", f1)
    print("Recall:", recall)
    print("Precision:", precision)
    print("Roc auc:", roc_auc)
    print("\n")
    
    performance_data.append({
    'Model': model_name,
    'Accuracy': accuracy,
    'F1 Score': f1,
    'Recall': recall,
    'Precision': precision,
    'ROC AUC': roc_auc})
    
performance_df = pd.DataFrame(performance_data)
performance_df.to_csv('all_model_metrics.csv', index=False)

roc_ax.plot([0, 1], [0, 1], color='black', linestyle='--')
roc_ax.set_xlim([0, 1])
roc_ax.set_ylim([0, 1])
roc_ax.set_xlabel('False Positive Rate')
roc_ax.set_ylabel('True Positive Rate')
roc_ax.set_title('ROC Curve')
roc_ax.legend(loc="lower right")

plt.tight_layout()
plt.show()

#儲存各模型的準確率等指標

df2 = pd.read_csv('all_model_metrics.csv')

df2

#回答Q4

import xgboost as xgb

X = data[['metric1', 'metric2', 'metric3', 'metric4', 'metric5', 'metric6', 'metric7', 'metric8', 'metric9']]
y = data['failure']

X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.1, random_state=42)

best_xgb_model = xgb.XGBClassifier(n_estimators=200, learning_rate=1, max_depth=5, random_state=42)
best_xgb_model.fit(X_train, y_train)
importance = best_xgb_model.feature_importances_

feature_importance_df = pd.DataFrame({'Feature': X.columns, 'Importance': importance}).sort_values(by='Importance', ascending=False)

colors = plt.cm.viridis(np.linspace(0, 1, len(X.columns)))
plt.figure(figsize=(10, 6))
plt.barh(feature_importance_df['Feature'], feature_importance_df['Importance'], color=colors)
plt.title('XGBoost Important Features', fontsize=15)
plt.gca().invert_yaxis()
plt.show()

#回答Q5

AA = best_xgb_model.predict([[127175526, 4109.434, 3.90566, 54.63208, 15.46226,
                                258303.5, 30.62264, 30.62264, 23.08491]])

BB = best_xgb_model.predict([[4527376, 0, 0, 0, 3, 24, 0, 0, 0]])

print('Device AA 預測為:', AA)

print('Device BB 預測為:', BB)
