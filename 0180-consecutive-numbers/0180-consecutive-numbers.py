import pandas as pd

def consecutive_numbers(logs: pd.DataFrame) -> pd.DataFrame:
    is_consecutive = (logs['num'] == logs['num'].shift(1)) & (logs['num'] == logs['num'].shift(2))
    
    # Filter the dataframe, extract unique values, and rename the column
    result = logs.loc[is_consecutive, ['num']].drop_duplicates()
    result.columns = ['ConsecutiveNums']
    
    return result