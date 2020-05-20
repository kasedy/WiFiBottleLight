#include "helpers.h"

#include <cctype>
#include <cstring>

const char* makeSafeName(const char *name) {
  size_t nameLength = strlen(name);

  char buffer[nameLength];
  memcpy(buffer, name, nameLength);

  size_t resultSize = 0;
  for (size_t i = 0; i < nameLength; ++i) {
    char chr = tolower(buffer[i]);
    if (isalnum(chr)) {
      buffer[resultSize++] = chr;
    } else if (resultSize > 0 && buffer[resultSize - 1] != '_') {
      buffer[resultSize++] = '_';
    }
  }

  if (resultSize > 0 && buffer[resultSize - 1] == '_') {
    --resultSize;
  }

  char *result = new char[resultSize + 1];
  memcpy(result, buffer, resultSize);
  result[resultSize] = 0;
  return result;
}