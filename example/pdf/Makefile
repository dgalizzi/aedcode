.PHONY: clean Ejercicios.pdf

Ejercicios.pdf: generate.lua
	lua generate.lua > Ejercicios.tex
	pdflatex Ejercicios.tex
	rm Ejercicios.tex Ejercicios.log Ejercicios.aux

clean:
	rm Ejercicios.pdf
