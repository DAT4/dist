import pandas as pd
import plotly.express as px
from itertools import groupby

keys = ['cores', 'pi', 'error', 'seconds']

csv = [[float(y) 
    for y in x.split(',')] 
    for x in open('out.log').readlines()]

groups = [list(vs) for _, vs in groupby(csv, lambda x: x[0])]

aggregation = [[sum([x[i] 
    for x in vs])/len(vs) 
    for i in range(len(vs[0])) if i != 2] 
    for vs in groups]

df = pd.DataFrame([{k:v for k,v in zip(keys,x)} for x in aggregation])
fig = px.line(df, x='cores', y='seconds')
fig.write_image('fig1.svg')

print(df)

