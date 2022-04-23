#!/usr/bin/env python3

"""
Created: 07/25/21
by: Lukas Schüttler

Test python modules
"""

import lib.plot as plot
import lib.path as path

print(f"\033[90m{__doc__}\033[0m", end="\n")

if __name__ == '__main__':
    path.init('')

    #fig = plot.bode('./bode_ges.txt', plottype='sim')
    # fig = plot.bode('./bode_messung.csv', fig=fig,
    #                marker='s', linestyle='-.', legend=('a', 'b'))
    fig = plot.time('trans_sim.txt', y_label="U in V", plottype='sim')
    fig = plot.time('trans_meas.csv', y_label="U in V", fig=fig)
    fig.savefig("./fig.png", dpi=500, format="png")
