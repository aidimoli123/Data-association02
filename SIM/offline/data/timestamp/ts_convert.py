import os
import json

import pandas as pd
from pandas.api.types import is_numeric_dtype

curDir = os.path.dirname(os.path.realpath(__file__))
file_pth = os.path.join(curDir, "ts.json")
csv_pth = os.path.join(curDir, "ts.csv")

with open(file_pth, "r") as load_f:
    load_dict = json.load(load_f)

    sample_ts = pd.Series([int(i) for i in load_dict['sample_ts']])
    camFront_ts = pd.Series([int(i) for i in load_dict['camFront_ts']])
    radarFront_ts = pd.Series([int(i) for i in load_dict['radarFront_ts']])

    if is_numeric_dtype(sample_ts):
        load_dict['sample_time'] = pd.to_datetime(sample_ts, unit='us')

    if is_numeric_dtype(camFront_ts):
        load_dict['camFront_time'] = pd.to_datetime(camFront_ts, unit='us')

    if is_numeric_dtype(radarFront_ts):
        load_dict['radarFront_time'] = pd.to_datetime(radarFront_ts, unit='us')

    pd_ts = pd.DataFrame(load_dict)
    pd_ts.to_csv(csv_pth, index=True, sep='\t')