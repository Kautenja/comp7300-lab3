

```python
import pandas as pd
from matplotlib import pyplot as plt
%matplotlib inline
```


```python
tests = 7
N = 40000
```

# Columnwise 


```python
columnwise = pd.read_csv('./columnwise.csv', index_col=0)
columnwise.head()
```




<div>
<style>
    .dataframe thead tr:only-child th {
        text-align: right;
    }

    .dataframe thead th {
        text-align: left;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>$index_{max}$</th>
      <th>$max$</th>
      <th>index_{min}</th>
      <th>min</th>
      <th>avg</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>1.0</td>
      <td>3.887</td>
      <td>1.0</td>
      <td>3.887</td>
      <td>3.887</td>
    </tr>
    <tr>
      <th>1</th>
      <td>1.0</td>
      <td>3.887</td>
      <td>2.0</td>
      <td>1.710</td>
      <td>2.798</td>
    </tr>
    <tr>
      <th>2</th>
      <td>1.0</td>
      <td>3.887</td>
      <td>3.0</td>
      <td>1.701</td>
      <td>2.433</td>
    </tr>
    <tr>
      <th>3</th>
      <td>1.0</td>
      <td>3.887</td>
      <td>3.0</td>
      <td>1.701</td>
      <td>2.251</td>
    </tr>
    <tr>
      <th>4</th>
      <td>1.0</td>
      <td>3.887</td>
      <td>3.0</td>
      <td>1.701</td>
      <td>2.143</td>
    </tr>
  </tbody>
</table>
</div>




```python
end_columnwise = columnwise.iloc[columnwise.index[(columnwise.index % tests == 0)] - 1].sort_index()
end_columnwise.index = pd.np.arange(len(end_columnwise)) + 1
```


```python
end_columnwise['total_avg'] = end_columnwise['avg'].mean()
```


```python
end_columnwise.head()
```




<div>
<style>
    .dataframe thead tr:only-child th {
        text-align: right;
    }

    .dataframe thead th {
        text-align: left;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>$index_{max}$</th>
      <th>$max$</th>
      <th>index_{min}</th>
      <th>min</th>
      <th>avg</th>
      <th>total_avg</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>1</th>
      <td>1.0</td>
      <td>3.887</td>
      <td>6.0</td>
      <td>1.694</td>
      <td>2.016</td>
      <td>1.9376</td>
    </tr>
    <tr>
      <th>2</th>
      <td>1.0</td>
      <td>3.675</td>
      <td>6.0</td>
      <td>1.605</td>
      <td>1.910</td>
      <td>1.9376</td>
    </tr>
    <tr>
      <th>3</th>
      <td>1.0</td>
      <td>3.718</td>
      <td>7.0</td>
      <td>1.587</td>
      <td>1.898</td>
      <td>1.9376</td>
    </tr>
    <tr>
      <th>4</th>
      <td>1.0</td>
      <td>3.772</td>
      <td>4.0</td>
      <td>1.616</td>
      <td>1.941</td>
      <td>1.9376</td>
    </tr>
    <tr>
      <th>5</th>
      <td>1.0</td>
      <td>3.728</td>
      <td>4.0</td>
      <td>1.613</td>
      <td>1.923</td>
      <td>1.9376</td>
    </tr>
  </tbody>
</table>
</div>




```python
ax = end_columnwise['avg'].plot(legend=True, title='Times to Initialize and Tranpose a 40000x40000 Matrix Columnwise')
ax = end_columnwise['total_avg'].plot(legend=True, style=['--'])
plt.legend(['Avg after 7th trial', 'total average'])
```




    <matplotlib.legend.Legend at 0x112088128>




![png](output_7_1.png)



```python
end_columnwise['avg'].mean()
```




    1.9375999999999998



# Rowwise 


```python
rowwise = pd.read_csv('./rowwise.csv', index_col=0)
rowwise.head()
```




<div>
<style>
    .dataframe thead tr:only-child th {
        text-align: right;
    }

    .dataframe thead th {
        text-align: left;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>$index_{max}$</th>
      <th>$max$</th>
      <th>index_{min}</th>
      <th>min</th>
      <th>avg</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>1.0</td>
      <td>3.883</td>
      <td>1.0</td>
      <td>3.883</td>
      <td>3.883</td>
    </tr>
    <tr>
      <th>1</th>
      <td>1.0</td>
      <td>3.883</td>
      <td>2.0</td>
      <td>1.773</td>
      <td>2.828</td>
    </tr>
    <tr>
      <th>2</th>
      <td>1.0</td>
      <td>3.883</td>
      <td>3.0</td>
      <td>1.771</td>
      <td>2.475</td>
    </tr>
    <tr>
      <th>3</th>
      <td>1.0</td>
      <td>3.883</td>
      <td>3.0</td>
      <td>1.771</td>
      <td>2.301</td>
    </tr>
    <tr>
      <th>4</th>
      <td>1.0</td>
      <td>3.883</td>
      <td>3.0</td>
      <td>1.771</td>
      <td>2.196</td>
    </tr>
  </tbody>
</table>
</div>




```python
end_rowwise = rowwise.iloc[rowwise.index[(rowwise.index % tests == 0)] - 1].sort_index()
end_rowwise.index = pd.np.arange(len(end_rowwise)) + 1
```


```python
end_rowwise['total_avg'] = end_rowwise['avg'].mean()
```


```python
end_rowwise.head()
```




<div>
<style>
    .dataframe thead tr:only-child th {
        text-align: right;
    }

    .dataframe thead th {
        text-align: left;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>$index_{max}$</th>
      <th>$max$</th>
      <th>index_{min}</th>
      <th>min</th>
      <th>avg</th>
      <th>total_avg</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>1</th>
      <td>1.0</td>
      <td>3.883</td>
      <td>7.0</td>
      <td>1.771</td>
      <td>2.075</td>
      <td>2.154</td>
    </tr>
    <tr>
      <th>2</th>
      <td>1.0</td>
      <td>3.680</td>
      <td>3.0</td>
      <td>1.910</td>
      <td>2.176</td>
      <td>2.154</td>
    </tr>
    <tr>
      <th>3</th>
      <td>1.0</td>
      <td>3.620</td>
      <td>7.0</td>
      <td>1.878</td>
      <td>2.143</td>
      <td>2.154</td>
    </tr>
    <tr>
      <th>4</th>
      <td>1.0</td>
      <td>3.588</td>
      <td>6.0</td>
      <td>1.909</td>
      <td>2.173</td>
      <td>2.154</td>
    </tr>
    <tr>
      <th>5</th>
      <td>1.0</td>
      <td>3.611</td>
      <td>4.0</td>
      <td>1.947</td>
      <td>2.203</td>
      <td>2.154</td>
    </tr>
  </tbody>
</table>
</div>




```python
ax = end_rowwise['avg'].plot(legend=True, title='Times to Initialize and Tranpose a 40000x40000 Matrix Rowwise')
ax = end_rowwise['total_avg'].plot(legend=True, style=['--'])
plt.legend(['Avg after 7th trial', 'total average'])
```




    <matplotlib.legend.Legend at 0x11218a940>




![png](output_14_1.png)



```python
end_rowwise['avg'].mean()
```




    2.1539999999999999



# Comparisons


```python
title = 'Times to Initialize and Transpose a ${N}$x${N}$ Matrix'
rowwise['avg'].plot(title=title.format(N=N), legend=True, lw=3)
ax = columnwise['avg'].plot(legend=True, lw=3)
ax.legend(['Rowwise', 'Columnwise'])
ax.set_xlabel('Test Trial')
ax.set_ylabel('Execution Time (s)')
_ = ax.set_xticks(7 * (pd.np.arange(len(end_rowwise))))
```


![png](output_17_0.png)



```python
title = 'Mean Times to Initialize and Transpose a ${N}$x${N}$ Matrix'
end_rowwise['avg'].plot(title=title.format(N=N), legend=True, lw=3)
ax = end_columnwise['avg'].plot(legend=True, lw=3)

ax.set_xlabel('Test Trial')
ax.set_ylabel('Mean Execution Time (s)')

ax = end_rowwise['total_avg'].plot(legend=True, style=['--'], lw=3)
ax = end_columnwise['total_avg'].plot(legend=True, style=['--'], lw=3)
ax.legend(['Rowwise (7th Trial)', 'Columnwise (7th Trial)', 'Rowwise (Total)', 'Columnwise (Total)'])

_ = ax.set_xticks(pd.np.arange(len(end_rowwise)) + 1)
```


![png](output_18_0.png)


 
