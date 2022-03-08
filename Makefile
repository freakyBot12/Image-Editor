build: image_editor

image_editor: image_editor.c
	gcc -Wall -Wextra image_editor.c -o image_editor

pack:
	zip -FSr 312CA_SeleaTudorOctavian_Tema3.zip README Makefile *.c *.h

clean:
	rm -f image_editor

.PHONY: pack clean