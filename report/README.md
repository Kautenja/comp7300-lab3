# Assignment 2 Report

[![ci-status][]][ci-home]

## Getting Started

These instructions will get you a copy of the project up and running on your
local machine for development and testing purposes. See deployment for notes on
how to deploy the project on a live system.

### Prerequisites

This application is dependency managed using [pip3][pip], the [python3][python]
package manager.

### Makefile

[Makefile][] contains quick shortcuts for basic activities in the command line.

### Installing

#### Linux

```shell
make linux_install
```
will install [LaTeX][], [pandoc][] (and [pypandoc][]) using `sudo apt-get`.

#### MacOS

```shell
make macos_install
```
will install [MacTeX][], [pandoc][] (and [pypandoc][]) using [`brew`][brew].

#### Windows

Windows users can use a virtual machine or [Cygwin][] and follow the Linux
instructions. If any advanced Windows user knows a better way of accessing the
Linux tools for this project using the command prompt, PRs are welcome.

## Usage

### Writing

This repository models a web design project. The [src][] directory contains a
hierarchy of subdirectories containing files of a certain filetype:
*   [src/bib][] - the folder with references files for the paper
*   [src/csl][] - the folder with reference styling files for LaTeX
*   [src/md][] - markdown files
    *   this is where all the writing happens
    *   [src/md/img][] this is where all figures go
*   [src/python][] - Python code files
    *   automation, filters, etc.
*   [src/sty][] - custom LaTeX styles that are being used
*   [src/tex][] - LaTeX layout files
    *   this is where the central (and any other) LaTeX layout files live

### Building

These scripts compile all the markdown in [src/md][] in _alphanumeric_
order into any output files in [build][]. They will look for images in
[src/md/img][].

#### Markdown

```shell
make markdown
```

#### LaTeX

This will first compile a markdown file, then a LaTeX one.

```shell
make tex
```

#### PDF

This will first compile a LaTeX file, then a PDF.

```shell
make pdf
```

## Deployment

This project is setup to deploy to Github using Travis-CI. Follow instructions
[here][travis-releases] to setup automatic deployment for your repositories.
Becuase this boilerplate project is public, I wont post my credentials. It's
possible to encrypt credentials for public projects, but I am too lazy to do
that right now.

## Built With

*   [python3][python] - Scripting
*   [pandoc][] - Production documents
    *   [pypandoc][] - Python wrapper around [pandoc][]
    *   [LaTeX][] - Formatting
    *   [MacTeX][] - MacOS LaTeX support
*   [travis-ci][] - Build Automation

## Acknowledgements

*   [src/python/table-filter.py][] is credited to [Wagner Macedo][].
*   [src/csl/ieee.csl][] is credited to [pandoc ieee.csl][]



<!-- Link shortcuts -->

<!-- Badges -->
[ci-status]: https://travis-ci.com/Kautenja/comp7970-assignment02-Report.svg?token=FCkX2qMNHzx2qWEzZZMP&branch=master
[ci-home]: https://travis-ci.com/Kautenja/comp7970-assignment02-Report

<!-- Project files -->
[Makefile]: ./Makefile
[build]: ./build
[src]: ./src
[src/md]: ./src/md
[src/md/img]: ./src/md/img
[src/tex]: ./src/tex
[src/python]: ./src/python
[src/bib]: ./src/bib
[src/csl]: ./src/csl
[src/python/table-filter.py]: ./src/python/table-filter.py
[src/csl/ieee.csl]: ./src/csl/ieee.csl

<!-- References -->
[Cygwin]: https://www.cygwin.com
[brew]: https://brew.sh
[pip]: https://pip.pypa.io/en/stable/
[python]: https://www.python.org
[pandoc]: https://pandoc.org
[pypandoc]: https://pypi.python.org/pypi/pypandoc
[LaTeX]: https://www.latex-project.org/about/
[MacTeX]: http://www.tug.org/mactex/
[travis-ci]: https://travis-ci.org/
[travis-releases]: https://docs.travis-ci.com/user/deployment/releases/

<!-- Acknowledgments -->
[Wagner Macedo]: https://groups.google.com/forum/#!msg/pandoc-discuss/RUC-tuu_qf0/h-H3RRVt1coJ
[pandoc ieee.csl]: http://pandoc.org/demo/ieee.csl
