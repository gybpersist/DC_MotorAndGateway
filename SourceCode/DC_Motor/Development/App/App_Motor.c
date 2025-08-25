#include "App_Motor.h"

void App_Motor_Init(void)
{
    // ��ʼ�� Motor ���
    Int_Motor_Init();

    // ��ʼ�� TIM4 ������
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
}

int8_t App_Motor_GetDir(void)
{
    // ��ȡ Motor ������з��� -1:������ 1:������
    if (__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim4))
    {
        REG_DISC_BUF[2] = 0; //д����ɢ��������
        return -1;
    }
    else
    {
        REG_DISC_BUF[2] = 1; //д����ɢ��������
        return 1;
    }
}

void App_Motor_GetSpeed(float dt)
{
    // ���徲̬����
    static uint16_t last_count = 0;    // ��һ�μ���
    static uint16_t current_count = 0; // ��ǰ����
    static float last_speed = 0;

    // ��ȡ��ǰ����
    current_count = __HAL_TIM_GetCounter(&htim4);
    // DEBUG_PRINTLN("current_count: %d", current_count);

    // ���� count �仯��
    int16_t count_diff = (int16_t)current_count - (int16_t)last_count;
    // ������һ�μ���
    last_count = current_count;
    // ���� ��� mesure_speed
    // mesure_speed  =  count�仯�� / ʱ���� / ��Ƶ�� / �������ֱ��� / ���ٱ� * 60
    float mesure_speed = count_diff / dt / 4 / 11 / 21.428 * 60;
    // ��ӡ������Ϣ
    // DEBUG_PRINTF("mesure_speed: %.2lf, count_diff: %d\n", mesure_speed, count_diff);

    // һ�׵�ͨ�˲�
    mesure_speed = 0.8 * last_speed + 0.2 * mesure_speed;
    // ������һ���ٶ�
    last_speed = mesure_speed;
    // ��ӡ������Ϣ
    // DEBUG_PRINTF("last_speed: %.2lf\n", last_speed);

    // ��ֵ��ȫ�ֱ���
    g_mesure_speed = last_speed;

    // �ѵ�ǰ�����ʵ��ת�ٽ��� modbus ������Ĵ���
    REG_INPUT_BUF[2] = g_mesure_speed + 500;
}

// ����������־ 0��δ���� 1�������� (��ֹ�ظ�����,�ر�)
static uint8_t is_start = 0;
// ��� PID ����
PID_Info motor_pid = {.Kd = 0.09f, .Ki = 2.2f, .Kp = 0.1f};

void App_Motor_Run(float dt)
{
    if (g_desired_speed == 0)
    {
        if (is_start == 1)
        {
            // �ر� Motor ���
            Int_Motor_Stop();
            is_start = 0;
            // ���������
            motor_pid.integral = 0;
            // �����һ�����
            motor_pid.last_error = 0;
            return;
        }
    }
    if (g_desired_speed != 0)
    {
        if (is_start == 0)
        {
            // ���� Motor ���
            Int_Motor_Start();
            is_start = 1;
        }
    }

    //  PID �㷨---------------------------------------------------------------//
    // ʹ�� PID �㷨��������ٶȵ����
    // 1 ���� �������ֵ
    motor_pid.desired = g_desired_speed;
    // 2 ���� �������ֵ
    App_Motor_GetSpeed(dt);
    motor_pid.measure = g_mesure_speed;
    // 3 ���� ��� dt
    motor_pid.dt = dt;
    // 5 ���� PID ���
    Com_Util_PID(&motor_pid);
    // 6 ��ȡ ���������
    float motor_result = motor_pid.result;
    // 7 ���� ��������� ��Χ -490 ~ 490
    motor_result = LIMIT(motor_result, -490, 490);
    // ��ӡ������Ϣ
    // DEBUG_PRINTF("motor_result: %.2lf\n", motor_result);
    //  PID �㷨---------------------------------------------------------------//

    // ���� Motor ����ٶ�
    Int_Motor_SetSpeed(motor_result);
}

void App_Motor_CheckModbus(void)
{
    // �жϵ������ͣ����
    if ((REG_COILS_BUF[2] == 1) && (is_start == 0))
    {
        // �������
        Int_Motor_Start();
        DEBUG_PRINTLN("\nmodbus �������...");
        
        // ����һ����ʼ�ٶ�
        // g_desired_speed = 50;

        is_start = 1;
    }
    else if ((REG_COILS_BUF[2] == 0) && (is_start == 1))
    {
        // �رյ��
        Int_Motor_Stop();
        DEBUG_PRINTLN("\nmodbus �رյ��...");
        is_start = 0;
    }

    // �жϵ�����ٶȿ��� REG_HOLD_BUF[2]
    if (REG_HOLD_BUF[2] != 0)
    {
        // �ٶȿ���
        g_desired_speed = REG_HOLD_BUF[2] - 500;
    }
}
