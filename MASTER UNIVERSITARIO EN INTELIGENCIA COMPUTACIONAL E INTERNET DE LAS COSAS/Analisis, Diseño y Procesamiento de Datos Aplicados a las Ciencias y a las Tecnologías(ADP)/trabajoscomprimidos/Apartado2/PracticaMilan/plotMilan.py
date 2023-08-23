__author__ = 'Marco De Nadai'
__license__ = "MIT"

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from math import sqrt
import datetime


parse = lambda x: datetime.datetime.fromtimestamp(float(x)/1000)

fig_width_pt = 345  # Get this from LaTeX using \showthe\columnwidth
inches_per_pt = 1.0/72.27               # Convert pt to inches
golden_mean = (sqrt(5)-1.0)/2.0         # Aesthetic ratio
fig_width = fig_width_pt*inches_per_pt  # width in inches
fig_height = fig_width*golden_mean       # height in inches
fig_size = [fig_width, fig_height]

sns.set_style("ticks")
sns.set_context("paper")

# Import dataset - Milano
sliceSum = pd.DataFrame({})
for index in range(18, 25):
    sliceSum2 = pd.read_csv('sms-call-internet-mi-2013-11-'+str(index).zfill(2) +'.txt', sep='\t', encoding="utf-8-sig", names=['CellID', 'datetime', 'countrycode', 'smsin', 'smsout', 'callin', 'callout', 'internet'], parse_dates=['datetime'], date_parser=parse)
    sliceSum2 = sliceSum2.set_index('datetime')
    sliceSum2['hour'] = sliceSum2.index.hour
    sliceSum2['weekday'] = sliceSum2.index.weekday
    sliceSum2 = sliceSum2.groupby(['hour', 'weekday', 'CellID'], as_index=False).sum()

    sliceSum = sliceSum.append(sliceSum2)

sliceSum['idx'] = sliceSum['hour'] + (sliceSum['weekday']*24)
sliceSum.head()

# Group by weekday-hour
sliceSum_city = sliceSum.groupby(['weekday', 'hour'], as_index=False).sum()
sliceSum_city['sms'] = sliceSum_city['smsin'] + sliceSum_city['smsout']
sliceSum_city['calls'] = sliceSum_city['callin'] + sliceSum_city['callout']
sliceSum_city.rename(columns={'sms': 'SMS', 'internet': 'Internet'}, inplace=True)

# Behaviour plot
types = ['SMS', 'calls', 'Internet']
fig_size2 = [fig_width, fig_width*golden_mean*2 ]
f, axs = plt.subplots(len(types), sharex=True, sharey=True,figsize=fig_size2)

# Z-score
sliceSum_z = (sliceSum_city - sliceSum_city.mean()) / sliceSum_city.std()

for i, p in enumerate(types):
    plt.xticks(np.arange(168, step=10))
    axs[i].plot(sliceSum_z[p], label=p)
    axs[i].legend(loc='upper center')
    sns.despine()

f.text(0, 0.5, "Number of events", rotation="vertical", va="center")

plt.xlabel("Hour (in a week)")
plt.savefig('behaviour.pdf', format='pdf', dpi=330,bbox_inches='tight')

# Import dataset Telecommunications - Trentino
sliceSum3 = pd.DataFrame({})
for index in range(18, 25):
    sliceSum2 = pd.read_csv('sms-call-internet-mi-2013-11-'+str(index).zfill(2) +'.txt', sep='\t', encoding="utf-8-sig", names=['CellID', 'datetime', 'countrycode', 'smsin', 'smsout', 'callin', 'callout', 'internet'], parse_dates=['datetime'], date_parser=parse)
    sliceSum2 = sliceSum2.set_index('datetime')
    sliceSum2['hour'] = sliceSum2.index.hour
    sliceSum2['weekday'] = sliceSum2.index.weekday
    sliceSum2 = sliceSum2.groupby(['hour', 'weekday', 'CellID'], as_index=False).sum()

    sliceSum3 = sliceSum3.append(sliceSum2)

sliceSum3['idx'] = sliceSum3['hour'] + (sliceSum3['weekday']*24)
sliceSum3.head()

# Validation behavioural plots
fig_size2 = [fig_width,fig_width*golden_mean*1.5 ]
fig = plt.figure(figsize=fig_size2)

f, axs = plt.subplots(1, sharex=True, sharey=False, figsize=fig_size2)

axs.plot(sliceSum[sliceSum.CellID == 5060].set_index('idx')['internet'], label='Duomo')
axs.plot(sliceSum[sliceSum.CellID == 4259].set_index('idx')['internet'], label='Bocconi')
axs.plot(sliceSum[sliceSum.CellID == 4456].set_index('idx')['internet'], label='Navigli')

axs.plot(sliceSum[sliceSum.CellID == 1419].set_index('idx')['internet'], label='terreno de agricultura')
axs.plot(sliceSum[sliceSum.CellID == 2436].set_index('idx')['internet'], label='área industrial')
axs.plot(sliceSum[sliceSum.CellID == 4990].set_index('idx')['internet'], label='aeropuerto de Linate')
axs.plot(sliceSum[sliceSum.CellID == 945].set_index('idx')['internet'], label='residencial aislado')
axs.plot(sliceSum[sliceSum.CellID == 5048].set_index('idx')['internet'], label='residencial céntrico')
axs.set_xticklabels([])
sns.despine()
# Shrink current axis's height by 10% on the bottom
box = axs.get_position()
axs.set_position([box.x0, box.y0 + box.height * 0.1, box.width, box.height * 0.9])
axs.legend(loc='upper center', bbox_to_anchor=(0.5, -0.10), fancybox=True, shadow=True, ncol=5)
"""axs[1].plot(sliceSum3[sliceSum3.CellID == 5200].set_index('idx')['internet'], label='Duomo')
axs[1].plot(sliceSum3[sliceSum3.CellID == 5085].set_index('idx')['internet'], label='Mesiano')
axs[1].plot(sliceSum3[sliceSum3.CellID == 4703].set_index('idx')['internet'], label='Bosco')

axs[1].plot(sliceSum3[sliceSum3.CellID == 1419].set_index('idx')['internet'], label='terreno de agricultura')
axs[1].plot(sliceSum3[sliceSum3.CellID == 2436].set_index('idx')['internet'], label='área industrial')
axs[1].plot(sliceSum3[sliceSum3.CellID == 4990].set_index('idx')['internet'], label='aeropuerto de Linate')
axs[1].plot(sliceSum3[sliceSum3.CellID == 945].set_index('idx')['internet'], label='residencial aislado')
axs[1].plot(sliceSum3[sliceSum3.CellID == 5048].set_index('idx')['internet'], label='residencial céntrico')
# Shrink current axis's height by 10% on the bottom
box = axs[1].get_position()
axs[1].set_position([box.x0, box.y0 + box.height * 0.05, box.width, box.height * 0.9])
axs[1].legend(loc='upper center', bbox_to_anchor=(0.5, -0.30), fancybox=True, shadow=True, ncol=5)
axs[1].set_xlabel("Weekly hour")
sns.despine()"""

f.text(0, 0.5, "Absolute number of connections", rotation="vertical", va="center")
plt.savefig('validation-Milano.pdf', format='pdf', dpi=330, bbox_inches='tight')

# Boxplots
boxplots = {
    'calls': "Calls",
    'sms': "SMS",
    "internet": "Internet CDRs"
}
fig_size2 = [fig_width, fig_width*golden_mean*2]
f, axs = plt.subplots(len(boxplots.keys()), sharex=True, sharey=False, figsize=fig_size2)
f.subplots_adjust(hspace=.35,wspace=0.1)
sliceSum['sms'] = sliceSum['smsin'] + sliceSum['smsout']
sliceSum['calls'] = sliceSum['callin'] + sliceSum['callout']
i = 0
plt.suptitle("")
for k, v in boxplots.items():

    ax = sliceSum.reset_index().boxplot(column=k, by='weekday', grid=False, sym='', ax =axs[i])
    axs[i].set_title(v)
    axs[i].set_xlabel("")
    sns.despine()
    i += 1

plt.xlabel("Weekday (0=Monday, 6=Sunday)")
f.text(0, 0.5, "Number of events", rotation="vertical", va="center")
plt.savefig('boxplots-Milano.pdf', format='pdf', dpi=330,bbox_inches='tight')




