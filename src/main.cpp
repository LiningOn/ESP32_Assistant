#include "includes.h"

void task1(void *parameter)
{
  while (1)
  {
    Serial.println("task1 working...");
    sleep(1);
  }
}

void task2(void *parameter)
{
  while (1)
  {
    time_t now = time(nullptr);
    Serial.print("Current time is: ");
    Serial.println(ctime(&now)); // 打印时间
    // Convert current time to Unix timestamp
    long unixTimestamp = static_cast<long>(now); // 获取unix时间戳
    Serial.print("Unix timestamp is: ");
    Serial.println(unixTimestamp);
    delay(1000);
  }
}

void setup()
{
  Serial.begin(115200);
  init_wifi();

  TaskHandle_t xTaskUartChat;
  TaskHandle_t xTaskSparkApi;
  TaskHandle_t xTask2;
  // xTaskCreate(send_msg_task,   /*任务函数*/
  //             "send_msg_task", /*带任务名称的字符串*/
  //             10000,           /*堆栈大小，单位为字节*/
  //             NULL,            /*作为任务输入传递的参数*/
  //             2,               /*任务的优先级*/
  //             &xTaskUartChat);
  xTaskCreate(send_request_task,    /* Task function. */
              "send_request_task",  /* String with name of task. */
              10000,    /* Stack size in bytes. */
              NULL,     /* Parameter passed as input of the task */
              1,        /* Priority of the task. */
              &xTaskSparkApi); /* Task handle. */
  // xTaskCreate(task2,    /* Task function. */
  //           "task2",  /* String with name of task. */
  //           10000,    /* Stack size in bytes. */
  //           NULL,     /* Parameter passed as input of the task */
  //           1,        /* Priority of the task. */
  //           &xTask2); /* Task handle. */
}

void loop()
{
  // put your main code here, to run repeatedly:
  // printf("loop working...");
}
