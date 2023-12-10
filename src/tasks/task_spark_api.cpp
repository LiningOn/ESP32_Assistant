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

    String urlencode(char *authorization, char *date, String host) {
        // TODO 进行生成url带参数
        
        return "";
    }

    String create_url()
    {
        // 生成RFC1123格式的时间戳
        time_t now = time(nullptr);
        struct tm tm_time = {};
        // 将字符串时间转换为tm结构体
        strptime(ctime(&now), "%a %b %d %H:%M:%S %Y", &tm_time);

        // 转换为time_t类型
        time_t t_time = mktime(&tm_time);
        struct tm *gmt_time = gmtime(&t_time);

        // 不加ctime，时间会有偏差
        ctime(&t_time);
        char date[30];
        strftime(date, 30, "%a, %d %b %Y %H:%M:%S GMT", gmt_time);

        // 拼接字符串
        String signature_origin = "host: " + this->host + "\n";
        signature_origin += "GET " + this->path + " HTTP/1.1";

        // 1.进行hmac-sha256进行加密
        size_t signature_len = signature_origin.length();
        unsigned char signature_sha[MBEDTLS_MD_MAX_SIZE];

        const char *secret = this->apiSecret.c_str();
        const char *signature = signature_origin.c_str();
        compute_hmac_sha256(secret, signature, signature_len, signature_sha);

        // Serial.println("\n--------Print the binary digest------");
        // // Print the binary digest
        // for (int i = 0; i < MBEDTLS_MD_MAX_SIZE; i++)
        // {
        //     // 使用两个参数的形式打印十六进制数字
        //     Serial.print(signature_sha[i], HEX);
        //     if (signature_sha[i] <= 0x0F)
        //     {
        //         Serial.print("0"); // 如果数组元素值小于等于0x0F，则在打印后添加一个0
        //     }
        // }
        // Serial.println("\n--------Print the binary digest end ------\n");

        // 2.获取 signature_sha_base64
        size_t signatureSize = MBEDTLS_MD_MAX_SIZE;
        String signature_sha_base64 = base64::encode(signature_sha, MBEDTLS_MD_MAX_SIZE);

        // 3.获取authorization_origin
        String authorization_origin = "api_key=" + this->apiKey +
                                      ", algorithm=\"hmac-sha256\", headers=\"host date request-line\", signature=\"" +
                                      signature_sha_base64 + "\"";

        // 4.获取authorization
        const unsigned char *authorization_origin_tmp = (const unsigned char *)malloc(authorization_origin.length() + 1); // 为`buffer`分配足够的内存空间
        strcpy((char *)authorization_origin_tmp, authorization_origin.c_str());                                           // 调用`strcpy`函数，将`String`对象复制到`buffer`缓冲区中
        // 计算编码后的长度
        size_t encoded_size;
        mbedtls_base64_encode(NULL, 0, &encoded_size, authorization_origin_tmp, authorization_origin.length());
        // 创建编码后的字符串缓冲区
        char *authorization = (char *)malloc(encoded_size + 1);
        // 执行编码操作
        mbedtls_base64_encode((unsigned char *)authorization, encoded_size, &encoded_size, authorization_origin_tmp, authorization_origin.length());
        // 添加字符串结束符
        authorization[encoded_size] = '\0';
        // 打印编码后的字符串
        printf("encoded: %s\n", authorization);

        // 5.拼接鉴权参数，生成url
        String url = this->sparkUrl + "?" + this->urlencode(authorization, date, this->host);
        // 释放缓冲区
        free(authorization);

        return url;
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
            Serial.println("\nUser:" + question);
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