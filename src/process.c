#include <string.h>
#include <ctype.h>
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "queue.h"
#include "task.h"
#include "sapi.h"

#include "qmpool.h"
#include "rx_parser.h"
#include "process.h"
#include "pool.h"

extern DEBUG_PRINT_ENABLE;

QueueHandle_t Upper_Queue;
QueueHandle_t Lower_Queue;

void Init_Process(void)
{
   Upper_Queue=xQueueCreate(10,sizeof(Line_t));
   Lower_Queue=xQueueCreate(10,sizeof(Line_t));
}

Line_t* To_Uppercase(Line_t* L)
{
   uint8_t i;
   for(i=0;i<L->T;i++)
      L->Data[i]=toupper(L->Data[i]);
  return L;
}
Line_t* To_Lowercase(Line_t* L)
{
   uint8_t i;
   for(i=0;i<L->T;i++)
      L->Data[i]=tolower(L->Data[i]);
  return L;
}

void Upper_Task( void* nil )
{
   Line_t L;
   while(TRUE) {
      while (xQueueReceive(Upper_Queue,&L,portMAX_DELAY)==pdFAIL)
         ;
      To_Uppercase(&L);
      Print_Line(&L);
      Pool_Put4Line(&L);
   }
}
void Lower_Task( void* nil )
{
   Line_t L;
   while(TRUE) {
      while (xQueueReceive(Lower_Queue,&L,portMAX_DELAY)==pdFAIL)
         ;
      To_Lowercase(&L);
      Print_Line(&L);
      Pool_Put4Line(&L);
   }
}
