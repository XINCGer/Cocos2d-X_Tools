#Json解析模块

##说明  
借助了JsonCpp库。  
Json::Reader 用于解析Json的类  
Json::Value  这个类代表了Json的一段数据
调用FileUtils的getStringFromFile("test1.json")，FileUtils用来加载文件，返回字符串  
调用Reader的parse函数开始解析Json文件，解析的结果会保存到root对象中(json::Value)  
