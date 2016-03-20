/*
    文件名：    CsvUtil.h
    描　述：    Csv文件读取工具
    创建人：    笨木头 (博客：http://www.benmutou.com)

    创建日期：   2013.11.04
*/
#ifndef CsvUtil_H
#define CsvUtil_H

#include "cocos2d.h"
#include "CsvData.h"

using namespace cocos2d;

class CsvUtil : public Ref {
public:
    /* 获取工具对象 */
    static CsvUtil* getInstance();

    virtual bool init();

    /* 加载配置文件 */
    void loadFile(const char* sPath);

    /* 获取某行某列的值 */
    Value getValue(int iRow, int iCol, const char* csvFilePath);

	/* 获取某行某列的值，并转化为字符串 */
	const std::string get(int iRow, int iCol, const char* csvFilePath);

	/* 获取某行某列的值，并且转换为整型 */
	const int getInt(int iRow, int iCol, const char* csvFilePath);

    /* 获取某行某列的值，并且转换为浮点型 */
    const float getFloat(int iRow, int iCol, const char* csvFilePath);

    /* 获取某行某列的值，并且转换为布尔型 */
    const bool getBool(int iRow, int iCol, const char* csvFilePath);

	/* 获取配置文件数据的行和列数量 */
	const Size getFileRowColNum(const char* csvFilePath);

	/* 根据某个列的值，查找该值所在的行 */
	const int findValueInWithLine(const char* chValue, int iValueCol, const char* csvFilePath);
private:
    static CsvUtil* m_CsvUtil;

    /* 存放mCsvStrList-filePath的字典 */
    Map<std::string, CsvData*> mCsvMap;
};

#endif