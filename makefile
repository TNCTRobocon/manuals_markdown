PANDOC?=/usr/bin/pandoc
MDS?=$(shell find -name '*.md')
TARGET?=$(shell basename $(PWD))
TARGET_PDF?=$(TARGET).pdf
.PHONY: all clean pdf
all: pdf
pdf: $(TARGET_PDF)
$(TARGET_PDF): $(MDS)
	$(PANDOC)  -N --toc --toc-depth=2 $^ -f markdown --pdf-engine=lualatex \
	-V documentclass=ltjsarticle -o $@
clean:
	rm -f $(TARGET_PDF)
