SUBDIRS=basics conditionals converters file loops operations utilities

clean:
	for i in $(SUBDIRS); do \
		cd "$$i" && $(MAKE) clean $@; \
		cd ..; \
	done

all:
	for i in $(SUBDIRS); do \
		cd "$$i" && $(MAKE) all $@; \
		cd ..; \
	done
