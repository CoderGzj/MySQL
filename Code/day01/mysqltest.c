#include<mysql/mysql.h>
#include<stdio.h>

int main(){
    MYSQL * conn = NULL;
    char * host = "localhost";
    char * user = "root";
    char * passwd = "123456";
    char * db = "43th";

    // 1.初始化mysql的链接句柄
    conn = mysql_init(NULL);

    // 2.建立连接(TCP的连接，完成三次握手的过程，信息的校验)
    if(mysql_real_connect(conn,host,user,passwd,db,3306,NULL,0) == NULL) {
        printf("error:%s\n",mysql_error(conn));
        return EXIT_FAILURE;
    }
    
    // 3.执行查询
    char * query = "select * from person";
    int ret = mysql_query(conn,query);
    if(ret != 0){
        printf("error query1:%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    // 4.获取结果集,N行数据
    // mysql_use_result 不会直接保存查询结果
    // MYSQL_RES * result = mysql_use_result(conn);
    // mysql_store_result 会直接把所有结果存储下来
    MYSQL_RES * result = mysql_store_result(conn);
    if(result == NULL){
        printf("error query2:%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    int rows = mysql_num_rows(result);
    int cols = mysql_num_fields(result);
    printf("rows:%d, cols:%d\n",rows, cols);

    // 5.获取每一行数据
    MYSQL_ROW row;
    while((row = mysql_fetch_row(result)) != NULL){
        for(int i = 0; i < cols; ++i){
            printf("%10s",row[i]);
        }
        printf("\n");
    }

    // 6.释放结果集和关闭连接
    mysql_free_result(result);
    mysql_close(conn);

    return 0;
}