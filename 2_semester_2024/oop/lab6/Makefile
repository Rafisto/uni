all: app

.PHONY:app
app:
	javac ./app/Main.java
	java app.Main

.PHONY:run
run:
	java app.Main

.PHONY:clean
clean:
	find . -name '*.class' -type f -delete