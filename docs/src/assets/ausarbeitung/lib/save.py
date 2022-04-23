#!/usr/bin/env python3

"""
Created: 07/23/21
by: Lukas Schüttler

Save plot or other displayed elements as pdf or png
"""

from typing import Tuple
import lib.path as path
from pandas import DataFrame


def toPDF(filename, figure):
    """
      Save figure to pdf
    """

    figure.savefig(path.image(filename), format="pdf", bbox_inches="tight")


def toIMG(filename, figure):
    """
      Save figure to png
    """

    figure.savefig(path.image(filename), format="png",
                   bbox_inches="tight", dpi=500)


if __name__ == '__main__':
    print(f"\033[90m{__doc__}\033[0m", end="\n")


def toTable(filename: str, data: DataFrame, caption: str, label: str, formatter: Tuple = None):
    latex = data.to_latex(caption=caption, label=label,
                          position="ht", na_rep="-", decimal=',', formatters=formatter, escape=True)
    latex = latex.split("\n")

    caption = [latex.pop(2), latex.pop(2)]

    latex.insert(-2, caption[0])
    latex.insert(-2, caption[1])

    with open(path.table(filename), 'w') as tab:
        for _, line in enumerate(latex):
            tab.write(f'{line}\n')
