# constants for the file
# the binary location of `pip` the python package installer
PIP=pip3
# the binary location of `python` the python interpretter for the machine
PYTHON=python3
# the linux package manager
APTGET=sudo apt-get
# the macos packager manager
BREW=brew
# the build directory for the project
BUILD=build
# the file to zip the final build into
ZIP_BUILD=${BUILD}.zip

#
# MARK: Installation Scripts
#

# do the full installation on a Linux machine using apt-get
linux_install:
	${APTGET} -qq update
	${APTGET} install -y --no-install-recommends texlive-full pandoc pandoc-citeproc

# do the full installation on a MacOS machine using brew
macos_install:
	${BREW} update
	${BREW} cask install mactex
	${BREW} install pandoc
	${BREW} install pandoc-citeproc

#
# MARK: Markdown Compilation
#

# Compile a document using pandoc
# Args:
# 	1: the output file type (i.e. 'tex' or 'pdf')
define pandoc_compile
	pandoc ${BUILD}/${BUILD}.md \
		-o ${BUILD}/${BUILD}.$(1) \
		--template=${BUILD}/template.tex
endef

# make the master markdown file
markdown:
	${PYTHON} src/python/compile.py

# generate a latex document
tex: markdown
	$(call pandoc_compile,tex)

# generate a pdf document using pdflatex and bibtex on the LaTeX build artifact
# This block looks redundant and dumb, but is the official recipe for compiling
# with Bibtex...
pdf: tex
	cd ${BUILD}; \
	pdflatex ${BUILD}; \
	bibtex ${BUILD}; \
	pdflatex ${BUILD}; \
	pdflatex ${BUILD}

#
# MARK: Deployment
#

# make all the buildables and zip them up
zip:
		zip -r ${ZIP_BUILD} ${BUILD}
