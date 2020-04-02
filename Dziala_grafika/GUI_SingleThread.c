
#include "cmsis_os2.h"
#include "GUI.h"
#include "DIALOG.h"
extern WM_HWIN CreateFramewin(void);
extern WM_HWIN CreateWindow(void);

/*----------------------------------------------------------------------------
 *      GUIThread: GUI Thread for Single-Task Execution Model
 *---------------------------------------------------------------------------*/
#define GUI_THREAD_STK_SZ    (2048U)

static void         GUIThread (void *argument);         /* thread function */
static osThreadId_t GUIThread_tid;                      /* thread id */
static uint64_t     GUIThread_stk[GUI_THREAD_STK_SZ/8]; /* thread stack */

static const osThreadAttr_t GUIThread_attr = {
  .stack_mem  = &GUIThread_stk[0],
  .stack_size = sizeof(GUIThread_stk),
  .priority   = osPriorityIdle 
};

int Init_GUIThread (void) {

  GUIThread_tid = osThreadNew(GUIThread, NULL, &GUIThread_attr);
  if (GUIThread_tid == NULL) {
    return(-1);
  }

	//CreateFramewin();
	//CreateWindow();
	GUIThread(CreateWindow);

//	GUI_DispString("Hello World! /n  \n Co tam /n \n               XYZ pzdr");
  return(0);
}

__NO_RETURN static void GUIThread (void *argument) {
  (void)argument;

            /* Initialize the Graphics Component */
	CreateWindow();

  /* Add GUI setup code here */
	
	

	 
  while (1) {
    
    /* All GUI related activities might only be called from here */
		
    GUI_Exec();         /* Execute all GUI jobs ... Return 0 if nothing was done. */
    GUI_X_ExecIdle();   /* Nothing left to do for the moment ... Idle processing */
  }
}
