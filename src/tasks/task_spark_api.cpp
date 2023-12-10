#include "task_spark_api.h"

class Ws_Param
{
private:
    String appId;
    String apiKey;
    String apiSecret;
    String host;
    String path;
    String sparkUrl;

public:
    Ws_Param() {}
    Ws_Param(String appId, String apiKey, String apiSecret, String host, String path, String sparkUrl)
    {
        this->appId = appId;
        this->apiKey = apiKey;
        this->apiSecret = apiSecret;
        this->host = host;
        this->path = path;
        this->sparkUrl = sparkUrl;
    }

    String create_url()
    {

        time_t now = time(nullptr);
        struct tm tm_time = {};
        // 将字符串时间转换为tm结构体
        strptime(ctime(&now), "%a %b %d %H:%M:%S %Y", &tm_time);

        // 转换为time_t类型
        time_t t_time = mktime(&tm_time);
        struct tm *gmt_time = gmtime(&t_time);

        // 不加ctime，时间会有偏差
        ctime(&t_time);

        // 格式化成RFC1123格式的时间戳
        char http_date[30];
        strftime(http_date, 30, "%a, %d %b %Y %H:%M:%S GMT", gmt_time);

        return http_date;
    }
};

/**
 * @brief 读取消息
 */
String receive()
{
    String data;
    if (Serial.available())
    {
        data = (char)Serial.read();
        data += receive();
    }
    return data;
}


/**
 * @brief 发送问题请求到spark api
 */
void send_request_task(void *parameter)
{
    while (1)
    {
        String question = receive();
        if (question != "")
        {
            Serial.print("User:" + question);
            // TODO 发送请求到后台
            // 1.生成url
            Ws_Param *wsParam = new Ws_Param(SPARK_APP_ID, 
                                            SPARK_API_KEY, 
                                            SPARK_API_SECRET, 
                                            SPARK_HOST,
                                            SPARK_PATH,
                                            SPARK_URL);
            String url = wsParam->create_url();
            Serial.print("Url is: " + url);
            // 2.
        }
        delay(1000);
    }
}