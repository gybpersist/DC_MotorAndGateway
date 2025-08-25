#ifndef __COM_DEBUG_H__
#define __COM_DEBUG_H__

#include <stdio.h>
#include <string.h>
#include "usart.h"

#define DEBUG_MODE  // ����һ���꣬���ڿ�����رյ���ģʽ (ͨ�������ע�͵�������������رյ���ģʽ)

#ifdef DEBUG_MODE
// ����һ���꣬���ڻ�ȡ�ļ�����������·����
#define __FILE_NAME_PER__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define __FILE_NAME__ (strrchr(__FILE_NAME_PER__, '\\') ? strrchr(__FILE_NAME_PER__, '\\') + 1 : __FILE_NAME_PER__)
// ����:  DEBUG_PRINTF("hello world!\n");  -->  [main.c:93]hello world!
#define DEBUG_PRINTF(format,...) printf("[%s:%d]" format,__FILE_NAME__,__LINE__,##__VA_ARGS__)
#define DEBUG_PRINTLN(format,...) printf("[%s:%d]" format "\n",__FILE_NAME__,__LINE__,##__VA_ARGS__)
#define debug_printf(format,...) printf("[%s:%d]" format,__FILE_NAME__,__LINE__,##__VA_ARGS__)
#define debug_printfln(format,...) printf("[%s:%d]" format "\n",__FILE_NAME__,__LINE__,##__VA_ARGS__)
#else
#define DEBUG_PRINTF(format,...)
#define DEBUG_PRINTLN(format,...)
#define debug_printf(format,...)
#define debug_printfln(format,...)
#endif // DEBUG_MODE

#endif /* __COM_DEBUG_H__ */
