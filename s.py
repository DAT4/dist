from statistics import mean
from itertools import groupby
import pandas as pd
import plotly.express as px
import sys

input_file  = sys.argv[1]
output_img  = f'{input_file.split('.')[0]}.svg'
output_csv  = f'{input_file.split('.')[0]}.csv'
keys        = [sys.argv[2], 'pi', 'error', 'seconds']

def save_plot(data):
    df = pd.DataFrame([{k:v for k,v in zip(keys,x)} for x in data])
    fig = px.line(
        data_frame = df, 
        x=x_axis,
        y='seconds',
        markers=True,
        line_shape = 'spline',
    )
    fig.update_layout(
        yaxis = dict(
            tickmode = 'linear',
            tick0 = 0.0,
            dtick = 0.005
        )
    )

    fig.write_image(output_img)

def save_csv(data):
    open(output_csv, 'w').write('\n'.join(', '.join(str(x) for x in x) for x in aggregation))

if __name__ == '__main__':
    csv = [[float(y) 
        for y in x.split(',')] 
        for x in open(input_file).readlines()]

    groups = [list(vs) for _, vs in groupby(csv, lambda x: x[0])]

    aggregation = [[
        mean([abs(x[i]) for x in vs])
        for i in range(len(vs[0]))] 
        for vs in groups]

    save_csv(aggregation)
    save_plot(aggregation)


