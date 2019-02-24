#include <linux/linkage.h>	/*使用 ENTRY 和 ENDPROC必须引入该头文件*/
/*
*点亮板上的led，用于接到板后的第一步确认SP设置是否正确
*/
       .globl light_led_asm
light_led_asm:		/*这种写法只能被汇编调用*/
       ldr     r0,=0x110002E0      @ set GPM4CON Register
       ldr     r1,=0x00001111      @ Configurate GPM4_0<A1>GPM4_1<A2>GPM4_2<A2>GPM4_3 output
       str     r1,[r0]
       ldr     r0,=0x110002E4       @ set GPM4DAT Register
@      mov     r1,#0xFE             @ light All led1 on
@      mov     r1,#0xFD             @ light All led2 on
@      mov     r1,#0xFB             @ light All led3 on
@      mov     r1,#0xF7             @ light All led4 on
       mov r1,#0xF0                     @ light All led on
       str     r1,[r0]
       mov pc, lr

ENTRY(light_led)	/*强烈推荐:汇编和C都能调用的写法*/

       ldr     r0,=0x110002E0      @ set GPM4CON Register
       ldr     r1,=0x00001111      @ Configurate GPM4_0<A1>GPM4_1<A2>GPM4_2<A2>GPM4_3 output
       str     r1,[r0]
       ldr     r0,=0x110002E4       @ set GPM4DAT Register
@      mov     r1,#0xFE             @ light All led1 on
@      mov     r1,#0xFD             @ light All led2 on
@      mov     r1,#0xFB             @ light All led3 on
@      mov     r1,#0xF7             @ light All led4 on
       mov r1,#0xF0                     @ light All led on
       str     r1,[r0]

	bx	lr

ENDPROC(light_led)
