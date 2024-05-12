all: app

.PHONY:app
app:
	javac ./app/Main.java
	javac ./app/controller/GUIController.java
	java app.Main

.PHONY:run
run:
	java app.Main

.PHONY:clean
clean:
	find . -name '*.class' -type f -delete