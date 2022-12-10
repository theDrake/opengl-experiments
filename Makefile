all: connect-four fractal

connect-four: connect-four-src/*
	g++ connect-four-src/*.cc -lglut -lGL -lGLU -o connect-four

fractal: fractal-src/*
	g++ fractal-src/*.cc -lglut -lGL -lGLU -o fractal

.PHONY: all clean

clean:
	rm -f connect-four fractal
