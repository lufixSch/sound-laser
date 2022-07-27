# Minimal makefile for Latex protocol template
#

# You can set these variables from the command line, and also
# from the environment.
OUTDIR      	?= build
DOC						?= SoundLaser_Thesis

# Put it first so that "make" without argument is like "make help".
help:


.PHONY: help Makefile

# create PDF with latexmk
latexmk:
	@latexmk -synctex=1 -interaction=nonstopmode -file-line-error -pdf -outdir=$(OUTDIR) $(DOC).tex -f

# create glossary
glossary:
	@makeglossaries -d $(OUTDIR) $(DOC)

# create pdf with glossary
pdf:
	@make latexmk
	@make glossary
	@make latexmk

# clean buildfolder and create pdf
clean:
	@rm -R ./build
	@make pdf