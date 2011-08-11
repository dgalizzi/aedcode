Ejercicios.pdf: generate.lua
	lua generate.lua > ejercicios.tex
	pdflatex ejercicios.tex
	rm ejercicios.tex ejercicios.log ejercicios.aux

.PHONY: clean

clean:
	rm ejercicios.pdf
