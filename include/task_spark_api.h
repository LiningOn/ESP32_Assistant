#ifndef _TASK_SPARK_API_
#define _TASK_SPARK_API_

#include <includes.h>

/**
 * Spark API 配置参数
*/
#define SPARK_APP_ID "a1206a6c"   
#define SPARK_API_SECRET "MWMxMDYzYjMyZWM5Yzg3N2MyZWE1ZTZi" 
#define SPARK_API_KEY "1981c1f64bb12219ba60c77b9ff2cffd" 
// 用于配置大模型版本，默认“general/generalv2”
#define SPARK_DOMAIN_V1_5 "general"   // v1.5版本
// #define SPARK_DOMAIN_V2 = "generalv2"    // v2.0版本
// 云端环境的服务地址
#define SPARK_URL "ws://spark-api.xf-yun.com/v1.1/chat"  // v1.5环境的地址
// #define SPARK_URL_V2 "ws://spark-api.xf-yun.com/v2.1/chat"  // v2.0环境的地址
#define SPARK_HOST "spark-api.xf-yun.com"  // v1.5环境的地址
#define SPARK_PATH "/v1.1/chat"  // v1.5环境的地址


void send_request_task(void *parameter);
String receive(void);


#endif