all: app

.PHONY:app
app:
	javac ./Main.java 

.PHONY:test
test:
	javac ./Test.java

.PHONY:regression
regression:
	$(MAKE) app --no-print-directory
	$(MAKE) test --no-print-directory
	java -ea Test

.PHONY:pmd
pmd:
	/home/rafisto/pmd-bin-7.0.0-rc4/bin/pmd check -d ./ -R ./pmdRules.xml -f text


.PHONY:clean
clean:
	rm -rf *.class