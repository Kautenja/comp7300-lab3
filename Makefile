
zip:
	mkdir -p lab3-kauten-code
	cp run.sh lab3-kauten-code
	cp myInitializeMatrix.c lab3-kauten-code
	cp rowwise.c lab3-kauten-code
	cp columnwise.c lab3-kauten-code
	cp README.md lab3-kauten-code
	zip lab3-kauten-code.zip lab3-kauten-code/*
	rm -rf lab3-kauten-code