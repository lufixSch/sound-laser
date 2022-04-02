#!/usr/bin/evn python3

"""
  Created: 5/13/21
  by: Lukas Schuettler

  Setupscript for the LaTex protocol template
"""


import argparse
import os
import subprocess as sp
import datetime
import requests

_main_file = r'main.tex'
_params_file = r'params.tex'
_assets = os.path.join('src', 'assets', 'privat')

arg_def = {
    "lecture": ("-l", "--lecture", "name of the lecture"),
    "lecture_short": ("-ls", "--lecture-short", "short form of the lecture"),
    "name": ("-n", "--name", "name of the protocol"),
    "count": ("-c", "--count", "number of the protocol"),
    "repo": ("-r", "--repo", "link to a repository (Optional)"),
    "token": ("-t", "--token", "token for private images (Optional)")
}

parser = argparse.ArgumentParser()

for key in arg_def:
    short, cmd, description = arg_def[key]
    parser.add_argument(short, cmd, help=description)

args = parser.parse_args().__dict__

for key in args:
    arg = args[key]

    if arg is None:
        args[key] = input(f'{arg_def[key][2]}: ')

filename = f'{args["lecture_short"]}_lab{args["count"]}_protokoll.tex'

os.rename(_main_file, filename)

date = datetime.datetime.now().strftime(r'%d.%m.%Y')

params = open(_params_file)
params_str = params.read()
params.close()

params_str = params_str.replace(
    '$COUNT$', args['count']).replace(
    '$NAME$', args['name']).replace(
    '$LECTURE$', args['lecture']).replace(
    '$DATE$', date)

params = open(_params_file, 'w')
params.write(params_str)
params.close()

makefile = open(r'Makefile',)
content = makefile.read()
makefile.close()

makefile = open(r'Makefile', 'w')
makefile.write(content.replace('%ENTRYPOINT%', filename))
makefile.close()

print(f'Protocol {args["count"]} from the '
      f'lecture {args["lecture"]} ({args["lecture_short"]}) '
      f'with the name {args["name"]} initialized')

sp.call('git remote rename origin vorlage', shell=True)
sp.call('git branch -m master vorlage-master', shell=True)

if args['repo']:
    sp.call(f'git remote add origin {args["repo"]}', shell=True)

    sp.call('git checkout -b master', shell=True)
    sp.call('git push --set-upstream origin master', shell=True)
    print('new repository initialized')
else:
    sp.call('git checkout -b master', shell=True)
    print('no new repository initialized')

load_sign = input('Load private signatures (Y/n): ')

if load_sign == "Y":
    tokens = args['token'].split('#')

    sign_ls = requests.get(
        f'https://firebasestorage.googleapis.com/v0/b/lufixsch-cdn.appspot.com/o/unterschriften%2Fsign_ls.png?alt=media&token={tokens[0]}').content
    with open(os.path.join(_assets, 'sign_ls.png'), 'wb') as handler:
        handler.write(sign_ls)

    sign_ts = requests.get(
        f'https://firebasestorage.googleapis.com/v0/b/lufixsch-cdn.appspot.com/o/unterschriften%2Fsign_ts.png?alt=media&token={tokens[1]}').content
    with open(os.path.join(_assets, 'sign_ts.png'), 'wb') as handler:
        handler.write(sign_ts)

    print('private pictures loaded')

print('repository structured')
