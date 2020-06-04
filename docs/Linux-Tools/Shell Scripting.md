> # Linux Command Line and Shell Scripting Bible

又名《Linux命令行与shell脚本编程大全》，可以配合Hackerrank的shell习题来巩固提高。

[TOC]

# 第3章 基本的bash shell命令

![1583592110567](F:\Project\Reading-Notes\Linux\assets\1583592110567.png)

## 3.5 文件和目录列表

### 3.5.1 基本列表功能

```bash
# -F命令可以轻松区分文件和目录，在目录的后面加上了正斜线/
$ ls -F
CS-631/  Scheme/   cpp/   myGitBook/  reveal.js/  unpv13e/
Python/  apue.3e/  docs/  photo/      test.txt
# -a把隐藏文件和其他文件都显示出来
# -R递归显示当前目录下的文件和子目录下的文件
```

### 3.5.2 显示长列表

```bash
# 显示更多相关信息
$ ls -l
```

## 3.6 处理文件

### 3.6.1 创建文件

```bash
$ touch [filename]
```

### 3.6.2 复制文件

```bash
$ cp source destination
```

如果复制的文件在目标路径下已经存在，可以加上`-i`选项强制shell询问是否覆盖。



**比较文件**

```
//file1.txt
I need to buy apples.
I need to run the laundry.
I need to wash the dog.
I need to get the car detailed.

//file2.txt
I need to buy apples.
I need to do the laundry.
I need to wash the car.
I need to get the dog detailed.
```

我们使用`diff`比较他们的不同：

```bash
$ diff file1.txt file2.txt
2,4c2,4
< I need to run the laundry.
< I need to wash the dog.
< I need to get the car detailed.
---
> I need to do the laundry.
> I need to wash the car.
> I need to get the dog detailed.
```

diff描述两个文件不同的方式是告诉我们怎么样改变第一个文件之后与第二个文件匹配。我们看看上面的比较结果中的第一行 2,4c2,4 前面的数字2,4表示第一个文件中的行，中间有一个字母c表示需要在第一个文件上做的操作(a=add,c=change,d=delete)，后面的数字2,4表示第二个文件中的行。

2,4c2,4 的含义是：第一个文件中的第[2,4]行(注意这是一个闭合区间，包括第2行和第4行)需要做出修改才能与第二个文件中的[2,4]行相匹配。
接下来的内容则告诉我们需要修改的地方，前面带 < 的部分表示左边文件的第[2,4]行的内容，而带> 的部分表示右边文件的第[2,4]行的内容，中间的 --- 则是两个文件内容的分隔符号。



# 第11章 构建基本脚本

## 11.2 创建shell脚本文件

在文件的第一行必须加上

```bash
#!/bin/bash
```

可以使用分毫`;`将命令放在一行。但是此时脚本文件不具有执行权限，所以：

```bash
$ chmod u+x filename.sh
# 第二种方式
$ chmod 777 filename.sh
```

## 11.3 显示消息

```bash
$ echo The time and date are && date
The time and date are
Sat Mar  7 23:03:28 DST 2020
```

会发现文本和`date`的显示信息分别在不同的行，如果想在同一行显示，可以使用`-n`选项。

```bash
$ echo -n 'The time and date are: ' && date
The time and date are: Sat Mar  7 23:04:02 DST 2020
```

参考链接：<https://www.cnblogs.com/anttech/p/11247423.html>

这里值得区分一下单引号`'`，双引号`"`和反引号在`echo`里的区别。

单引号：强引用，所见即所得，即单引号里面包含什么就输出什么。

双引号：弱引用，输出双引号的所有内容；如果内容中有命令（要反引）、变量、特殊转义，会先把变量、命令、转义字符解析出结果，然后在输出最终内容

反引号：一般用于命令，执行的时候命令会被执行，相当于`$()`，赋值和输出都要用反引号引起来。

通过几个例子来区分：

```bash
$ echo $USER
kylin
$ echo '$USER'
$USER
$ echo "$USER"
kylin
$ echo "`$USER`"
kylin: command not found
```









## 11.4 使用变量

### 11.4.2 用户变量

引用一个变量时需要使用`$`符号，比如：

```sh
#!/bin/bash
days=10
guest='Katie'
echo "$guest checked in &days days ago"
days=5
guest='Jessica'
echo "$guest checked in &days days ago"
```

```bash
$ sudo chmod 777 test.sh
$ ./test.sh
```

### 11.4.3 命令替换





### 11.5.2 输入重定向

```bash
$ wc < test.txt
```

`wc`命令一般会有3个输出：

* 文本的行数
* 文本的词数
* 文本的字节数

内联重定向：

```bash
$ wc << EOF
> test string 1
> test string 2
> test string 3
> EOF
 3  9 42
```



## 11.6 管道

有时需要将一个命令的输出作为另一个命令的输入。

## 11.7 数学运算

![1584546798309](F:\Project\Reading-Notes\Linux\assets\1584546798309.png)

**注意：许多命令在`expr`里存在歧义**

比如执行

```bash
$ expr 1 * 2
expr: syntax error
```

这是因为在`shell`里面`*`另有含义，所以需要转义字符`\`。

```bash
$ expr 1 \* 2
2
```

### 11.7.2 使用方括号

如果我们在编写程序的过程中，还要注意符号存在歧义，显然会产生很多麻烦，但是使用方括号就不用考虑产生歧义的问题了。

```bash
#!/bin/bash
var=$[1*2]
echo $var
```

### 11.7.3 浮点数解决方案

有几种解决方案能够克服bash中数学运算的整数限制。最常见的方案是用内建的bash计算器，叫作bc。

要退出bash计算器，你必须输入quit。

```bash
$ bc
1 + 2
3
1 / 2
0
3.44 / 5
0
```

浮点运算是由内建变量scale控制的。必须将这个值设置为你希望在计算结果中保留的小数位数，否则无法得到期望的结果。

```bash
$ bc
scale=4
3.44 / 5
.6880
```

scale变量的默认值是0。在scale值被设置前，bash计算器的计算结果不包含小数位。在将其值设置成4后，bash计算器显示的结果包含四位小数。-q命令行选项可以不显示bash计算器冗长的欢迎信息。

除了普通数字，bash计算器还能支持变量。

```bash
$ bc
var = 1     
var2 = 2    
var + var2  
3           
print var
1
quit
```

**在脚本中使用bc**

可以用命令替换运行bc命令，并将输出赋给一个变量。基本格式如下：

```bash
#!/bin/bash
var=$(echo "scale=4; 3.44 / 5" | bc)
echo The answer is $var
```

但是这种使用方法还是不够优雅，所以可以使用内联重定向：

```bash
#!/bin/bash
var1=10.46
var2=43.67
var3=33.2
var4=71
var5=$(bc << EOF
scale = 4
a1 = ($var1 * $var2)
b1 = ($var3 * $var4)
a1 + b1
EOF
)
echo $var5
```

## 11.8 退出脚本

查看退出状态码：

```bash
$ date && echo $?
Thu Mar 19 00:15:16 DST 2020
0
$ absd
Command 'absd' not found, did you mean:

  command 'amsd' from deb ion
  command 'afsd' from deb openafs-client

Try: sudo apt install <deb name>
$ echo $?
127
```

![1584548206479](F:\Project\Reading-Notes\Linux\assets\1584548206479.png)

### 11.8.2 `exit`命令

默认情况下，shell脚本会以脚本中的最后一个命令的退出状态码退出。

你可以改变这种默认行为，返回自己的退出状态码。exit命令允许你在脚本结束时指定一个退出状态码。

# 第12章 使用结构化命令

## 12.1 使用`if-then`语句

```sh
if command
then
	command
fi
```

bash shell的if-then语句和C++相比，C++在`if`后的语句会产生一个求值结果为`true`或`false`，但是bash shell会先执行`if`后面的命令，如果命令的状态码是0，位于`then`后的命令会被执行，否则不执行。

```sh
#!/bin/bash
if pwd
then
	echo "it worded!"	
fi
```

也存在`if-then`语句的另一种形式：

```sh
if command; then
	command
fi
```

通过分号把`then`和`if`放在同一行，看起来和其他语言更接近。

## 12.2 `if-then-else`语句

```sh
if command
then
	command
else
	command
fi
```

## 12.3 嵌套`if`

```sh
if command1
then
	commands
elif command2
then
	commands
fi
```

## 12.4 `test`命令

```sh
if test condition
then 
	command
fi
```

也可以使用方括号定义测试条件，但是注意第一个方括号后和第二个方括号前必须加上一个空格。

```sh
if [ condition ]
then
	command
fi
```

`test`可以判断三类条件：

* 数值比较
* 字符串比较
* 文件比较

### 12.4.1 数值比较

|   比较    |        描述        |
| :-------: | :----------------: |
| `a -eq b` |  检查a和b是否相等  |
| `a -ge b` | 检查a是否大于等于b |
| `a -gt b` |   检查a是否大于b   |
| `a -le b` | 检查a是否小于等于b |
| `a -lt b` |   检查a是否小于b   |
| `a -ne b` |  检查a和b是否相等  |

不能再`test`命令中使用浮点值。

### 12.4.2 字符串比较

|    比较    |      描述      |
| :--------: | :------------: |
|  s1 = s2   | s1和s2是否相同 |
|  s1 != s2  | s1和s2是否不同 |
| `s1 \< s2` |    s1比s2小    |
| `s1 \> s2` |    s1比s2大    |
|    -n s    | s的长度是否非0 |
|    -z s    |  s长度是否为0  |

注意小于号和大于号要进行转义，否则会被解释为重定向。

另一个问题就是和`sort`相关，比如下面：

```sh
#!/bin/bash
s1=Testing
s2=testing
if [ $s1 \< $s2 ]
then
	echo "$s1 is less than $s2"
else
	echo "$s1 is greater than $s2"
fi
```

```bash
$ ./test.sh
Testing is less than testing
```

因为比较测试中按照ASCII顺序，大写字母被认为小于小写字母。

```bash
$ touch testfile
$ vim testfile
```

在`testfile`里写入

```
Testing
testing
```

```bash
$ sort testfile
Testing
testing
```

sort命令使用的是系统的本地化语言设置中定义的排序顺序。对于英语，本地化设置指定了在排序顺序中小写字母出现在大写字母前。

注意大于号和小于号会产生输入/输出重定向的歧义，所以需要转义字符。

### 12.4.3 文件比较

![1584714776568](F:\Project\Reading-Notes\Linux\assets\1584714776568.png)

1. 检查目录

```shell
#!/bin/bash
# Look before you leap
#
jump_directory=/home/kylin
#
if [ -d $jump_directory ]
then
    echo "The $jump_directory directory exists"
    cd $jump_directory
    ls
else
	echo "The $jump_directory directory does not exist"
fi
#
```

```bash
$ sudo chmod 777 test.sh
$ ./test.sh
The /home/kylin directory exists
12.sh  CS-631  CS631-APUE  Python  Scheme  apue.3e  cpp  docs  myGitBook  photo  reveal.js  unpv13e
```

2. 检测对象是否存在

```shell
#!/bin/bash
# Check if either a directory or file exists
#
location=$HOME
file_name="sentinel"
#
if [ -e $location ]
then #Directory does exist
    echo "OK on the $location directory."
    echo "Now checking on the file, $file_name."
    #
    if [ -e $location/$file_name ]
    then #File does exist
        echo "OK on the filename"
        echo "Updating Current Date..."
        date >> $location/$file_name
    #
    else #File does not exist
        echo "File does not exist"
        echo "Nothing to update"
    fi
#
else #Directory does not exist
    echo "The $location directory does not exist."
    echo "Nothing to update"
fi
```



## 12.5 复合测试条件

```shell
[ condition1 ] && [ condition2 ]
[ condition1 ] || [ condition2 ]
```

## 12.6 `if-then`的高级特性

### 12.6.1 使用双括号

双括号名命令提供了更多的数学操作，对于其他编程语言来讲比较友好。

![1584715640445](F:\Project\Reading-Notes\Linux\assets\1584715640445.png)

### 12.6.2 使用双方括号

双方括号命令提供了针对字符串比较的高级特性。

```shell
[[ expression ]]
```

双方括号里的expression使用了test命令中采用的标准字符串比较.

在模式匹配中，可以定义一个正则表达式

```shell
#!/bin/bash
# using pattern matching
#
if [[ $USER == k* ]]
then
	echo "Hello $USER"
else
	echo "Sorry, I do not know you"
fi
```

```bash
$ ./test.sh
Hello kylin
```

## 12.7 `case`命令

case命令会采用列表格式来检查单个变量的多个值。

```shell
#!/bin/bash
# using the case command
#
case $USER in
rich | barbara)
    echo "Welcome, $USER"
    echo "Please enjoy your visit";;
testing)
	echo "Special testing account";;
jessica)
	echo "Do not forget to log off when you're done";;
*)
	echo "Sorry, you are not allowed here";;
esac
```

# 第13章 更多结构化命令

## 13.1 `for`命令

```shell
for var in list
do
	commands
done
```

### 13.1.2 读取列表中的复杂值

```shell
$ cat badtest1
#!/bin/bash
# another example of how not to use the for command
for test in I don't know if this'll work
do
	echo "word:$test"
done
$ ./badtest1
word:I
word:dont know if thisll
word:work
$
```

shell看到了列表值中的单引号并尝试使用它们来定义一个单独的数据值.

for循环假定每个值都是用空格分割的

### 13.1.5 更换字段分隔符

bash会将空格、制表、换行作为分隔符。

要解决这个问题，可以在shell脚本中临时更改IFS环境变量的值来限制被bash shell当作字段
分隔符的字符。例如，如果你想修改IFS的值，使其只能识别换行符，那就必须这么做：

```shell
IFS=$'\n'
```

```shell
#!/bin/bash
# reading values from a file
file="states"
IFS=$'\n'
for state in $(cat $file)
do
	echo "Visit beautiful $state"
done
```

如果要指定多个IFS字符，只要将它们在赋值行串起来就行。

```shell
IFS=$'\n':;"
```

这个赋值会将换行符、冒号、分号和双引号作为字段分隔符。如何使用IFS字符解析数据没
有任何限制。

### 13.1.6 用通配符读取目录

```shell
#!/bin/bash
# iterate through all the files in a directory
for file in /home/kylin/*
do
if [ -d "$file" ]
then
	echo "$file is a directory"
elif [ -f "$file" ]
then
	echo "$file is a file"
fi
done
```

```bash
$ ./test.sh
/home/kylin/12.sh is a file
/home/kylin/CS-631 is a directory
/home/kylin/CS631-APUE is a directory
/home/kylin/Python is a directory
/home/kylin/Scheme is a directory
/home/kylin/apue.3e is a directory
/home/kylin/cpp is a directory
/home/kylin/docs is a directory
/home/kylin/myGitBook is a directory
/home/kylin/photo is a directory
/home/kylin/reveal.js is a directory
/home/kylin/unpv13e is a directory
```

在Linux中，目录名和文件名中包含空格当然是合法的。要适应这种情况，应该将`$file`变量用双引号圈起来。如果不这么做，遇到含有空格的目录名或文件名时就会有错误产生.

也可以在for命令中列出多个目录通配符，将目录查找和列表合并进同一个for语句。

## 13.2 C语言风格的`for`命令

```shell
for (( variable assignment ; condition ; iteration process ))
```

例如：

```shell
for (( a = 1; a < 10; a++ ))
```

有些部分并没有遵循bash shell标准的for命令：

* 变量赋值可以有空格；
* 条件中的变量不以美元符开头；
* 迭代过程的算式未用expr命令格式。

```shell
#!/bin/bash
# testing the C-style for loop
for (( i = 1; i <= 10; i++ ))
do
	echo "The next number is $i"
done
```

```shell
#!/bin/bash
# multiple variables
for (( a = 1, b = 10; a <= 10; a++, b-- ))
do
	echo "$a - $b"
done
```

## 13.3 `while`命令

基本格式：

```shell
while test-command
do
	command
done
```

## 13.4 `until`命令

```shell
#!/bin/bash
# using the until command
var1=100
until [ $var1 -eq 0 ]
do
    echo $var1
    var1=$[ $var1 - 25 ]
done
```

```shell
var=100
until (( $var == 0))
do
	echo $var
	var=$(( $var - 25 ))
done
```



















