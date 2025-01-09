import pandas as pd
import pickle
import numpy as np

from sklearn.metrics import (accuracy_score, precision_score, confusion_matrix,
                            recall_score, f1_score, roc_curve, auc)
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler, MinMaxScaler

import matplotlib.pyplot as plt
import seaborn as sns

df = pd.read_csv('Insurance_dataset.csv')

#檢查有無缺失或重複值
df.info()

df.isna().any()

df.loc[df.duplicated()]

dup_rows = df.duplicated().sum()
print(f'\n重複的行數: {dup_rows}')

df.describe()

#計算每個欄位的類別數量
for column in df.columns:
    unique_v = df[column].nunique()
    print(f'{column} 有 {unique_v} 種類別')

#顯示文字欄位的各類別名稱
print('\n性別', df['Gender'].value_counts())
print('\n裝置年紀', df['Vehicle_Age'].value_counts())
print('\n裝置損壞', df['Vehicle_Damage'].value_counts())
print('\n回應', df['Response'].value_counts())

#文字轉數值表示
df['Gender'] = df['Gender'].map({'Female':0, 'Male':1}).astype('int')
df['Vehicle_Age'] = df['Vehicle_Age'].map({'1-2 Year':0, '< 1 Year':1, '> 2 Years':2}).astype('int')
df['Vehicle_Damage'] = df['Vehicle_Damage'].map({'No':0, 'Yes':1}).astype('int')

df.head()

scale_standard = StandardScaler()
numeric_features = ['Annual_Premium', 'Vintage']
df[numeric_features] = scale_standard.fit_transform(df[numeric_features])

df.head(10)

#製作訓練模型的特徵與標籤
X = df.drop(['id', 'Response'], axis=1)
y = df['Response']

from imblearn.under_sampling import RandomUnderSampler
from collections import Counter

rus = RandomUnderSampler(random_state=42)
X_rus, y_rus = rus.fit_resample(X, y)
print(Counter(y_rus))

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
    X_train, X_test, y_train, y_test = train_test_split(X_rus, y_rus, test_size=k/100, random_state=42)
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
        "\nConfusion Matrix:\n", best_cm)     


with open('d2_best_decision_tree_model.pkl', 'wb') as file:
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
    X_train, X_test, y_train, y_test = train_test_split(X_rus, y_rus, test_size=k/100, random_state=42)
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

with open('d2_best_knn_model.pkl', 'wb') as file:
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
    X_train, X_test, y_train, y_test = train_test_split(X_rus, y_rus, test_size=k/100, random_state=71)
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

with open('d2_best_random_forest_model.pkl', 'wb') as file:
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
    X_train, X_test, y_train, y_test = train_test_split(X_rus, y_rus, test_size=k/100, random_state=42)
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

with open('d2_best_xgboost_model.pkl', 'wb') as file:
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
    X_train, X_test, y_train, y_test = train_test_split(X_rus, y_rus, test_size=k/100, random_state=42)
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

with open('d2_best_logistic_regression_model.pkl', 'wb') as file:
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
    X_train, X_test, y_train, y_test = train_test_split(X_rus, y_rus, test_size=k/100, random_state=42)
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


with open('d2_best_gaussian_nb_model.pkl', 'wb') as file:
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
    X_train, X_test, y_train, y_test = train_test_split(X_rus, y_rus, test_size=k/100, random_state=42)
    for i in alpha_values:
        for j in fit_prior_values:
            for r in class_prior_values:
                clf = MultinomialNB(alpha=i, fit_prior=j, class_prior=r)
                
                min_feature_value = np.min(X_train)
                if min_feature_value < 0:
                    shift_value = abs(min_feature_value)
                    X_train += shift_value
                    X_test += shift_value  
                
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

with open('d2_best_multinomial_nb_model.pkl', 'wb') as file:
    pickle.dump(best_clf, file)

#模型8 SVM

from sklearn import svm
from sklearn.model_selection import GridSearchCV

kernel_values = ["rbf", "poly"]
gamma_values = ["scale"]
param_grid = {'kernel': kernel_values, 'gamma': gamma_values,}

X_train, X_test, y_train, y_test = train_test_split(X_rus, y_rus, test_size=0.2, random_state=42)
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

with open('d2_best_svm_model.pkl', 'wb') as file:
    pickle.dump(best_model, file)
    
'''
用8個儲存的模型來預測原始資料集 並計算多個指標與視覺化 
'''

data = pd.read_csv('Insurance_dataset.csv')

X = df.drop(['id', 'Response'], axis=1)
y = df['Response']

model_files = [
    'd2_best_xgboost_model.pkl',
    'd2_best_decision_tree_model.pkl',
    'd2_best_gaussian_nb_model.pkl',
    'd2_best_knn_model.pkl',
    'd2_best_logistic_regression_model.pkl',
    'd2_best_multinomial_nb_model.pkl',
    'd2_best_random_forest_model.pkl',
    'd2_best_svm_model.pkl']

performance_data = []

fig, axes = plt.subplots(4, 2, figsize=(10, 20)) 
axes = axes.flatten()

roc_fig, roc_ax = plt.subplots(figsize=(5, 5))

for i, model_file in enumerate(model_files):
    with open(model_file, 'rb') as file:
        model = pickle.load(file)

    model_name = model_file.replace('d2_best_', '').replace('_model.pkl', '')

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

performance_df

df_val = pd.read_csv('Insurance_validation.csv')

df_val

df_val['Gender'] = df_val['Gender'].map({'Female':0, 'Male':1}).astype('int')
df_val['Vehicle_Age'] = df_val['Vehicle_Age'].map({'1-2 Year':0, '< 1 Year':1, '> 2 Years':2}).astype('int')
df_val['Vehicle_Damage'] = df_val['Vehicle_Damage'].map({'No':0, 'Yes':1}).astype('int')

scale_standard = StandardScaler()
numeric_features = ['Annual_Premium', 'Vintage']
df_val[numeric_features] = scale_standard.fit_transform(df_val[numeric_features])

df_val.head(10)

import joblib

model = joblib.load('d2_best_xgboost_model.pkl')

validation_id = df_val['id']
validation_no_id = df_val.drop(columns=['id'])

predictions = model.predict(validation_no_id)

results = pd.DataFrame({'id': validation_id, 'Response': predictions})
results.to_csv('D2_val_predict.csv', index=False)

results.head(20)
