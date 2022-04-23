#!/usr/bin/env python3

"""
Created: 07/23/21
by: Lukas Schüttler

Plot data from a csv
"""

from typing import Literal
import pandas as pd
from matplotlib import pyplot as plt
import lib.path as path

linestyles = ['-', '-.', '--', ':']


def _getData(filepath, plottype: Literal['meas', 'sim']):
    """
      create dataframe from file
    """

    if plottype == 'meas':
        return pd.read_csv(filepath, ';', decimal=',')
    if plottype == 'sim':
        return pd.read_csv(filepath, delim_whitespace=True, decimal='.')


def _getLinestyle():
    """
      get linestyle depending on the number of axes
    """

    ax_i = len(plt.gca().lines)
    i = ax_i % 4
    return linestyles[i]


def _bodeConfig(ylabel, legend):
    """
      Configrue Bode Plot figure
    """

    plt.xticks(fontsize=10)
    plt.yticks(fontsize=10)
    plt.xlabel(r'f in Hz $\rightarrow$')
    plt.ylabel(ylabel)
    plt.grid(True, 'minor', 'x', linewidth=0.2)
    plt.grid(True, 'major', 'y', linewidth=0.3)
    plt.legend(legend)

    return plt


def bode(filename, legend=(), plottype: Literal['meas', 'sim'] = 'meas', fig=False, marker='o'):
    """
      Create a Bodeplot from a CSV-File

      Parameters
      ----------
        filename: str
          path to the file
        legend: list
          touple of strings to add as legend
        plottype: str
          Can be eather meas (for measurement) or sim (for simulation)
        fig: pyplot
          figure where a plot should be added
        linestyle: str
          Linestyle for the plot
        marker: str
          Marker for the plot (only added for Plots of type 'meas')

      Returns
      -----------
        Pyplot figure
    """

    linewidth = 0.8
    markersize = 2
    filepath = path.data(filename)

    if not fig:
        fig = plt
        fig.figure(figsize=(8, 6))

    df = _getData(filepath, plottype)
    linestyle = _getLinestyle()

    fig.subplot(2, 1, 1)

    if plottype == 'meas':
        plt.semilogx(df[df.columns[0]], df[df.columns[1]],
                     linestyle, marker=marker, ms=markersize, linewidth=linewidth)
    elif plottype == 'sim':
        plt.semilogx(df[df.columns[0]], df[df.columns[1]],
                     linestyle, linewidth=linewidth)

    _bodeConfig(r'Gain in dB $\rightarrow$', legend)

    fig.subplot(2, 1, 2)

    if plottype == 'meas':
        plt.semilogx(df[df.columns[0]], df[df.columns[2]],
                     linestyle, marker=marker, ms=markersize, linewidth=linewidth)
    elif plottype == 'sim':
        plt.semilogx(df[df.columns[0]], df[df.columns[2]],
                     linestyle, linewidth=linewidth)

    _bodeConfig(r'$\varphi$ in ° $\rightarrow$', legend)

    fig.tight_layout(h_pad=2)
    fig.count = 2

    return fig


def _timeConfig(ylabel, legend):
    """
      Configure Time Plot figure
    """

    plt.xticks(fontsize=10)
    plt.yticks(fontsize=10)
    plt.xlabel(r't in s $\rightarrow$')
    plt.ylabel(ylabel)
    plt.grid(True, 'both', linewidth=0.3)
    plt.legend(legend)

    return plt


def time(filename, y_label, legend=(), plottype: Literal['meas', 'sim'] = 'meas', fig=False, marker='o'):
    """
       Parameters
      ----------
        filename: str
          path to the file
        y_label: str
          Label for the y axis
        legend: list
          touple of strings to add as legend
        plottype: str
          Can be eather meas (for measurement) or sim (for simulation)
        fig: pyplot
          figure where a plot should be added
        linestyle: str
          Linestyle for the plot
        marker: str
          Marker for the plot (only added for Plots of type 'meas')

      Returns
      -----------
        Pyplot figure
    """

    linewidth = 0.8
    markersize = 2
    filepath = path.data(filename)

    if not fig:
        fig = plt
        fig.figure(figsize=(8, 4))

    df = _getData(filepath, plottype)
    df = df.set_index(df.columns[0])

    for _, data in df.iteritems():
        linestyle = _getLinestyle()

        if plottype == 'meas':
            plt.plot(data,
                     linestyle, marker=marker, ms=markersize, linewidth=linewidth)
        elif plottype == 'sim':
            plt.plot(data,
                     linestyle, linewidth=linewidth)

    _timeConfig(y_label, legend)

    return fig


if __name__ == "__main__":
    print(f"\033[90m{__doc__}\033[0m", end="\n")
