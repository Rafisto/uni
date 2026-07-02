DIRS=$(shell ls -d */Makefile 2>/dev/null | sed 's:/Makefile::')

run:
	for dir in $(DIRS); do \
		make -C $$dir; \
	done

clean:
	for dir in $(DIRS); do \
		make -C $$dir clean; \
	done