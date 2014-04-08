#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "List.h"
#include "Object.h"
#include "String.h"

#define BUFFER 32

class Tokenizer {
   private:
      List *tokens;
      Node *current;
   public:
      Tokenizer();
      ~Tokenizer();
      void tokenize(const char *path);
      String *nextToken();
};

#endif
