#ifndef TEXT_PROCESS
#define TEXT_PROCESS

extern QueueHandle_t Upper_Queue;
extern QueueHandle_t Lower_Queue;
extern QueueHandle_t Processed_Queue;

void Init_Text_Process ( void      );
void Upper_Task        ( void* nil );
void Lower_Task        ( void* nil );
void Print_Line_Task   ( void* nil );

#endif