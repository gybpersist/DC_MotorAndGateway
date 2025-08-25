#include "App_Motor.h"

void App_Motor_Init(void)
{
    // 初始化 Motor 电机
    Int_Motor_Init();

    // 初始化 TIM4 编码器
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
}

int8_t App_Motor_GetDir(void)
{
    // 获取 Motor 电机运行方向 -1:反方向 1:正方向
    if (__HAL_TIM_IS_TIM_COUNTING_DOWN(&htim4))
    {
        REG_DISC_BUF[2] = 0; //写到离散量缓冲区
        return -1;
    }
    else
    {
        REG_DISC_BUF[2] = 1; //写到离散量缓冲区
        return 1;
    }
}

void App_Motor_GetSpeed(float dt)
{
    // 定义静态变量
    static uint16_t last_count = 0;    // 上一次计数
    static uint16_t current_count = 0; // 当前计数
    static float last_speed = 0;

    // 获取当前计数
    current_count = __HAL_TIM_GetCounter(&htim4);
    // DEBUG_PRINTLN("current_count: %d", current_count);

    // 计算 count 变化量
    int16_t count_diff = (int16_t)current_count - (int16_t)last_count;
    // 更新上一次计数
    last_count = current_count;
    // 计算 电机 mesure_speed
    // mesure_speed  =  count变化量 / 时间间隔 / 分频数 / 编码器分辨率 / 减速比 * 60
    float mesure_speed = count_diff / dt / 4 / 11 / 21.428 * 60;
    // 打印调试信息
    // DEBUG_PRINTF("mesure_speed: %.2lf, count_diff: %d\n", mesure_speed, count_diff);

    // 一阶低通滤波
    mesure_speed = 0.8 * last_speed + 0.2 * mesure_speed;
    // 更新上一次速度
    last_speed = mesure_speed;
    // 打印调试信息
    // DEBUG_PRINTF("last_speed: %.2lf\n", last_speed);

    // 赋值到全局变量
    g_mesure_speed = last_speed;

    // 把当前电机的实际转速交给 modbus 的输入寄存器
    REG_INPUT_BUF[2] = g_mesure_speed + 500;
}

// 定义启动标志 0：未启动 1：已启动 (防止重复启动,关闭)
static uint8_t is_start = 0;
// 电机 PID 参数
PID_Info motor_pid = {.Kd = 0.09f, .Ki = 2.2f, .Kp = 0.1f};

void App_Motor_Run(float dt)
{
    if (g_desired_speed == 0)
    {
        if (is_start == 1)
        {
            // 关闭 Motor 电机
            Int_Motor_Stop();
            is_start = 0;
            // 清除积分项
            motor_pid.integral = 0;
            // 清除上一次误差
            motor_pid.last_error = 0;
            return;
        }
    }
    if (g_desired_speed != 0)
    {
        if (is_start == 0)
        {
            // 启动 Motor 电机
            Int_Motor_Start();
            is_start = 1;
        }
    }

    //  PID 算法---------------------------------------------------------------//
    // 使用 PID 算法消除电机速度的误差
    // 1 保存 电机期望值
    motor_pid.desired = g_desired_speed;
    // 2 保存 电机测量值
    App_Motor_GetSpeed(dt);
    motor_pid.measure = g_mesure_speed;
    // 3 保存 电机 dt
    motor_pid.dt = dt;
    // 5 计算 PID 输出
    Com_Util_PID(&motor_pid);
    // 6 获取 电机输出结果
    float motor_result = motor_pid.result;
    // 7 限制 电机输出结果 范围 -490 ~ 490
    motor_result = LIMIT(motor_result, -490, 490);
    // 打印调试信息
    // DEBUG_PRINTF("motor_result: %.2lf\n", motor_result);
    //  PID 算法---------------------------------------------------------------//

    // 设置 Motor 电机速度
    Int_Motor_SetSpeed(motor_result);
}

void App_Motor_CheckModbus(void)
{
    // 判断电机的启停控制
    if ((REG_COILS_BUF[2] == 1) && (is_start == 0))
    {
        // 启动电机
        Int_Motor_Start();
        DEBUG_PRINTLN("\nmodbus 启动电机...");
        
        // 设置一个初始速度
        // g_desired_speed = 50;

        is_start = 1;
    }
    else if ((REG_COILS_BUF[2] == 0) && (is_start == 1))
    {
        // 关闭电机
        Int_Motor_Stop();
        DEBUG_PRINTLN("\nmodbus 关闭电机...");
        is_start = 0;
    }

    // 判断电机的速度控制 REG_HOLD_BUF[2]
    if (REG_HOLD_BUF[2] != 0)
    {
        // 速度控制
        g_desired_speed = REG_HOLD_BUF[2] - 500;
    }
}
