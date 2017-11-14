TEXFN=tech_review

all: pdf

dvi: ${TEXFN}.tex
	latex $(TEXFN).tex
	#bibtex $(TEXFN)
	latex $(TEXFN).tex

ps: dvi
	dvips -R -Poutline -t letter ${TEXFN}.dvi -o ${TEXFN}.ps

pdf: ps
	ps2pdf ${TEXFN}.ps
	rm -f ${TEXFN}.aux
	rm -f ${TEXFN}.log
	rm -f ${TEXFN}.dvi
	rm -f ${TEXFN}.out
	rm -f ${TEXFN}.ps
	rm -f $(TEXFN).toc

clean-dvi:
	rm -f ${TEXFN}.aux
	rm -f ${TEXFN}.log
	rm -f ${TEXFN}.dvi
	rm -f ${TEXFN}.out
	rm -f ${TEXFN}.toc
	rm -f ${TEXFN}.blg
	rm -f ${TEXFN}.bbl

clean-ps: clean-dvi
	rm -f ${TEXFN}.ps

clean-pdf: clean-ps
	rm -f ${TEXFN}.pdf

clean: clean-pdf
