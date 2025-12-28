#ifndef __PARSER_EXPORT__
#define __PARSER_EXPORT__

#include <assert.h>

typedef struct lex_data_ {

    int token_code;
    int token_len;
    char* token_val;

} lex_data_t;

#define MAX_MEXPR_LEN  512
#define MAX_STRING_SIZE 512
#define PARSER_EOL  10000
#define PARSER_WHITE_SPACE 10002


typedef struct stack_ {

    int top;
    lex_data_t data[MAX_MEXPR_LEN];
} stack_t;

stack_t undo_stack = {-1, {0, 0, 0}};

extern "C" int yylex();

extern char lex_buffer[MAX_MEXPR_LEN];
extern stack_t undo_stack;
extern char *curr_ptr;
extern int cyylex();
extern void yyrewind();
extern void parser_stack_reset();
extern void lex_set_scan_buffer();

#define CHECKPOINT(a) a = undo_stack.top
#define RESTORE_CHKP(a) = yyrewind(undo_stack.top - a)

#endif