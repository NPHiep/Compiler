#ifndef __SCANNER_H__
#define __SCANNER_H__

#include "token.h"

void skipBlank();
void skipComment();
Token* readIdentKeyword(void);
Token* readNumber(void);
Token* readConstChar(void);
Token* getToken(void);

#endif /* _SCANNER_H_ */
