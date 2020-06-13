> # Higher Than 75 Marks

Tags: `Easy` `Basic Seelct`

Links: https://www.hackerrank.com/challenges/more-than-75-marks/problem

-----

Query the *Name* of any student in **STUDENTS** who scored higher than 75 *Marks*. Order your output by the *last three characters* of each name. If two or more students both have names ending in the same last three characters (i.e.: Bobby, Robby, etc.), secondary sort them by ascending *ID*.

**Input Format**

The **STUDENTS** table is described as follows:

![img](https://s3.amazonaws.com/hr-challenge-images/12896/1443815243-94b941f556-1.png)

The *Name* column only contains uppercase (`A`-`Z`) and lowercase (`a`-`z`) letters.

**Sample Input**

![img](https://s3.amazonaws.com/hr-challenge-images/12896/1443815209-cf4b260993-2.png)

**Sample Output**

```
Ashley
Julia
Belvet
```

**Explanation**

Only Ashley, Julia, and Belvet have *Marks* > . If you look at the last three characters of each of their names, there are no duplicates and 'ley' < 'lia' < 'vet'.

-----

解法一：使用`right`函数

```
Name: 'RIGHT'                                                       
Description:                                                        
Syntax:                                                             
RIGHT(str,len)                                                      
                                                                    
Returns the rightmost len characters from the string str, or NULL if
any argument is NULL.                                               
                                                                    
URL: https://dev.mysql.com/doc/refman/5.7/en/string-functions.html  
                                                                    
Examples:                                                           
mysql> SELECT RIGHT('foobarbar', 4);                                
        -> 'rbar'                                                   
```

```mysql
SELECT name
FROM students
WHERE marks > 75
ORDER BY RIGHT(name, 3), id;
```

解法二：使用`substr`函数

```
Name: 'SUBSTR'
Description:
Syntax:
SUBSTR(str,pos), SUBSTR(str FROM pos), SUBSTR(str,pos,len), SUBSTR(str
FROM pos FOR len)

SUBSTR() is a synonym for SUBSTRING().
//注意下标从1开始计数
```

```mysql
SELECT name
FROM students
WHERE marks > 75
ORDER BY SUBSTR(name, length(name) - 2, 3), ID;
```

