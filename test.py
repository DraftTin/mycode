import pandas as pd

data = {"A": [1, 2, 3, 4]}
series = pd.Series(data)
# 应用 reset_index() 函数
df = series.reset_index()
print(df)
print(df.columns)
