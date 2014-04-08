#include "Tokenizer.h"

Tokenizer::Tokenizer() : tokens(new List()), current(NULL) {}

Tokenizer::~Tokenizer() {
	Node *node = tokens->head;
	while (node) {
		delete (String *)node->data;
		node = node->next;
	}
	delete tokens;
}

void Tokenizer::tokenize(const char *path) {
	char line[BUFFER], c;
	int ndx = 0;
   FILE *file = fopen(path, "r");
   if (not file) {throw "Could not open file\n"; return;}
   do {
   	c = fgetc(file);
		switch (c) {
			case '\n':
				*(line + ndx) = '\0';
				tokens->add(new String(line));
				tokens->add(new String("\n"));
				ndx = 0;
				break;
			case '/':
				*(line + ndx) = '\0';
				if (strlen(line) >= 1) tokens->add(new String(line));
				tokens->add(new String("/"));
				ndx = 0;
				break;
			case '\\':
				*(line + ndx) = '\0';
				if (strlen(line) >= 1) tokens->add(new String(line));
				tokens->add(new String("\\"));
				ndx = 0;
				break;
			case ' ':
			case '\t':
				*(line + ndx) = '\0';
				if (strlen(line) >= 1) tokens->add(new String(line));
				ndx = 0;
				break;
			default:
				*(line + ndx) = c;
				ndx++;
		}
   } while (c != EOF);
   fclose(file);
}

String *Tokenizer::nextToken() {
	String *string;
	if (!current) {
		current = tokens->head;
		string = (String *)current->data;
	} else if (current->next) {
		current = current->next;
		string = (String *)current->data;
	} else {
		current = NULL;
		string = NULL;
	}
	return string;
}
