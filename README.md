# DC_MotorAndGateway

# 直流减速电机和网关

主控芯片:

STM32F103C8T6

电机:

GA25-370减速电机(12V280RPM)

按键:

KEY1:增加期望转速/modbusid,

KEY2:减少期望转速/modbusid,

KEY3:清空转速/modbusID,

KEY4:模式切换(调节转速/modbusID)

OLED:

显示1:项目名称

显示2:期望转速

显示3:测量转速

显示4:modbusID

Modbus:

modbus-RTU:连接电机和网关通信

网关:

W5500网关+MQTT协议+TCP 连接服务器



