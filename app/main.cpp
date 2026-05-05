#include "../sqlite/sqlite3.h"
#include <iostream>
#include <string>

using namespace std;

char* sqlCreateTable = 
"CREATE TABLE IF NOT EXISTS student("\
"id INT PRIMARY KEY,"\
"name VARCHAR(20),"\
"class INT,"\
"number INT,"\
"score REAL)";

char* sqlInsert =
"INSERT INTO student("\
"id, name, class, number, score)"\
"VALUES"\
"(1, 'Li Hua', 1, 1, 100),"\
"(2, 'Li Si', 1, 2, 80),"\
"(3, 'Zhang San', 1, 3, 10),"\
"(4, 'Wang Wu', 1, 4, 90),"\
"(5, 'Xu Liu', 1, 36, 59),"\
"(6, 'Chen Qi', 1, 6, 66)"\
"ON CONFLICT(id) DO NOTHING";


void checkError(sqlite3* db, int errcode, const string& message)
{
    if (errcode != SQLITE_OK)
    {
        cout << message << endl << "error message:" << sqlite3_errmsg(db) << endl << endl;
    }
}

void printTable(sqlite3* db)
{
    char** result = nullptr;
    auto col = 0, row = 0;
    auto errcode = sqlite3_get_table(db, "SELECT * FROM student", &result, &row, &col, nullptr);
    checkError(db, errcode, "Error: sqlite3_get_table");
    for (int i = 0; i <= row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            cout << result[i * col + j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
}


int main() {
    sqlite3* db = nullptr;
    int res = SQLITE_EMPTY;
    //打开数据库
    res = sqlite3_open("student.db", &db);
    checkError(db, res, "Error: database student.db not open");

    //创建表
    res = sqlite3_exec(db, sqlCreateTable, nullptr, nullptr, nullptr);
    checkError(db, res, "Error: data table create not success");

    //插入数据
    res = sqlite3_exec(db, sqlInsert, nullptr, nullptr, nullptr);
    checkError(db, res, "Error: data insert can't success");

    //查找数据
    res = sqlite3_exec(db, "SELECT * FROM student", nullptr, nullptr, nullptr);
    checkError(db, res, "Error: select student data can't success");
    printTable(db);

    //修改数据
    res = sqlite3_exec(db, "UPDATE student SET score=100 WHERE name='Li Hua'", nullptr, nullptr, nullptr);
    checkError(db, res, "Error: update table student can't success");
    printTable(db);

    //

    //删除数据
    //res = sqlite3_exec(db, "DELETE FROM student WHERE score<60", nullptr, nullptr, nullptr);
    //checkError(db, res, "Error: delete student data can't success");
    //printTable(db, "SELECT * FROM student");
    
    //删除表
    //res = sqlite3_exec(db, "DROP student", nullptr, nullptr, nullptr);
    //checkError(db, res, "Error: drop table student can't success");

    //关闭数据库
    sqlite3_close(db);

    return 0;
}
