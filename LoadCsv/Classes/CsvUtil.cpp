#include "CsvUtil.h"
#include "StringUtil.h"

CsvUtil* CsvUtil::m_CsvUtil = NULL;

CsvUtil* CsvUtil::getInstance(){
    if(m_CsvUtil == NULL) {
        m_CsvUtil = new CsvUtil();
        if(m_CsvUtil && m_CsvUtil->init()) {
            m_CsvUtil->autorelease();
            m_CsvUtil->retain();
        }
        else {
            CC_SAFE_DELETE(m_CsvUtil);
            m_CsvUtil = NULL;
        }
    }

    return m_CsvUtil;
}

bool CsvUtil::init(){
    return true;
}

void CsvUtil::loadFile( const char* sPath ){

    /* 存放一个csv文件的对象。 */
    CsvData* csvData = CsvData::create();

    /* 读取数据，按行保存到列表中 */
    std::string str = FileUtils::getInstance()->getStringFromFile(sPath);
    ValueVector linesList = StringUtil::getInstance()->split(str.c_str(), "\n");

    /* 把每一行的字符串拆分出来（按逗号分隔） */
    for(auto value : linesList) {
        /* 
            将一行的字符串按逗号分隔，然后存放到列表中，最后将列表存放到CsvData对象里。
            换句话说，csvData将成为一个二维表格，记录了配置文件行和列的字符串
        */
        ValueVector tArr = StringUtil::getInstance()->split(value.asString().c_str(), ",");
        csvData->addLineData(tArr);
    }

    /* 添加列表到字典里 */
    mCsvMap.insert(sPath, csvData);
}

Value CsvUtil::getValue( int iRow, int iCol, const char* csvFilePath ) {
    /* 取出Csv文件对象 */
    auto csvData = mCsvMap.at(csvFilePath);

    /* 如果配置文件的数据不存在，则加载配置文件 */
    if(csvData == nullptr) {
        loadFile(csvFilePath);
        csvData = mCsvMap.at(csvFilePath);
    }
    Size size = csvData->getRowColNum();

    /* 数据行数 */
    int iRowNum = size.width;
    int iColNum = size.height;

    /* 下标越界 */
    if(iRow >= iRowNum || iCol >= iColNum) {
        return Value("");
    }

    /* 获取第iRow行数据 */
    ValueVector rowVector = csvData->getSingleLineData(iRow);

    /* 获取第iCol列数据 */
    Value colValue = rowVector.at(iCol);

    return colValue;
}

const std::string CsvUtil::get(int iRow, int iCol, const char* csvFilePath) {
    Value colValue = getValue(iRow, iCol, csvFilePath);

    return colValue.asString();
}

const Size CsvUtil::getFileRowColNum( const char* csvFilePath )
{
    /* 取出配置文件的二维表格 */
    auto csvData = mCsvMap.at(csvFilePath);

    /* 如果配置文件的数据不存在，则加载配置文件 */
    if(csvData == nullptr) {
        loadFile(csvFilePath);
        csvData = mCsvMap.at(csvFilePath);
    }
    Size size = csvData->getRowColNum();
    return size;
}

const int CsvUtil::getInt( int iRow, int iCol, const char* csvFilePath ) {
    Value colValue = getValue(iRow, iCol, csvFilePath);
	return colValue.asInt();
}

const float CsvUtil::getFloat(int iRow, int iCol, const char* csvFilePath) {
    Value colValue = getValue(iRow, iCol, csvFilePath);

    return colValue.asFloat();
}

const bool CsvUtil::getBool(int iRow, int iCol, const char* csvFilePath)
{
    Value colValue = getValue(iRow, iCol, csvFilePath);
    return colValue.asBool();
}

const int CsvUtil::findValueInWithLine( const char* chValue, int iValueCol, const char* csvFilePath ) {
    Size csvSize = getFileRowColNum(csvFilePath);

    int iLine = -1;
    for(int i = 2; i < csvSize.width; i++) {
        int ID = getInt(i, iValueCol, csvFilePath);
        if(Value(ID).asString().compare(chValue) == 0) {
            iLine = i;
            break;
        }
    }

    return iLine;
}
