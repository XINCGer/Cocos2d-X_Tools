#include "HelloWorldScene.h"
#include "sqlite3.h"
USING_NS_CC;
Scene* HelloWorld::createScene()
{
	auto scene = Scene::create();
	auto layer = HelloWorld::create();
	scene->addChild(layer);
	return scene;
}
bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto* background = LayerColor::create(Color4B(255, 255, 255, 255));
	addChild(background);
	///////////////////////////////////////////////////////////////////

	sqlite3 * db=createDatabase("save");
	std::string sql = "create table student(ID integer primary key autoincrement,name text,sex text)";
	/*createTable(sql, db);*/
	//sql = "insert into student values(1,'student1','male')";
	//insert(sql, db);
	//sql = "insert into student  values(2,'student2','female')";
	//insert(sql, db);
	//sql = "insert into student  values(3,'student3','male')";
	//insert(sql, db);
	sql = "select * from student";
	query(sql, db);
	sql = "update student set name='Jack' where id=3";
	update(sql, db);
	sql = "select * from student";
	query(sql, db);
	sql = "delete from student where id =3";
	del(sql, db);
	sql = "select * from student";
	query(sql, db);
	sqlite3_close(db);
	return true;
}

/**
 * 创建数据库
 */
sqlite3* HelloWorld::createDatabase(const std::string dbName)
{
	sqlite3 *pdb = NULL;
	std::string path = FileUtils::getInstance()->getWritablePath() + dbName + ".db";
	log(path.c_str());;
	std::string sql;
	int result;
	result = sqlite3_open(path.c_str(), &pdb);
	if (result != SQLITE_OK)
	{
		log("Open DataBase Failed!,Error Number:" + result);
		exit(-1);
	}
	return pdb;
}

/*
 * 创建表
 */
void HelloWorld::createTable(const std::string sql, sqlite3 * pdb)
{
	int result = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	if (result != SQLITE_OK)
	{
		log("Create Table Failed!");
		exit(-1);
	}
}


/*
 * 向表中插入数据
 */
void HelloWorld::insert(const std::string sql, sqlite3* pdb)
{
	int result = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	if (result != SQLITE_OK)
	{
		log("Insert Data Failed!");
	}
	else
	{
		log("Insert Data Success!");
	}
}

/*
 * 查询数据
 */
void HelloWorld::query(const std::string sql, sqlite3* pdb)
{
	char **result;
	int row, column;
	sqlite3_get_table(pdb, sql.c_str(), &result, &row, &column, NULL);
	log("row is %d,column is %d", row, column);

	//遍历数据
	for (int i = 1; i <= row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			log("%s", result[i*column + j]);
		}
	}
}

/*
 * 删除数据
 */
void HelloWorld::del(const std::string sql, sqlite3* pdb)
{
	int result = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	if (result != SQLITE_OK)
	{
		log("Delete Data Failed!");
	}
}

/*
 * 更新数据
 */
void HelloWorld::update(const std::string sql, sqlite3* pdb)
{
	int result = sqlite3_exec(pdb, sql.c_str(), NULL, NULL, NULL);
	if (result != SQLITE_OK)
	{
		log("Update Data Failed!");
	}
}







