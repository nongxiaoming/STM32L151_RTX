#include "RTL.h"
#include "board.h"
#include "power.h"
#include "tasks.h"




__task void main_task(void) {

    led_task_init();

		os_tsk_delete_self();
}

int main(void)
{
	board_init();
	os_sys_init(main_task);
	
  /* ��Զ����ִ�е��������ϵͳ�쳣 */

  return 0;
}
