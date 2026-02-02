build:
	gcc src/core/kotel.c -Iinclude/ -Llib/ -lm -llua55  -lcurl -o bin/kotel
debug:
	gcc src/core/kotel.c -Iinclude/ -Llib/ -lm -llua55 -lcurl -lyaml -o bin/kotel-debug -g
