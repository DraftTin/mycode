import numpy as np
import pandas as pd

df = pd.DataFrame({"A": [1, np.nan, 3, np.nan], "B": [2, 4, np.nan, np.nan]})
print(df.ffill())
print(df.bfill())
print(df.interpolate())
