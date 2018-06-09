#include <iostream>
#include "errorhandle.h"

using namespace std;

void init_error_handle(void);
void close_error_handle(void);
void PrintRow(void); 
int  GetNextChar(char *b, int maxBuffer);
void BeginToken(char*);
void PrintError(char *s, ...);

static int eof=0;
static int row_number=0;
static int Buffer_length=0;
static int Buffer_next=0;//lex 的下一个字符
static int TokenStart=0;//bison token start
static int TokenLength=0;//bison token length
static int TokenNextStart=0;
static int BufferMaxLen=2000;
static char *buffer;

void init_error_handle()
{
    buffer = (char*)malloc(BufferMaxLen);
}
void close_error_handle()
{
    free(buffer);
}
void PrintRow()
{
    if (row_number == 0) return;
    fprintf(stdout,"%6d |%.*s",row_number,Buffer_length,buffer);
}
void PrintError(char* s, ...)
{
    static char errmsg[10000];
    va_list args;

    int start=TokenStart;
    int end=start + TokenLength - 1;
    int i;
    PrintRow();
    /*================================================================*/
    /* simple version ------------------------------------------------*/
    /*^在错误后面-------------------------------------------------------*/
    /*
        fprintf(stdout, "...... !");
        for (i=0; i<Buffer_next; i++)
        fprintf(stdout, ".");
        fprintf(stdout, "^\n");
    */

    /*================================================================*/
    /* a bit more complicate version ---------------------------------*/
    /* 标记指示错误位置--------------------------------------------------*/
    /* */
    if (  eof  ) {
        fprintf(stdout, "...... !");
        for (i=0; i<Buffer_length; i++)
        fprintf(stdout, ".");
        fprintf(stdout, "^-EOF\n");
    }
    else {
        fprintf(stdout, "...... !");
        for (i=1; i<start; i++)
        fprintf(stdout, ".");
        for (i=start; i<=end; i++)
        fprintf(stdout, "^");
        for (i=end+1; i<Buffer_length; i++)
        fprintf(stdout, ".");
        fprintf(stdout, "   token from %d to %d\n", start, end);
    }
    /* */

    /*================================================================*/
    /* print it using variable arguments -----------------------------*/
    va_start(args, errorstring);
    vsprintf(errmsg, errorstring, args);
    va_end(args);
    
    fprintf(stdout, "Error: %s\n", errmsg);
}
//to buffer
int getNextLine()
{
    int i;
    char *p;
    
    Buffer_next = 0;
    TokenStart = -1;
    TokenNextStart = 1;
    eof = false;

    p = fgets(buffer, BufferMaxLen, file);
    if (  p == NULL  ) {
        if (  ferror(file)  )
        return -1;//error
        eof = true;
        return 1;//tail
    }

    row_number += 1;
    Buffer_length = strlen(buffer);

    return 0;
}
int GetNextChar(char* b,int maxLen)
{
    if (eof) return 0;
    //这一行解析完了，就读下一行
    while (Buffer_next>=Buffer_length)
    {
        if (getNextLine()!=0) return 0;
    }
    b[0]=buffer[Buffer_next];
    Buffer_next++;
    return b[0]==0?0:1;
}
void BeginToken(char *t)
{
    TokenStart=TokenNextStart;
    TokenLength=strlen(t);
    TokenNextStart=Buffer_next;

    yylloc.first_line = row_number;
    yylloc.first_column = TokenStart;
    yylloc.last_line = row_number;
    yylloc.last_column = TokenStart + TokenLength - 1;

}

