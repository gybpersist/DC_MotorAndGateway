/*
 * FreeRTOS V202212.01
 * Copyright (C) 2020 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/

// ������ռʽ������
#define configUSE_PREEMPTION 1
// ʹ�ܿ��������Ӻ���, ��Ĭ���趨��
#define configUSE_IDLE_HOOK 0
// ʹ��ϵͳʱ�ӽ����жϹ��Ӻ���, ��Ĭ���趨��
#define configUSE_TICK_HOOK 0
// ����CPU��Ƶ, ��λ: Hz, ��Ĭ���趨��
#define configCPU_CLOCK_HZ ((unsigned long)72000000)
// ����ϵͳʱ�ӽ���Ƶ��, ��λ: Hz, ��Ĭ���趨��
#define configTICK_RATE_HZ ((TickType_t)1000)
// ����������ȼ���, ������ȼ�=configMAX_PRIORITIES-1, ��Ĭ���趨��
#define configMAX_PRIORITIES (32)
// ������������ջ�ռ��С, ��λ: Word, ��Ĭ���趨��
#define configMINIMAL_STACK_SIZE ((unsigned short)128)
// FreeRTOS���п��õ�RAM����, ��λ: Byte, ��Ĭ���趨��
#define configTOTAL_HEAP_SIZE ((size_t)(12 * 1024))
// ��������������ַ���, Ĭ��: 16
#define configMAX_TASK_NAME_LEN (32)
// ʹ�ܿ��ӻ����ٵ���, Ĭ��: 0
#define configUSE_TRACE_FACILITY 0
// ����ϵͳʱ�ӽ��ļ���������������Ϊ16λ�޷�����, ��Ĭ���趨��
#define configUSE_16_BIT_TICKS 0
// ʹ������ռʽ������,ͬ���ȼ�����������ռ��������, Ĭ��: 1
#define configIDLE_SHOULD_YIELD 1

// �����������ȼ�
#define INCLUDE_vTaskPrioritySet 1
// ��ȡ�������ȼ�
#define INCLUDE_uxTaskPriorityGet 1
// ɾ������
#define INCLUDE_vTaskDelete 1
// ��������
#define INCLUDE_vTaskSuspend 1
// ���������ʱ
#define INCLUDE_vTaskDelayUntil 1
// ������ʱ
#define INCLUDE_vTaskDelay 1

/* ���� RTOS �ں�����ʹ�õ��ж����ȼ��� һ������Ϊ������ȼ�, �����������������ȼ�����*/
// ���������������ļ����Ѵ��ڣ��޸�ԭֵ����Ҫ�ظ�����
#define configKERNEL_INTERRUPT_PRIORITY (15 << 4)
/* ������ �����жϰ�ȫ�� FreeRTOS API ����������ж����ȼ��� FreeRTOS �Ĺ����������ȼ� */
// ���������������ļ����Ѵ��ڣ��޸�ԭֵ����Ҫ�ظ�����
#define configMAX_SYSCALL_INTERRUPT_PRIORITY (5 << 4)
/* ͬ��. �������°���ֲ�� �������ǵ�Ч�ġ� */
#define configMAX_API_CALL_INTERRUPT_PRIORITY configMAX_SYSCALL_INTERRUPT_PRIORITY

// RTOS �����ͨ�� RAM ���� FreeRTOS �����Զ����䣩����
// ����Ϊ 0���� RTOS ����ֻ��ͨ��Ӧ�ó����д���ṩ�� RAM ����
// Ĭ��Ϊ 1��
#define configSUPPORT_DYNAMIC_ALLOCATION 1

// ��ӱ����������
#define xPortPendSVHandler PendSV_Handler
#define vPortSVCHandler SVC_Handler
#define INCLUDE_xTaskGetSchedulerState 1

#endif /* FREERTOS_CONFIG_H */
