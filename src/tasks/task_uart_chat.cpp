#include "task_uart_chat.h"

// /**
//  * @brief 读取消息
//  */
// String receive()
// {
//     String data;
//     if (Serial.available())
//     {
//         data = (char)Serial.read();
//         data += receive();
//     }
//     return data;
// }

// /**
//  * @brief 发送消息
//  */
// void send_msg_task(void *parameter)
// {
//     while (1)
//     {
//         String data = receive();
//         if (data != "")
//         {
//             Serial.print("User:" + data);
//         }
//         delay(100);
//     }
// }