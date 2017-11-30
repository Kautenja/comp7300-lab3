
submission: zip paper
	rm -rf submission
	mkdir -p submission
	mv lab3-kauten-code.zip submission
	mv report/build/build.pdf submission/lab3-kauten-report.pdf

zip:
	mkdir -p lab3-kauten-code
	cp run.sh lab3-kauten-code
	cp myInitializeMatrix.c lab3-kauten-code
	cp rowwise.c lab3-kauten-code
	cp columnwise.c lab3-kauten-code
	cp README.md lab3-kauten-code
	pandoc --standalone lab3-kauten-code/README.md -o lab3-kauten-code/README.pdf
	cp -r best_run lab3-kauten-code
	zip -r lab3-kauten-code.zip lab3-kauten-code
	rm -rf lab3-kauten-code

paper:
	cd report && make pdf
