> # 《MySQL必知必会》

## 准备工作

配套网站：<https://forta.com/books/0672327120/>

可下载相应的配套数据文件`mysql_scripts.zip`，包含`create.sql`和`populate.sql`两个文件。

首先安装MySQL，参考官方文档：https://dev.mysql.com/doc/mysql-apt-repo-quick-guide/en/

```bash
$ sudo apt-get install mysql-client
$ sudo apt-get install mysql-server
```

```bash
$ sudo vim /etc/mysql/mysql.conf.d/mysqld.cnf
# 注释掉bind-address = 127.0.0.1
$ sudo service mysql start
$ sudo mysql
```

```mysql
> CREATE DATABASE crash;
Query OK, 1 row affected (0.00 sec)
> USE crash;
Database changed
> source /mnt/f/Project/Reading-Notes/Database/MySQL-Crash-Course/create.sql;
> source /mnt/f/Project/Reading-Notes/Database/MySQL-Crash-Course/populate.sql;
> SHOW tables;
+-----------------+      
| Tables_in_crash |      
+-----------------+      
| customers       |      
| orderitems      |      
| orders          |      
| productnotes    |      
| products        |      
| vendors         |      
+-----------------+      
6 rows in set (0.00 sec) 
```

如果上述操作一切正常，就完成了准备工作。

了解一下各个表地字段：

```mysql
> SHOW COLUMNS FROM products;
+------------+--------------+------+-----+---------+-------+
| Field      | Type         | Null | Key | Default | Extra |
+------------+--------------+------+-----+---------+-------+
| prod_id    | char(10)     | NO   | PRI | NULL    |       |
| vend_id    | int(11)      | NO   | MUL | NULL    |       |
| prod_name  | char(255)    | NO   |     | NULL    |       |
| prod_price | decimal(8,2) | NO   |     | NULL    |       |
| prod_desc  | text         | YES  |     | NULL    |       |
+------------+--------------+------+-----+---------+-------+
```

```mysql
mysql> show columns from customers;
+--------------+-----------+------+-----+---------+----------------+
| Field        | Type      | Null | Key | Default | Extra          |
+--------------+-----------+------+-----+---------+----------------+
| cust_id      | int(11)   | NO   | PRI | NULL    | auto_increment |
| cust_name    | char(50)  | NO   |     | NULL    |                |
| cust_address | char(50)  | YES  |     | NULL    |                |
| cust_city    | char(50)  | YES  |     | NULL    |                |
| cust_state   | char(5)   | YES  |     | NULL    |                |
| cust_zip     | char(10)  | YES  |     | NULL    |                |
| cust_country | char(50)  | YES  |     | NULL    |                |
| cust_contact | char(50)  | YES  |     | NULL    |                |
| cust_email   | char(255) | YES  |     | NULL    |                |
+--------------+-----------+------+-----+---------+----------------+
```

```mysql
mysql> show columns from orderitems;
+------------+--------------+------+-----+---------+-------+
| Field      | Type         | Null | Key | Default | Extra |
+------------+--------------+------+-----+---------+-------+
| order_num  | int(11)      | NO   | PRI | NULL    |       |
| order_item | int(11)      | NO   | PRI | NULL    |       |
| prod_id    | char(10)     | NO   | MUL | NULL    |       |
| quantity   | int(11)      | NO   |     | NULL    |       |
| item_price | decimal(8,2) | NO   |     | NULL    |       |
+------------+--------------+------+-----+---------+-------+
```

```mysql
mysql> show columns from orders;
+------------+----------+------+-----+---------+----------------+
| Field      | Type     | Null | Key | Default | Extra          |
+------------+----------+------+-----+---------+----------------+
| order_num  | int(11)  | NO   | PRI | NULL    | auto_increment |
| order_date | datetime | NO   |     | NULL    |                |
| cust_id    | int(11)  | NO   | MUL | NULL    |                |
+------------+----------+------+-----+---------+----------------+
```

```mysql
mysql> show columns from productnotes;
+-----------+----------+------+-----+---------+----------------+
| Field     | Type     | Null | Key | Default | Extra          |
+-----------+----------+------+-----+---------+----------------+
| note_id   | int(11)  | NO   | PRI | NULL    | auto_increment |
| prod_id   | char(10) | NO   |     | NULL    |                |
| note_date | datetime | NO   |     | NULL    |                |
| note_text | text     | YES  | MUL | NULL    |                |
+-----------+----------+------+-----+---------+----------------+
```

```mysql
mysql> show columns from vendors;                                    
+--------------+----------+------+-----+---------+----------------+  
| Field        | Type     | Null | Key | Default | Extra          |  
+--------------+----------+------+-----+---------+----------------+  
| vend_id      | int(11)  | NO   | PRI | NULL    | auto_increment |  
| vend_name    | char(50) | NO   |     | NULL    |                |  
| vend_address | char(50) | YES  |     | NULL    |                |  
| vend_city    | char(50) | YES  |     | NULL    |                |  
| vend_state   | char(5)  | YES  |     | NULL    |                |  
| vend_zip     | char(10) | YES  |     | NULL    |                |  
| vend_country | char(50) | YES  |     | NULL    |                |  
+--------------+----------+------+-----+---------+----------------+  
```

卸载MySQL：

```bash
$ sudo apt-get remove mysql-*
$ dpkg -l |grep ^rc|awk '{print $2}' |sudo xargs dpkg -P
```



## 第一章 了解MySQL

### 1.1 数据库基础

#### 1.1.1 什么是数据库

**数据库（database）**：保存有组织的数据的容器（通常是一个文件或一组文件）。

注意：数据库软件应该被称为DBMS（数据库管理系统），数据库是通过DBMS创建和操作的容器。

#### 1.1.2 表

**表（table）**：某种特定类型数据的结构化清单。

数据库中每个表都有一个名字，并且是唯一的。

在相同数据库中表名是唯一的，但是在不同数据库中，表的名字可以相同。

**模式（schema）**：关于数据库和表的布局及特性的信息。

表有一些特性，这些特性定义了数据在表中如何存储，可以存储什么样的数据，数据如何分解，各部分信息如何命名等等。描述表的这组信息就是所谓的模式。

#### 1.1.3 列和数据类型

表由列组成，列存储着表中某部分的信息。

**列（column）**：表中的一个字段。所有表都是由一个或多个列组成的。

**数据类型（datatype）**：所容许的数据的类型。每个表列都有相应的数据类型，它限制（或允许）该列中存储的数据。

#### 1.1.4 行

**行（row）**：表中的一个记录。

#### 1.1.5 主键

**主键（primary key）**：一列（或一组列），其值能够唯一区分表中每个行。

表中的任何列都可以作为主键，只要满足：

* 任意两行都具有不同的值；
* 每个行都必须具有主键值（即不允许为NULL值）。

主键的最好习惯：

* 不更新主键列中的值；
* 不重用主键列的值；
* 不在主键列中使用可能会更改的值（如使用供应商名字为主键，如果供应商合并，则需要更改这个主键）。

### 1.2 什么是MySQL

SQL是一种专门用来与数据库通信的语言。



## 第三章 使用MySQL

### 3.1 连接

为了连接到MySQL，需要以下信息：

* 主机名（计算机名）——如果连接到本地MySQL服务器，为`localhost`。
* 端口（默认端口是3306）.
* 一个合法的用户名。
* 用户口令。

### 3.2 选择数据库

**关键字（key word）**：作为MySQL语言组成部分的一个保留字，不能用关键字命名一个表或列。

输入：`USE [database name];`.

输出：`Database changed`

```mysql
USE crash;
```

```
Database changed
```



### 3.3 了解数据库和表

如果不知道数据库名，那么可以通过以下命令显示数据库列表：

输入：`SHOW DATABASES;`。

```mysql
SHOW DATABASES;
```

```
+--------------------+
| Database           |
+--------------------+
| information_schema |
| crash              |
| mysql              |
| performance_schema |
| sys                |
+--------------------+
```

获取一个数据库内的所有表的列表：

输入：`SHOW TABLES;`

```mysql
SHOW TABLES;
```

```
+-----------------+ 
| Tables_in_crash | 
+-----------------+ 
| customers       | 
| orderitems      | 
| orders          | 
| productnotes    | 
| products        | 
| vendors         | 
+-----------------+ 
```

显示一个表内的某一列：

输入：`SHOW COLUMNS FROM [table name];`

**自动增量**：某些表列需要唯一值，如订单编号。在每个行添加到表中，MySQL可以自动的为每个行分配下一个可用编号，不用手动分配唯一值，这个功能就是自动增量。

`DESCRIBE [table name];`和`SHOW COLUMNS FROM [table name];`效果是一样的。

```mysql
SHOW COLUMNS FROM customers;
```

```
+--------------+-----------+------+-----+---------+----------------+
| Field        | Type      | Null | Key | Default | Extra          |
+--------------+-----------+------+-----+---------+----------------+
| cust_id      | int(11)   | NO   | PRI | NULL    | auto_increment |
| cust_name    | char(50)  | NO   |     | NULL    |                |
| cust_address | char(50)  | YES  |     | NULL    |                |
| cust_city    | char(50)  | YES  |     | NULL    |                |
| cust_state   | char(5)   | YES  |     | NULL    |                |
| cust_zip     | char(10)  | YES  |     | NULL    |                |
| cust_country | char(50)  | YES  |     | NULL    |                |
| cust_contact | char(50)  | YES  |     | NULL    |                |
| cust_email   | char(255) | YES  |     | NULL    |                |
+--------------+-----------+------+-----+---------+----------------+
```

```mysql
DESCRIBE customers;
```

```
+--------------+-----------+------+-----+---------+----------------+
| Field        | Type      | Null | Key | Default | Extra          |
+--------------+-----------+------+-----+---------+----------------+
| cust_id      | int(11)   | NO   | PRI | NULL    | auto_increment |
| cust_name    | char(50)  | NO   |     | NULL    |                |
| cust_address | char(50)  | YES  |     | NULL    |                |
| cust_city    | char(50)  | YES  |     | NULL    |                |
| cust_state   | char(5)   | YES  |     | NULL    |                |
| cust_zip     | char(10)  | YES  |     | NULL    |                |
| cust_country | char(50)  | YES  |     | NULL    |                |
| cust_contact | char(50)  | YES  |     | NULL    |                |
| cust_email   | char(255) | YES  |     | NULL    |                |
+--------------+-----------+------+-----+---------+----------------+
```



## 第四章 检索数据

### 4.2 检索单个列

检索表中一列的数据：

输入：`SELECT [column name] FROM [table name];`

结束SQL语句：多条SQL语句必须以分号分割。

SQL语句不区分大小写，许多开发人员喜欢对关键字使用大写，所有列和表名使用小写，这样代码更易于阅读。

SQL语句被处理时忽略空格。

### 4.3 检索多个列

当选择多个列时，一定要在列名之间加上逗号。

输入： `SELECT [column name 1], [column name 2] FROM [table name];`

数据表示：SQL语句一般返回原始的、无格式的数据。

### 4.4 检索所有列

如果给定一个通配符，则返回表中的所有列。

输入：`SELECT * FROM [table name];`

使用通配符可能会比价省事，但是检索不需要的数据会降低检索和应用程序的性能。

### 4.5 检索不同的行

比如要检索在表`product`里的所有供应商的`ID`，如果输入：`SELECT id FROM product;`，则返回所有`id`，虽然实际上可能只有几个供应商，那么我们应该使用关键字`DISTINCT`。

输入：`SELECT DISTINCT id FROM product;`。

关键字`DISTINCT`必须放在列名的前面，而且应用于所有列而不是前置列，比如`SELECT DISTINCT id, prices FROM product;`。

### 4.6 限制结果

`SELECT`语句返回所有匹配的行，为了返回第一行或者前几行，可以使用`LIMIT`关键字：

输入：`SELECT [column name] FROM [table name] LIMIT 5;`

上述语句只会输出匹配到的前5行。

为了从某一个特定的位置开始检索，可以使用：

输入：`SELECT [column name] FROM [table name] LIMIT 5, 5;`

其中关键字`LIMIT`后的第一个数字表示开始位置，第二个数字表示检索的行数。

**行0**：检索出来的第一行为0而不是1，所以`LIMIT 1, 1;`检索出来的是第二行。

行数不够时：如果第二个数加上第一个数超过了行数，那么只返回存在的行。

MySQL5支持`LIMIT 4 OFFSET 3;`和`LIMIT 3, 4;`效果一样，但是更容易理解。

### 4.7 使用完全限定的表名

输入：`SELECT [table name].[column name] FROM [database name].[table name];`



## 第五章 排序检索数据

### 5.1 排序数据

如果没有其他限定，检索出来的顺序并不是纯粹随机显示的，一半以它在底层中出现的顺序显示。

```sql
SELECT prod_name 
FROM products
ORDER BY prod_name;
```

对`prod_name`以字母序排序后的顺序显示查询结果。

### 5.2 按多个列排序

```sql
SELECT prod_id, prod_price, prod_name
FROM products
ORDER BY prod_price, prod_name;
```

先按`prod_price`进行排序，如果`prod_price`相同，就按`prod_name`的字母序进行排序。

### 5.3 指定排序方向

`ORDER BY`默认升序排列，如果想降序

```sql
SELECT prod_id, prod_price, prod_name
FROM products
ORDER BY prod_price DESC;
```

多个列的情形：

```sql
SELECT prod_id, prod_price, prod_name
FROM products
ORDER BY prod_price DESC, prod_name;
```

`DESC`关键字只应用到直接位于其前面的列名。所以`prod_price`按照降序排列，但是`prod_name`仍然是升序。

`ASC`代表升序，其实用不到，因为默认是升序的。

使用`ORDER BY`和`LIMIT`的组合，找出最贵的物品：

```sql
SELECT prod_price
FROM products
ORDER BY prod_price DESC
LIMIT 1;
```

`LIMIT 1`告诉MySQL仅返回一行。

## 第六章 过滤数据

### 6.1 使用WHERE子句

只检索所需数据需要指定搜索条件（search criteria），也被称为过滤条件（filter condition0）。

```mysql
SELECT prod_name, prod_price
FROM products
WHERE prod_price = 2.50;
```

### 6.2 WHERE子句操作符

|   操作符   |        说明        |
| :--------: | :----------------: |
|    `=`     |        等于        |
| `<>`或`!=` |       不等于       |
|    `<`     |        小于        |
|    `<=`    |      小于等于      |
|    `>`     |        大于        |
|    `>=`    |      大于等于      |
| `BETWEEN`  | 在指定的两个值之间 |

#### 6.2.1 检查单个值

```mysql
SELECT prod_name, prod_price
FROM products
WHERE prod_name = 'fuses';
```

```
+-----------+------------+ 
| prod_name | prod_price | 
+-----------+------------+ 
| Fuses     |       3.42 | 
+-----------+------------+ 
1 row in set (0.00 sec)    
```

#### 6.2.2 不匹配检查

```mysql
SELECT vend_id, prod_name
FROM products
WHERE vend_id != 1003;
```

```
+---------+--------------+
| vend_id | prod_name    |
+---------+--------------+
|    1001 | .5 ton anvil |
|    1001 | 1 ton anvil  |
|    1001 | 2 ton anvil  |
|    1002 | Fuses        |
|    1005 | JetPack 1000 |
|    1005 | JetPack 2000 |
|    1002 | Oil can      |
+---------+--------------+
7 rows in set (0.12 sec)
```

**何时使用引号**：单引号用来限定字符串，数值则不需要。

#### 6.2.3 范围检查

```mysql
SELECT prod_name, prod_price
FROM products
WHERE prod_price BETWEEN 5 AND 10;
```

```
+----------------+------------+
| prod_name      | prod_price |
+----------------+------------+
| .5 ton anvil   |       5.99 |
| 1 ton anvil    |       9.99 |
| Bird seed      |      10.00 |
| Oil can        |       8.99 |
| TNT (5 sticks) |      10.00 |
+----------------+------------+
5 rows in set (0.16 sec)
```

使用`BETWEEN`时，必须指定所需范围的低端值和高端值，用`AND`关键字分隔，匹配范围包含低端值和高端值。

#### 6.2.4 空值检查

```mysql
SELECT cust_id 
FROM customers
WHERE cust_email IS NULL;
```

```
+---------+              
| cust_id |              
+---------+              
|   10002 |              
|   10005 |              
+---------+              
2 rows in set (0.00 sec) 
```

## 第七章 数据过滤

### 7.1 组合WHERE子句

MySQL允许多个WHERE子句，以AND或OR子句的方式使用。

**操作符**用来联结或改变WHERE子句的关键字，也称为逻辑操作符。

#### 7.1.1 AND操作符

```mysql
SELECT prod_id, prod_price, prod_name
FROM products
WHERE vend_id = 1003 AND prod_price <= 10;
```

```
+---------+------------+----------------+
| prod_id | prod_price | prod_name      |
+---------+------------+----------------+
| FB      |      10.00 | Bird seed      |
| FC      |       2.50 | Carrots        |
| SLING   |       4.49 | Sling          |
| TNT1    |       2.50 | TNT (1 stick)  |
| TNT2    |      10.00 | TNT (5 sticks) |
+---------+------------+----------------+
```

#### 7.1.2 OR操作符

```mysql
SELECT prod_name, prod_price
FROM products
WHERE vend_id = 1002 OR vend_id = 1003;
```

```
+----------------+------------+
| prod_name      | prod_price |
+----------------+------------+
| Detonator      |      13.00 |
| Bird seed      |      10.00 |
| Carrots        |       2.50 |
| Fuses          |       3.42 |
| Oil can        |       8.99 |
| Safe           |      50.00 |
| Sling          |       4.49 |
| TNT (1 stick)  |       2.50 |
| TNT (5 sticks) |      10.00 |
+----------------+------------+
```

#### 7.1.3 计算次序

组合AND和OR带来了一个有趣的问题。假如需要列出价格为10美元（含）以上且由1002或1003制造的所有产品。下面的SELECT语句使用AND和OR操作符的组合建立了一个WHERE子句：

```mysql
SELECT vend_id, prod_name, prod_price
FROM products
WHERE vend_id = 1002 OR vend_id = 1003 AND prod_price >= 10;
```

```
+---------+----------------+------------+
| vend_id | prod_name      | prod_price |
+---------+----------------+------------+
|    1003 | Detonator      |      13.00 |
|    1003 | Bird seed      |      10.00 |
|    1002 | Fuses          |       3.42 |
|    1002 | Oil can        |       8.99 |
|    1003 | Safe           |      50.00 |
|    1003 | TNT (5 sticks) |      10.00 |
+---------+----------------+------------+
```

查询的结果中有两行的价格小于10美元。这是因为AND的优先级高于OR的优先级。解决办法就是利用圆括号来明确地分组相应地操作符。

```mysql
SELECT vend_id, prod_name, prod_price
FROM products
WHERE (vend_id = 1002 OR vend_id = 1003) AND prod_price >= 10;
```

```
+---------+----------------+------------+
| vend_id | prod_name      | prod_price |
+---------+----------------+------------+
|    1003 | Detonator      |      13.00 |
|    1003 | Bird seed      |      10.00 |
|    1003 | Safe           |      50.00 |
|    1003 | TNT (5 sticks) |      10.00 |
+---------+----------------+------------+
```

### 7.2 IN操作

IN操作符用来指定条件范围，范围中地每个条件都可以进行匹配。IN地合法值由逗号分隔，扩在圆括号中。

```mysql
SELECT prod_name, prod_price
FROM products
WHERE vend_id IN (1002,1003)
ORDER BY prod_name;
```

```
+----------------+------------+
| prod_name      | prod_price |
+----------------+------------+
| Bird seed      |      10.00 |
| Carrots        |       2.50 |
| Detonator      |      13.00 |
| Fuses          |       3.42 |
| Oil can        |       8.99 |
| Safe           |      50.00 |
| Sling          |       4.49 |
| TNT (1 stick)  |       2.50 |
| TNT (5 sticks) |      10.00 |
+----------------+------------+
```

IN操作符地优点：

* 在使用长的合法选项清单时，IN操作符的语法更清楚且更直观。
* 在使用IN时，计算的次序更容易管理（因为使用的操作符更少）。
* IN操作符一般比OR操作符清单执行更快。
* IN的最大优点是可以包含其他SELECT语句，使得能够更动态地建立WHERE子句。第14章将对此进行详细介绍。

### 7.3 NOT操作符

WHERE子句中的NOT操作符有且只有一个功能，那就是否定它之后所跟的任何条件。

```mysql
SELECT prod_name, prod_price
FROM products
WHERE vend_id NOT IN (1002,1003)
ORDER BY prod_name;
```

```
+--------------+------------+  
| prod_name    | prod_price |  
+--------------+------------+  
| .5 ton anvil |       5.99 |  
| 1 ton anvil  |       9.99 |  
| 2 ton anvil  |      14.99 |  
| JetPack 1000 |      35.00 |  
| JetPack 2000 |      55.00 |  
+--------------+------------+  
```

## 第八章 用通配符进行过滤

### 8.1 LIKE操作符

#### 8.1.1 百分号通配符

最常使用的通配符是百分号（%）。在搜索串中，%表示任何字符出现任意次数。例如，为了找出所有以词jet起头的产品，可使用以下SELECT语句：

```mysql
SELECT prod_id, prod_name
FROM products
WHERE prod_name LIKE 'jet%';
```

```
+---------+--------------+
| prod_id | prod_name    |
+---------+--------------+
| JP1000  | JetPack 1000 |
| JP2000  | JetPack 2000 |
+---------+--------------+
```

在刚才地检索中，忽略了大小写。如果需要，也可以区分大小写，这样JetPack就不能完成匹配了。

通配符可在搜索模式中任意位置使用，并且可以使用多个通配符。

```mysql
SELECT prod_id, prod_name
FROM products
WHERE prod_name LIKE '%anvil%';
```

```
+---------+--------------+
| prod_id | prod_name    |
+---------+--------------+
| ANV01   | .5 ton anvil |
| ANV02   | 1 ton anvil  |
| ANV03   | 2 ton anvil  |
+---------+--------------+
```

%能匹配0个、1个或多个字符，但是不能匹配NULL。

#### 8.1.2 下划线通配符

下划线只匹配单个字符。

```mysql
SELECT prod_id, prod_name
FROM products
WHERE prod_name LIKE '_ ton anvil';
```

```
+---------+-------------+
| prod_id | prod_name   |
+---------+-------------+
| ANV02   | 1 ton anvil |
| ANV03   | 2 ton anvil |
+---------+-------------+
```

与%百分号通配符地对比：

```mysql
SELECT prod_id, prod_name
FROM products
WHERE prod_name LIKE '% ton anvil';
```

```
+---------+--------------+
| prod_id | prod_name    |
+---------+--------------+
| ANV01   | .5 ton anvil |
| ANV02   | 1 ton anvil  |
| ANV03   | 2 ton anvil  |
+---------+--------------+
```

## 第九章 正则表达式

熟悉正则表达式的一个很好的办法是去Hackerrank上的`Regex`部分做练习，不过没有MySQL选项，可以通过python或shell来练习，大体思路基本一致，细节语法注意一下即可。

* https://www.runoob.com/regexp/regexp-syntax.html

### 9.2 使用MySQL正则表达式

#### 9.2.1 基本字符匹配

我们从一个非常简单的例子开始。下面的语句检索列prod_name包含文本1000的所有行：

```mysql
SELECT prod_name
FROM products
WHERE prod_name REGEXP '1000'
ORDER BY prod_name;
```

```
+--------------+
| prod_name    |
+--------------+
| JetPack 1000 |
+--------------+
```

上面的例子也可以用LIKE替换，但是比如下面的例子：

```mysql
SELECT prod_name
FROM products
WHERE prod_name REGEXP '.000'
ORDER BY prod_name;
```

```
+--------------+
| prod_name    |
+--------------+
| JetPack 1000 |
| JetPack 2000 |
+--------------+
```

`.`在正则表达式里面匹配一个字符。

MySQL中正则表达式不区分大小写，可以使用BINARY关键字强制区分。

#### 9.2.2 进行OR匹配

```mysql
SELECT prod_name
FROM products
WHERE prod_name REGEXP '1000|2000'
ORDER BY prod_name;
```

```
+--------------+
| prod_name    |
+--------------+
| JetPack 1000 |
| JetPack 2000 |
+--------------+
```

当然也可以用之前学到的百分号通配符和OR操作符来实现

```mysql
SELECT prod_name
FROM products
WHERE prod_name LIKE '%1000%' OR prod_name LIKE '%2000%'
ORDER BY prod_name;
```

也可以写成：

```mysql
SELECT prod_name
FROM products
WHERE prod_name LIKE '%000%'
ORDER BY prod_name;
```

查询结果都是相同的。

#### 9.2.3 匹配几个字符之一

匹配任何单一字符。但是，如果你只想匹配特定的字符，怎么办？可通过指定一组用[]括起来的字符来完成：

```mysql
SELECT prod_name
FROM products
WHERE prod_name REGEXP '[123] Ton'
ORDER BY prod_name;
```

```
+-------------+ 
| prod_name   | 
+-------------+ 
| 1 ton anvil | 
| 2 ton anvil | 
+-------------+ 
```

[]是另一种形式的OR语句。[123]是1|2|3的缩写。下面的例子说明使用[]的必要性：

```mysql
SELECT prod_name
FROM products
WHERE prod_name REGEXP '1|2|3 Ton'
ORDER BY prod_name;
```

```
+---------------+   
| prod_name     |   
+---------------+   
| 1 ton anvil   |   
| 2 ton anvil   |   
| JetPack 1000  |   
| JetPack 2000  |   
| TNT (1 stick) |   
+---------------+   
```

这并不是期望的输出。两个要求的行被检索出来，但还检索出了另外3行。之所以这样是由于MySQL假定你的意思是’1’或2’或3 ton'。除非把字符|括在一个集合中，否则它将应用于整个串。

字符集合也可以被否定，即，它们将匹配除指定字符外的任何东西。为否定一个字符集，在集合的开始处放置一个即可。因此，尽管[123]匹配字符1、2或3，但`[^123]`却匹配除这些字符外的任何东西。

#### 9.2.4 匹配范围

集合可用来定义要匹配的一个或多个字符。例如，下面的集合将匹配数字0到9：`[0-9]`，`[1-3]`和`[6-9]`也是合法的范围。

`[a-z]`匹配任意字母字符。

```mysql
SELECT prod_name
FROM products
WHERE prod_name REGEXP '[1-5] Ton'
ORDER BY prod_name;
```

```
+--------------+ 
| prod_name    | 
+--------------+ 
| .5 ton anvil | 
| 1 ton anvil  | 
| 2 ton anvil  | 
+--------------+ 
```

#### 9.2.5 匹配特殊字符

正则表达式语言由具有特定含义的特殊字符构成。我们已经看到`.`、`[]`、`|`和`-`等，还有其他一些字符。如果需要匹配这些字符，应该怎么办呢？

为了匹配特殊字符，必须用`\\`为前导。`\\-`表示查找`-`，`\\.`表示查找`.`。

```mysql
SELECT vend_name
FROM vendors
WHERE vend_name REGEXP '\\.'
ORDER BY vend_name;
```

```
+--------------+
| vend_name    |
+--------------+
| Furball Inc. |
+--------------+
```

如果匹配反斜杠，需要`\\\`。一半转义字符都是用单反斜杠，MySQL是双反斜杠，需要引起注意。

#### 9.2.6 匹配字符类

|      类      | 说明 |
| :----------: | :--: |
| `[:alnum:]`  |      |
| `[:alpha:]`  |      |
| `[:blank:]`  |      |
| `[:cntrl:]`  |      |
| `[:digit:]`  |      |
| `[:lower:]`  |      |
| `[:print:]`  |      |
| `[:punct:]`  |      |
| `[:space:]`  |      |
| `[:upper:]`  |      |
| `[:xdigit:]` |      |
| `[:graph:]`  |      |

#### 9.2.7 匹配多个实例

| 元字符  |             说明             |
| :-----: | :--------------------------: |
|   `*`   |        0个或多个匹配         |
|   `+`   |        1个或多个匹配         |
|   `?`   |        0个或一个匹配         |
|  `{n}`  |        指定数目的匹配        |
| `{n,}`  |     不少于指定数目的匹配     |
| `{n,m}` | 匹配数目的范围（m不超过255） |

```mysql
SELECT prod_name
FROM products
WHERE prod_name REGEXP '\\([0-9] sticks?\\)'
ORDER BY prod_name;
```

```
+----------------+
| prod_name      |
+----------------+
| TNT (1 stick)  |
| TNT (5 sticks) |
+----------------+
```

值得说明的是`?`，代表`?`前的`s`可以是0个或一个，所以可以匹配`stick`和`sticks`。

下面打算匹配连载一起的4位数字：

```mysql
SELECT prod_name
FROM products
WHERE prod_name REGEXP '[[:digit:]]{4}'
ORDER BY prod_name;
```

```
+--------------+
| prod_name    |
+--------------+
| JetPack 1000 |
| JetPack 2000 |
+--------------+
```

`[:digit:]`匹配任意数字，因为数字连在一起构成集合，所以是`[[:digit:]]`。

当然也可以按照下面这样写：

```mysql
SELECT prod_name
FROM products
WHERE prod_name REGEXP '[0-9][0-9][0-9][0-9]'
ORDER BY prod_name;
```

#### 9.2.8 定位符

为了匹配特定位置的文本，需要使用定位元字符。



|  元字符   |    说明    |
| :-------: | :--------: |
|    `^`    | 文本的开始 |
|    `$`    | 文本的结尾 |
| `[[:<:]]` |  词的开始  |
| `[[:>:]]` |    词的    |

例如，如果你想找出以一个数（包括以小数点开始的数）开始的所有产品，怎么办？简单搜索`[0-9\\.]`（或`[[:digit:]\\.]`）不行，因为它将在文本内任意位置查找匹配。解决办法是使用`^`定位符:

```mysql
SELECT prod_name
FROM products
WHERE prod_name REGEXP '^[0-9\\.]'
ORDER BY prod_name;
```

```
+--------------+ 
| prod_name    | 
+--------------+ 
| .5 ton anvil | 
| 1 ton anvil  | 
| 2 ton anvil  | 
+--------------+ 
```

## 第十章 创建计算字段

### 10.1 计算字段

计算字段并不实际存在于数据表中，是运行时在`SELECT`语句内创建的。

**字段（field）**基本上与列的意思相同。

### 10.2 拼接字段

**拼接（concatenate）**将值连接到一起构成单个值。

比如从`vendors`表中选取`vend_name`和`vend_country`按照`name(location)`的格式输出。

> 多数DBMS使用`+`或`||`来实现拼接，MySQL则使用`Concat()`函数来实现

```mysql
SELECT Concat(vend_name, ' (', vend_country, ') ')
FROM vendors
ORDER BY vend_name;
```

```
+---------------------------------------------+
| Concat(vend_name, ' (', vend_country, ') ') |
+---------------------------------------------+
| ACME (USA)                                  |
| Anvils R Us (USA)                           |
| Furball Inc. (USA)                          |
| Jet Set (England)                           |
| Jouets Et Ours (France)                     |
| LT Supplies (USA)                           |
+---------------------------------------------+
```

删除数据右侧多余的空格来整理数据，使用MySQL的`RTrim()`函数来完成。

```mysql
SELECT Concat(RTrim(vend_name), '(', RTrim(vend_country), ')')
FROM vendors
ORDER BY vend_name;
```

```
+---------------------------------------------------------+
| Concat(RTrim(vend_name), '(', RTrim(vend_country), ')') |
+---------------------------------------------------------+
| ACME(USA)                                               |
| Anvils R Us(USA)                                        |
| Furball Inc.(USA)                                       |
| Jet Set(England)                                        |
| Jouets Et Ours(France)                                  |
| LT Supplies(USA)                                        |
+---------------------------------------------------------+
```

对比发现函数`RTrim()`删除了字段右侧的空格。

> MySQL除了支持RTrim()函数外，还支持LTrim()，去掉左边的空格；和Trim()，删除串左右两边的空格。

**使用别名**

上面的结果拼接字段完成的很好，但是新计算的字段名字却是一长串`Concat(vend_name, ' (', vend_country, ') ')`，乍看很难知道这一列的内容和含义，所以可以使用**别名（`alias`），有时也称为导出列（derived column）**来进行替换，用关键字`AS`。

```mysql
SELECT Concat(RTrim(vend_name), '(', RTrim(vend_country), ')')
AS vend_title
FROM vendors
ORDER BY vend_name;
```

```
+------------------------+  
| vend_title             |  
+------------------------+  
| ACME(USA)              |  
| Anvils R Us(USA)       |  
| Furball Inc.(USA)      |  
| Jet Set(England)       |  
| Jouets Et Ours(France) |  
| LT Supplies(USA)       |  
+------------------------+  
```

> 别名常见的用途是：实际的表列名包含不符合规定的字符时重新命名它；原来的名字含糊或容易误解时扩充它。

### 10.3 执行算数计算

从`orderitems`表中计算出每项物品的总价值。

```mysql
SELECT prod_id, quantity, item_price, quantity * item_price AS expanded_price
FROM orderitems
WHERE order_num = 20005;
```

```
+---------+----------+------------+----------------+
| prod_id | quantity | item_price | expanded_price |
+---------+----------+------------+----------------+
| ANV01   |       10 |       5.99 |          59.90 |
| ANV02   |        3 |       9.99 |          29.97 |
| TNT2    |        5 |      10.00 |          50.00 |
| FB      |        1 |      10.00 |          10.00 |
+---------+----------+------------+----------------+
```

## 第十一章 使用数据处理函数

### 11.2 使用函数

#### 11.2.1 文本处理函数

使用函数`Upper()`将串内字符全部转换成大写。

```mysql
SELECT vend_name, Upper(vend_name) AS vend_name_upcase
FROM vendors
ORDER BY vend_name;
```

```
+----------------+------------------+
| vend_name      | vend_name_upcase |
+----------------+------------------+
| ACME           | ACME             |
| Anvils R Us    | ANVILS R US      |
| Furball Inc.   | FURBALL INC.     |
| Jet Set        | JET SET          |
| Jouets Et Ours | JOUETS ET OURS   |
| LT Supplies    | LT SUPPLIES      |
+----------------+------------------+
```

常用的文本处理函数：

| 函数          | 说明                                                         |
| ------------- | ------------------------------------------------------------ |
| `Left()`      | 返回串左边的字符，用法`LEFT(str,len)`                        |
| `Length()`    | 返回串的长度，用法`Length(str)`                              |
| `Locate()`    | 找出串的一个子串，用法通过`help locate`查看                  |
| `Lower()`     | 将串转为小写，用法`Lower(str)`                               |
| `LTrim()`     | 去掉串左边的空格，用法`LTrim(str)`                           |
| `Right()`     | 返回串右边的字符，用法`Right(str, len)`，从尾部数`len`个字符。 |
| `RTrim()`     | 去掉串右边的空格，用法`RTrim(str)`                           |
| `Soundex()`   | 返回串的的`SOUNDEX`值，通常`soundex`是由四个字符组成的代码，来评估相似性，但是MySQL的`soundex`返回任意长度的代码，可以用`substring`来取前四位。 |
| `SubString()` | 返回子串，用法`SUBSTRING(str,pos)`或`SUBSTRING(str,pos,len)` |
| `Upper()`     | 将串转为大写，用法`Upper(str)`                               |

`SOUNDEX`是一个将任何文本串转为描述其语音表示的字母数字模式的算法，考虑了类似的发音字符和音节，使得能对串进行发音比较而不是字母比较。

比如`customers`表中有一个顾客的联系名为`Y.Lee`，但是如果这是输入错误，实际应为`Y.Lie`，直接搜索不会有任何结果，但是用`Soundex`可以搜索到：

```mysql
SELECT cust_name, cust_contact
FROM customers
WHERE Soundex(cust_contact) = Soundex('Y Lie');
```

```
+-------------+--------------+
| cust_name   | cust_contact |
+-------------+--------------+
| Coyote Inc. | Y Lee        |
+-------------+--------------+
```

#### 11.2.2 日期和时间处理函数

常用日期和时间处理函数

| 函数            | 说明                                                    |
| --------------- | ------------------------------------------------------- |
| `AddDate()`     | 对一个日期增加天、周等                                  |
| `AddTime()`     | 对一个时间增加一个时间                                  |
| `CurDate()`     | 返回当前日期                                            |
| `CurTime()`     | 返回当前时间                                            |
| `Date()`        | 返回日期时间的日期部分                                  |
| `DateDiff()`    | 计算两个日期之差                                        |
| `Date_Add()`    | 很灵活的日期运算函数，通过`help date_add`来了解详细功能 |
| `Date_Format()` | 返回一个格式化的 日期或时间串                           |
| `Day()`         | 返回日期的天数部分                                      |
| `DayOfWeek()`   | 返回一个日期对应星期几                                  |
| `Hour()`        | 返回一个时间的小时部分                                  |
| `Minute()`      | 返回一个时间的分钟部分                                  |
| `Month()`       | 返回一个时间的月份部分                                  |
| `Now()`         | 返回当前日期和时间                                      |
| `Second()`      | 返回一个时间的秒部分                                    |
| `Time()`        | 返回一个日期时间的时间部分                              |
| `Year()`        | 返回一个日期的年份部分                                  |

注意日期格式最好为`yyyy-mm-dd`，这样就排除了多义性，虽然支持两位数的年份，但是最好写完整的4位数的形式。

```mysql
SELECT cust_id, order_num
FROM orders
WHERE order_date = '2005-09-01';
```

```
+---------+-----------+
| cust_id | order_num |
+---------+-----------+
|   10001 |     20005 |
+---------+-----------+
```

但是上面的这种做法并不可靠，因为假如存储的日期形式是`2005-09-01 11: 30: 05`，那么上面的语句是无法完成检索的。所以应该使用`Date()`函数来提取日期部分。

```mysql
SELECT cust_id, order_num
FROM orders
WHERE Date(order_date) = '2005-09-01';
```

```
+---------+-----------+
| cust_id | order_num |
+---------+-----------+
|   10001 |     20005 |
+---------+-----------+
```

另外一种常见的检索是查询某一年份或某一月份下的所有订单：

```mysql
SELECT cust_id, order_num
FROM orders
WHERE Date(order_date) BETWEEN '2005-09-01' AND '2005-09-30';
```

```
+---------+-----------+
| cust_id | order_num |
+---------+-----------+
|   10001 |     20005 |
|   10003 |     20006 |
|   10004 |     20007 |
+---------+-----------+
```

另外的一种方法是使用函数`Year()`和`Month()`：

```mysql
SELECT cust_id, order_num
FROM orders
WHERE Year(order_date) = 2005 AND Month(order_date) = 9;
```

```
+---------+-----------+
| cust_id | order_num |
+---------+-----------+
|   10001 |     20005 |
|   10003 |     20006 |
|   10004 |     20007 |
+---------+-----------+
```

#### 11.2.3 数值处理函数

常用数值处理函数

| 函数     | 说明               |
| -------- | ------------------ |
| `Abs()`  | 返回数值的绝对值   |
| `Cos()`  | 返回角度的余弦     |
| `Exp()`  | 返回数值的指数值   |
| `Mod()`  | 返回余数           |
| `Pi()`   | 返回圆周率         |
| `Rand()` | 返回一个随机数     |
| `Sin()`  | 返回一个角度的正弦 |
| `Sqrt()` | 返回一个数的平方根 |
| `Tan()`  | 返回一个角度的正切 |

## 第十二章 汇总数据

### 12.1 聚集函数

**聚集函数（aggregate function）**运行在行组上，计算和返回单个值的函数。

| 函数      | 说明             |
| --------- | ---------------- |
| `AVG()`   | 返回一列的平均值 |
| `COUNT()` | 返回某一列的行数 |
| `MAX()`   | 返回某列的最大值 |
| `MIN()`   | 返回某列的最小值 |
| `SUM()`   | 返回某列数值之和 |

#### 12.1.1 `AVG()`函数

```mysql
SELECT AVG(prod_price) AS avg_price
FROM products;
```

```
+-----------+
| avg_price |
+-----------+
| 16.133571 |
+-----------+
```

发现返回的数值是一个浮点数，后面跟随一长串的数字，如果我们只想要某一个精度，那么可以使用`Round()`函数：

```mysql
SELECT Round(AVG(prod_price), 3) AS avg_price
FROM products;
```

```
+-----------+  
| avg_price |  
+-----------+  
|    16.134 |  
+-----------+  
```

计算特定商品的平均价格：

```mysql
SELECT AVG(prod_price) AS avg_price
FROM products
WHERE vend_id = 1003;
```

```
+-----------+
| avg_price |
+-----------+
| 13.212857 |
+-----------+
```

#### 12.1.2 `COUNT()`函数

`COUNT()`函数的两种典型用法：

* `COUNT(*)`对表中一列的行的数目进行计数，无论是否包含空值`NULL`
* `COUNT(column)`对特定列的行进行计数，忽略空值

假如我们对`customers`表进行统计，首先来看一下表中的内容：

```mysql
SELECT * FROM customers;
```

```
+---------+----------------+---------------------+-----------+------------+----------+--------------+--------------+---------------------+
| cust_id | cust_name      | cust_address        | cust_city | cust_state | cust_zip | cust_country | cust_contact | cust_email          |
+---------+----------------+---------------------+-----------+------------+----------+--------------+--------------+---------------------+
|   10001 | Coyote Inc.    | 200 Maple Lane      | Detroit   | MI         | 44444    | USA          | Y Lee        | ylee@coyote.com     |
|   10002 | Mouse House    | 333 Fromage Lane    | Columbus  | OH         | 43333    | USA          | Jerry Mouse  | NULL                |
|   10003 | Wascals        | 1 Sunny Place       | Muncie    | IN         | 42222    | USA          | Jim Jones    | rabbit@wascally.com |
|   10004 | Yosemite Place | 829 Riverside Drive | Phoenix   | AZ         | 88888    | USA          | Y Sam        | sam@yosemite.com    |
|   10005 | E Fudd         | 4545 53rd Street    | Chicago   | IL         | 54545    | USA          | E Fudd       | NULL                |
+---------+----------------+---------------------+-----------+------------+----------+--------------+--------------+---------------------+
```

然后统计所有客户：

```mysql
SELECT COUNT(*) AS num_cust
FROM customers;
```

```
+----------+
| num_cust |
+----------+
|        5 |
+----------+
```

然后对具有电子邮件的客户进行计数：

```mysql
SELECT COUNT(cust_email) AS num_cust
FROM customers;
```

```
+----------+
| num_cust |
+----------+
|        3 |
+----------+
```

#### 12.1.3 `MAX()`函数

```mysql
SELECT MAX(prod_price) AS max_price
FROM products;
```

```
+-----------+
| max_price |
+-----------+
|     55.00 |
+-----------+
```

#### 12.1.4 `MIN()`函数

```mysql
SELECT MIN(prod_price) AS min_price
FROM products;
```

```
+-----------+
| min_price |
+-----------+
|      2.50 |
+-----------+
```

#### 12.1.5 `SUM()`函数

```mysql
SELECT SUM(quantity) AS items_ordered
FROM orderitems
WHERE order_num = 20005;
```

```
+---------------+
| items_ordered |
+---------------+
|            19 |
+---------------+
```

`SUM()`函数也可以用来合计计算值：

```mysql
SELECT SUM(item_price * quantity) AS total_price
FROM orderitems
WHERE order_num = 20005;
```

```
+-------------+
| total_price |
+-------------+
|      149.87 |
+-------------+
```

### 12.2 聚集不同值

上面介绍的五个聚集函数都可以有下面的使用方法：

* 对所有的行执行计算，指定`ALL`参数或不给参数（`ALL`是默认行为）
* 只包含不同值，指定`DISTINCT`参数

```mysql
SELECT AVG(DISTINCT prod_price) AS avg_price
FROM products
WHERE vend_id = 1003;
```

```
+-----------+
| avg_price |
+-----------+
| 15.998000 |
+-----------+
```

### 12.3 组合聚集函数

```mysql
SELECT 
	COUNT(*) AS num_items,
	MIN(prod_price) AS price_min,
	MAX(prod_price) AS price_max,
	AVG(prod_price) AS price_avg
FROM products;
```

```
+-----------+-----------+-----------+-----------+
| num_items | price_min | price_max | price_avg |
+-----------+-----------+-----------+-----------+
|        14 |      2.50 |     55.00 | 16.133571 |
+-----------+-----------+-----------+-----------+
```

## 第十三章 分组数据

### 13.2 创建分组

分组的一个例子：

```mysql
SELECT vend_id, Count(*) AS num_prods
FROM products
GROUP BY vend_id;
```

```
+---------+-----------+
| vend_id | num_prods |
+---------+-----------+
|    1001 |         3 |
|    1002 |         2 |
|    1003 |         7 |
|    1005 |         2 |
+---------+-----------+
```

`GROUP BY`子句是按`vend_id`排序并分组数据，所以`Count()`函数计算的是每个`vend_id`而不是计算所有的。

* `GROUP BY`子句可以包含任意数目的列，所以能对分组进行嵌套，为数据分组提供更细致的控制

使用`WITH ROLLUP`可以得到每个分组及每个分组汇总的数据。

```mysql
SELECT vend_id, Count(*) AS num_prods
FROM products
GROUP BY vend_id WITH ROLLUP;
```

### 13.3 过滤分组

过滤分组，可以根据包括哪些分组，排除哪些分组进行查询。注意`WHERE`过滤行，而`HAVING`过滤分组。

先来看一下不过滤分组的结果：

```mysql
 SELECT cust_id, Count(*) AS orders 
 FROM orders 
 GROUP BY cust_id;
```

```
+---------+--------+
| cust_id | orders |
+---------+--------+
|   10001 |      2 |
|   10003 |      1 |
|   10004 |      1 |
|   10005 |      1 |
+---------+--------+
```

然后过滤分组：

```mysql
SELECT cust_id, Count(*) AS orders
FROM orders
GROUP BY cust_id
HAVING Count(*) >= 2;
```

```
+---------+--------+
| cust_id | orders |
+---------+--------+
|   10001 |      2 |
+---------+--------+
```

看一个`WHERE`和`HAVING`同时使用的例子：

```mysql
SELECT vend_id, Count(*) AS num_prods
FROM products
WHERE prod_price >= 10
Group BY vend_id
HAVING Count(*) >= 2;
```

```
+---------+-----------+
| vend_id | num_prods |
+---------+-----------+
|    1003 |         4 |
|    1005 |         2 |
+---------+-----------+
```

### 13.4 分组和排序

区分`GROUP BY`和`ORDER BY`：

```mysql
SELECT order_num, SUM(quantity * item_price) AS ordertotal
FROM orderitems
GROUP BY order_num
HAVING SUM(quantity * item_price) >= 50;
```

```
+-----------+------------+
| order_num | ordertotal |
+-----------+------------+
|     20005 |     149.87 |
|     20006 |      55.00 |
|     20007 |    1000.00 |
|     20008 |     125.00 |
+-----------+------------+
```

```mysql
SELECT order_num, SUM(quantity * item_price) AS ordertotal
FROM orderitems
GROUP BY order_num
HAVING SUM(quantity * item_price) >= 50
ORDER BY ordertotal;
```

```
+-----------+------------+   
| order_num | ordertotal |   
+-----------+------------+   
|     20006 |      55.00 |   
|     20008 |     125.00 |   
|     20005 |     149.87 |   
|     20007 |    1000.00 |   
+-----------+------------+   
```

## 第十四章 使用子查询

### 14.1 子查询

**查询（query）**：任何SQL语句都是查询，一般指`SELECT`语句。SQL语句支持创建**子查询（subquery）**，即嵌套其他查询中的查询。

### 14.2 利用子查询进行过滤

```mysql
SELECT cust_id
FROM orders
WHERE order_num IN (SELECT order_num
                    FROM orderitems 
                    WHERE prod_id = 'TNT2');
```

```
+---------+  
| cust_id |  
+---------+  
|   10001 |  
|   10004 |  
+---------+  
```

检索到了客户ID，下一步检索客户名：

```mysql
SELECT cust_id, cust_contact
FROM customers
WHERE cust_id IN (SELECT cust_id
                  FROM orders
                  WHERE order_num IN (SELECT order_num
                                      FROM orderitems 
                                      WHERE prod_id = 'TNT2'));
```

```
+---------+--------------+
| cust_id | cust_contact |
+---------+--------------+
|   10001 | Y Lee        |
|   10004 | Y Sam        |
+---------+--------------+
```

### 14.3 作为计算字段使用子查询

```mysql
SELECT cust_name, cust_state,(SELECT Count(*)
                             FROM orders
                             WHERE orders.cust_id = customers.cust_id) AS orders
FROM customers
ORDER BY cust_name;
```

```
+----------------+------------+--------+
| cust_name      | cust_state | orders |
+----------------+------------+--------+
| Coyote Inc.    | MI         |      2 |
| E Fudd         | IL         |      1 |
| Mouse House    | OH         |      0 |
| Wascals        | IN         |      1 |
| Yosemite Place | AZ         |      1 |
+----------------+------------+--------+
```

**相关子查询（correlated subquery）**涉及外部查询的子查询。

任何时候只要列明可能存在多义性，就必须使用这种语法（表明和列明由一个句点分隔）。

## 第十五章 联结表

### 15.1 联结

#### 15.1.1 关系表

**外键（foreign key）**：外键为某个表中的一列，它包含另一个表的主键值，定义了两个表之间的关系。 

关系数据库的可伸缩性远比非关系数据库要好。

### 15.2 创建联结

```mysql
SELECT vend_name, prod_name, prod_price
FROM vendors, products
WHERE vendors.vend_id = products.vend_id
ORDER BY vend_name, prod_name;
```

```
+-------------+----------------+------------+
| vend_name   | prod_name      | prod_price |
+-------------+----------------+------------+
| ACME        | Bird seed      |      10.00 |
| ACME        | Carrots        |       2.50 |
| ACME        | Detonator      |      13.00 |
| ACME        | Safe           |      50.00 |
| ACME        | Sling          |       4.49 |
| ACME        | TNT (1 stick)  |       2.50 |
| ACME        | TNT (5 sticks) |      10.00 |
| Anvils R Us | .5 ton anvil   |       5.99 |
| Anvils R Us | 1 ton anvil    |       9.99 |
| Anvils R Us | 2 ton anvil    |      14.99 |
| Jet Set     | JetPack 1000   |      35.00 |
| Jet Set     | JetPack 2000   |      55.00 |
| LT Supplies | Fuses          |       3.42 |
| LT Supplies | Oil can        |       8.99 |
+-------------+----------------+------------+
```

#### 15.2.1 `WHERE`子句的重要性

**笛卡尔积（cartesian product）**由没有联结条件的表关系返回的结果为笛卡尔积。

比如：

```mysql
SELECT vend_name, prod_name, prod_price
FROM vendors, products
ORDER BY vend_name, prod_name;
```

仅仅是去掉了`WHERE`子句，结果会发生很大改变。返回的数据是用供应商匹配了每个产品，包含了不正确的匹配。

#### 15.2.2 内部联结

目前为止所用的联结成为**等值联结（equijoin）**，它基于两个表之间的相等测试，也称为**内部联结**。

```mysql
SELECT vend_name, prod_name, prod_price
FROM vendors INNER JOIN products
ON vendors.vend_id = products.vend_id
ORDER BY vend_name, prod_name;
```

```
+-------------+----------------+------------+
| vend_name   | prod_name      | prod_price |
+-------------+----------------+------------+
| ACME        | Bird seed      |      10.00 |
| ACME        | Carrots        |       2.50 |
| ACME        | Detonator      |      13.00 |
| ACME        | Safe           |      50.00 |
| ACME        | Sling          |       4.49 |
| ACME        | TNT (1 stick)  |       2.50 |
| ACME        | TNT (5 sticks) |      10.00 |
| Anvils R Us | .5 ton anvil   |       5.99 |
| Anvils R Us | 1 ton anvil    |       9.99 |
| Anvils R Us | 2 ton anvil    |      14.99 |
| Jet Set     | JetPack 1000   |      35.00 |
| Jet Set     | JetPack 2000   |      55.00 |
| LT Supplies | Fuses          |       3.42 |
| LT Supplies | Oil can        |       8.99 |
+-------------+----------------+------------+
```

发现查询的结果一致，规定最好首选使用`INNER JOIN`语法。

#### 15.2.3 联结多个表

列出所有表，然后定义表之间的关系：

```mysql
SELECT prod_name, vend_name, prod_price, quantity
FROM orderitems, products, vendors
WHERE products.vend_id = vendors.vend_id
	AND orderitems.prod_id = products.prod_id
	AND order_num = 20005;
```

```
+----------------+-------------+------------+----------+
| prod_name      | vend_name   | prod_price | quantity |
+----------------+-------------+------------+----------+
| .5 ton anvil   | Anvils R Us |       5.99 |       10 |
| 1 ton anvil    | Anvils R Us |       9.99 |        3 |
| TNT (5 sticks) | ACME        |      10.00 |        5 |
| Bird seed      | ACME        |      10.00 |        1 |
+----------------+-------------+------------+----------+
```

回顾14章的`SELECT`子句查询`TNT2`的信息，这里可以用联结的方式来代替。

```mysql
SELECT cust_id, cust_contact
FROM customers
WHERE cust_id IN (SELECT cust_id
                  FROM orders
                  WHERE order_num IN (SELECT order_num
                                      FROM orderitems 
                                      WHERE prod_id = 'TNT2'));
```

```mysql
SELECT cust_name, cust_contact
FROM customers, orders, orderitems
WHERE customers.cust_id = orders.cust_id
	AND orderitems.order_num = orders.order_num
	AND prod_id = 'TNT2';
```

```
+----------------+--------------+
| cust_name      | cust_contact |
+----------------+--------------+
| Coyote Inc.    | Y Lee        |
| Yosemite Place | Y Sam        |
+----------------+--------------+
```

## 第十六章 创建高级联结

### 16.1 使用表别名

第十章中使用关键字`AS`来用别名引用被检索的表列，SQL还允许给表名起别名。这样做的两个主要理由：

* 缩短SQL语句
* 允许在单条`SELECT`语句中多次使用相同的表

```mysql
SELECT cust_name, cust_contact
FROM customers AS c, orders AS o, orderitems AS oi
WHERE c.cust_id = o.cust_id
	AND oi.order_num = o.order_num
	AND prod_id = 'TNT2';
```

```
+----------------+--------------+  
| cust_name      | cust_contact |  
+----------------+--------------+  
| Coyote Inc.    | Y Lee        |  
| Yosemite Place | Y Sam        |  
+----------------+--------------+  
```

### 16.2 使用不同类型的联结

之前看到的都是等值联结（内联结），其他三种联结：自联结、自然联结和外部联结。

#### 16.2.1 自联结

假如某些物品存在问题，现在想知道生产该产品的供应商的其他物品是否也存在问题。

```mysql
SELECT prod_id, prod_name
FROM products
WHERE vend_id = (SELECT vend_id
                 FROM products
                 WHERE prod_id = 'DTNTR');
```

```
+---------+----------------+
| prod_id | prod_name      |
+---------+----------------+
| DTNTR   | Detonator      |
| FB      | Bird seed      |
| FC      | Carrots        |
| SAFE    | Safe           |
| SLING   | Sling          |
| TNT1    | TNT (1 stick)  |
| TNT2    | TNT (5 sticks) |
+---------+----------------+
```

使用联结的等效方法：

```mysql
SELECT p1.prod_id, p1.prod_name
FROM products AS p1, products AS p2
WHERE p1.vend_id = p2.vend_id
AND p2.prod_id = 'DTNR';
```

```
+---------+----------------+
| prod_id | prod_name      |
+---------+----------------+
| DTNTR   | Detonator      |
| FB      | Bird seed      |
| FC      | Carrots        |
| SAFE    | Safe           |
| SLING   | Sling          |
| TNT1    | TNT (1 stick)  |
| TNT2    | TNT (5 sticks) |
+---------+----------------+
```

自联结通常作为外部语句用来替代从相同表中检索数据时使用的子查询语句。使用联结和子查询性能存在差异，实际使用时应测试两种方法的快慢。

#### 16.2.2 自然联结

























