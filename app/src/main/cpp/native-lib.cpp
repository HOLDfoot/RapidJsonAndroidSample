#include <jni.h>
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>

#include "mylog.h"

using namespace rapidjson;


extern "C"
JNIEXPORT jstring

JNICALL
Java_com_example_zhumingren_jsonbuildercplusdemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string oauth = "abcd1234";
    std::string method = "GET";
    std::string url = "/v1/users";

    // 1. 把 JSON 解析至 DOM。
    const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
    Document d;
    d.Parse(json);
    // 2. 利用 DOM 作出修改。
    Value& s = d["stars"];
    s.SetInt(s.GetInt() + 1);
    // 3. 把 DOM 转换（stringify）成 JSON。
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
    // Output {"project":"rapidjson","stars":11}
    std::cout << buffer.GetString() << std::endl;
    LOGD("buffer = %s", buffer.GetString());

    std::string hello = "Hello from C++";
    LOGD("HELLO");
    return env->NewStringUTF(hello.c_str());
}

