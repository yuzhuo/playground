1. mysql -uroot -proot -h192.168.3.8 -Dxxx -e "`cat extract.sql`"
2. create database xxx;
3. show databases;
4. show tables;
5. use xxx;
6. check charset: show variables like '%character%';
7. create table search_log( id int not null auto_increment, keyword varchar(200) not null, frequency int, primary key(id)  )charset=utf8;
8. 复制表结构及数据到新表
CREATE TABLE 新表SELECT * FROM 旧表
9. 只复制表结构到新表
CREATE TABLE 新表SELECT * FROM 旧表WHERE 1=2
或CREATE TABLE 新表LIKE 旧表
10. 复制旧表的数据到新表(假设两个表结构不一样)
INSERT INTO 新表(字段1,字段2,.......) SELECT 字段1,字段2,...... FROM 旧表

11. 可以将表1结构复制到表2
SELECT * INTO 表2 FROM 表1 WHERE 1=2
12. 可以将表1内容全部复制到表2
SELECT * INTO 表2 FROM 表1
13. show create table 旧表;
14. mysqldump
15. 导入数据到 mysql（文件中属性 tab 分割）：
load data local infile 'search_log_20170401.1' into table search_log(keyword,frequency);
16. select keywords, frequency into outfile 'test' from search_log;
执行失败 solution：http://www.cnblogs.com/guosihui/p/5344621.html
17. delete from search_log where id=1;
18. insert into tmp2 select a.keyword, b.log_date from tmp1 a left join search_log b on a.keyword = b.keyword;
19. insert into tmp2 select a.keyword, b.log_date from tmp1 a left join search_log b on a.keyword = b.keyword;
20. show index from search_log;

21. truncate search_log;
22. delete from search_log where keword='count';
23. show tables like "test1";
