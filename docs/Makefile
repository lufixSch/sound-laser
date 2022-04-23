# Minimal makefile for Latex protocol template
#

# You can set these variables from the command line, and also
# from the environment.
OUTDIR      	?= build
DOC						?= %ENTRYPOINT%

# Put it first so that "make" without argument is like "make help".
help:


.PHONY: help Makefile

# create PDF with xelatex
pdf:
	@xelatex -synctex=1 -interaction=nonstopmode -file-line-error -output-directory=$(OUTDIR) $(DOC)

# clean buildfolder and create pdf
clean:
	@rm -R ./build
	@make pdf

# push to Bitbucket and GitHub
push:
	@git push
	@git push "git@github.com:lufixSch/protokoll_vorlage.git"

pull-github:
	@git pull "git@github.com:lufixSch/protokoll_vorlage.git"

# run setup script
init:
	@/usr/bin/env python3 ./setup/setup.py