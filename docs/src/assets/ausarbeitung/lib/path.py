#!/usr/bin/env python3

"""
Created: 08/01/21
by: Lukas Schüttler

initialize and create paths for images or csv's
"""

import os


def init(prefix: str):
    """ save lab prefix as environment variable """

    os.environ['lab_pref'] = prefix


def image(name: str):
    """ create imagepath """

    lib_path = os.path.dirname(__file__)
    pref = os.environ['lab_pref']

    return os.path.abspath(os.path.join(lib_path, '..', '..', 'pictures', pref, name))


def table(name: str):
    """ create imagepath """

    lib_path = os.path.dirname(__file__)
    pref = os.environ['lab_pref']

    return os.path.abspath(os.path.join(lib_path, '..', '..', 'tables', pref, name))


def data(name: str):
    """ create datapath """

    lib_path = os.path.dirname(__file__)
    pref = os.environ['lab_pref']

    return os.path.abspath(os.path.join(lib_path, '..', pref, name))


if __name__ == '__main__':
    print(f"\033[90m{__doc__}\033[0m", end="\n")
