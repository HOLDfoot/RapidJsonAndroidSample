#include <jni.h>
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>

#include <stdlib.h>

#include "mylog.h"

using namespace rapidjson;

std::string testJsonSet() ;

void testSimpleWriter() ;


void testAddMember() ;

extern "C"
JNIEXPORT jstring

JNICALL
Java_com_example_zhumingren_jsonbuildercplusdemo_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string oauth = "abcd1234";
    std::string method = "GET";
    std::string url = "/v1/users";
    // {"pt":"\/v1\/zhipei\/juquan","mt":"GET","qy":{"t":"6702074d6252b9350c9a70d9ec996dfb-3969988"}}
    //testSimpleWriter();
    testAddMember();

    std::string hello = "Hello from C++";
    LOGD("HELLO");
    return env->NewStringUTF(hello.c_str());
}

void testAddMember() {
    rapidjson::Document document;
    document.SetObject();
    //rapidjson::MemoryPoolAllocator& allocator = document.GetAllocator();

    rapidjson::Value info_objects(rapidjson::kObjectType);

    rapidjson::Value idStr(rapidjson::kStringType);
    idStr.SetString("123", 3);

    const char* url = "success_url";
    document.AddMember(rapidjson::StringRef(url), rapidjson::StringRef(url), document.GetAllocator());

    std::string hello = "info_objects";
    info_objects.AddMember(rapidjson::StringRef(hello.c_str()), rapidjson::StringRef(hello.c_str()), document.GetAllocator());
    info_objects.AddMember(rapidjson::StringRef(hello.c_str()), rapidjson::StringRef(hello.c_str()), document.GetAllocator());

    document.AddMember(rapidjson::StringRef(hello.c_str()), info_objects, document.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);
    //const std::string json = document.GetString();
    LOGD("testAddMember = %s", buffer.GetString());
}

void testSimpleWriter() {
    StringBuffer s;
    Writer<StringBuffer> writer(s);

    writer.StartObject();               // Between StartObject()/EndObject(),
    writer.Key("hello");                // output a key,
    writer.String("world");             // follow by a value.
    writer.Key("t");
    writer.Bool(true);
    writer.Key("f");
    writer.Bool(false);
    writer.Key("n");
    writer.Null();
    writer.Key("i");
    writer.Uint(123);
    writer.Key("pi");
    writer.Double(3.1416);
    writer.Key("a");
    writer.StartArray();                // Between StartArray()/EndArray(),
    for (unsigned i = 0; i < 4; i++)
        writer.Uint(i);                 // all values are elements of the array.
    writer.EndArray();
    writer.Key("jsonObject");
    std::string strTemp = testJsonSet();
    writer.String(strTemp.c_str());

    writer.EndObject();

    // {"hello":"world","t":true,"f":false,"n":null,"i":123,"pi":3.1416,"a":[0,1,2,3]}
    std::cout << s.GetString() << std::endl;
    LOGD("testSimpleWriter = %s", s.GetString());
}

std::string testJsonSet() {
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
    std::string strTemp = std::string(buffer.GetString());
    LOGD("buffer = %s", strTemp.c_str());
    return strTemp;
}

long getTimeStamp() {
    time_t t;
    t = time(NULL);
    return t;
}
