
SUBDIRS = bitsetter bittester linkcable looptest queuetest

all:
	for dir in $(SUBDIRS); do make -C $$dir $@; done
	
clean realclean:
	for dir in $(SUBDIRS); do make -C $$dir $@; done

