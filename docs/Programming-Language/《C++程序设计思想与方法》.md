> # 《C++程序设计：思想与方法》

`内容说明：笔记中积累的课后程序题或者教材中的案例是自己第一次写出错或者没有教材写的好的部分，部分题目个人认为比较有代表性，便于举一反三，也在积累范围内`

`所用教材为《C++程序设计：思想与方法（第二版）》翁惠玉编著，也是本校CS专业的教材`

## 第三章 逻辑思维——分支程序设计

```c++
//程序设计题5
/*
问题描述：
输入一个字母，判断该字母是元音还是辅音字母，用if语句和switch语句实现
*/

#include<iostream>
using namespace std;

int main()
{
    char ch='d';

    if (ch >= 'a' && ch <= 'z'){
        ch = ch - 'a' + 'A';
        if (ch <= 'A' || ch >= 'Z') cout << "不是字母" << endl;
        else{
            if (ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U') cout << "元音字母" << endl;
            else cout << "辅音字母" << endl;
        }
    }

    return 0;
}

/*
解析：
两个要点：一个是默认输入的是小写字母，练习字母大小写转换；另一个是if语句的嵌套
*/
```

```C++
//程序设计题 7
/*
问题描述：
凯撒密码是将每个字母循环后移三个位置后输出。如“a”变成“d”，“b”变成“e”，“z”变成“c”，编写程序实现
*/

#include<iostream>
using namespace std;

int main()
{
    char ch='z';

    ch = (ch - 'a' + 3) % 26 + 'a';

    cout << ch << endl;

    return 0;
}

/*
解析：
这种问题可以有很多种变化，比如一段文字加密之类的，比较关键的在于'x'，'y'，'z'这三个字母，采用取模运算解决。当然也可以参照第五题，考虑不是字母和大小写的情况。
*/
```



## 第四章 重复控制——循环程序设计

```c++
//课本P62例题
/*
问题描述：编写计算e^x展开式的程序
*/
#include<iostream>
using namespace std;

int main()
{
    double ex=0,x,p=1;
    int i = 0;
    
    cout << "请输入x的数值" ；
    cin >> x;
  
    while(p>1e-6){
        ex += p;
        ++i;
        p *= x / i;
    }
    
    return 0;
}
```

```c++
//程序设计题 2
/*
问题描述：
写一个程序，提示用户输入一个整数，然后输出这个整型数地每一位数字，数字之间有一个空格。例如输入12345时，输出为1 2 3 4 5
*/

#include<iostream>
using namespace std;

int main()
{
    int n=12345,i;

    for (i=1;n>=i;i*=10);

    do{
        i/=10;
        cout << n/i << ' ';
        n %= i;
    }while(i>1);

    return 0;
}

/*
解析：
难点主要是如何判断输入数字的位数，并且从高位到低位输出，巧妙地地方在于do while部分地设计，先利用i来判断位数，然后利用整除地性质依次取各个位上地数字
*/
```

```C++
//程序设计题 3
/*
问题描述：
斐波那契数列F0=0，F1=1，F2=F0+F1，写一个程序顺序显示F0到F15
*/

#include<iostream>
using namespace std;

int main()
{
    int f0=0,f1=1,f2,i;

    cout<<f0<<" "<<f1<< ' ';

    for (i=2;i<=15;++i){
        f2=f0+f1;
        cout << f2 << ' ';
        f0=f1;
        f1=f2;
    } 
    
    return 0;
}

/*
解析：
设计主要是在for循环部分，通过赋值来实现
*/
```

```c++
//程序设计题 9
/*
问题描述：
输入一个年份（大于2010），输出这一年的年历，已知2010年1月1日是星期五
*/
#include<iostream>
using namespace std;

int main()
{
    int year = 2014,i,day = 0,weekday=0;

    //计算所求年份距离2010年的天数，闰年366天，非闰年365天
    for (i=2010;i<year;++i){
        day += 365;
        if ((i%4 == 0 && i%100 != 0) || i%400 == 0) ++day;
    }

    weekday = (5 + day) % 7; //判断所求年份是星期几

    //打印每一年的日历
    for (int month = 1;month<=12;++month){
        cout << month << "月份" << endl;
        cout << "Sun\tMon\tTue\tWed\tThu\tFri\tSat\n";
        //区分不同月份
        switch(month){
            case 4: case 6: case 9: case 11: day=30;break;
            case 2:
                if ((year%4 == 0 && year%100 != 0) || year%400 == 0) day = 29; 
                else day = 28;break;
			default: day = 31;
        }
        //打印每个月的日历
        for (i=0;i<weekday;++i) cout << '\t';
        for (i=1;i<=day;++i){
            cout << i << '\t';
            weekday = ++weekday % 7;
            if(weekday == 0) cout << endl;
        }
		cout << endl;
    }

    return 0;
}
```

```c++
//程序设计题11
/*
问题描述：
有算式 ABCD * E = DCBA，ABCD各不相同，编程找出这些数字
*/
#include<iostream>
using namespace std;

int main()
{
    int A,B,C,D,E,num1,num2;

    for (num1=1023;num1<=9876;++num1){
        A = num1 / 1000;
        B = num1 % 1000 / 100;
        C = num1 % 100 / 10;
        D = num1 % 10;
        if( D==0 || A == B || A == C || A == D || B == C || B == D || C == D ) continue;
        num2 = D*1000 + C*100 + B*10 + A;
        for (E=2;E<=9;++E){
            if ( E == A || E == B || E == C || E == D ) continue;
            if ( num1 * E == num2 ){
                cout << num1 << '*' << E << '=' << num2 << endl;
            }
        }
    }

    return 0;
}

/*
解析：
此题有两种思路，一种是用五个循环去寻找，但是效率太差，另一种就是考虑四位数最小的是1023，最大的是9876，而且A和D只能是1-9，B和C是0-9，E只能是2-9，并且要判断各个数字之间不相等
最后结果是 2178*4=8712
*/
```

```c++
//程序设计题13
//编写程序，输入某人的出生年月，输出10000天和20000天的纪念日期
#include<iostream>
using namespace std;

int main()
{
	int year,month,day;
	int resday,i;

	cout << "请输入您的出生年月日：";
	cin >> year >> month >> day;

	for ( i = 0; i <2 ; ++i ){ //分别计算10000天和20000天纪念日
		resday = 10000; //设置剩余天数为10000天
		switch(month){ //扣除当月剩余的天数
			case 4: case 6: case 9: case 11:
				resday -= 30 - day;break;
			case 2:
				if ( year%100 != 0 && year%4 == 0 || year%400 == 0 ) resday -= 29 - day;
				else resday -= 28 - day;break;
			default : resday -= 31 - day;
		}
		day = 0;
		while ( resday>0 && day == 0 ){
			month = month % 12 + 1; //从出生月的下一个月开始计算
			if ( month == 1 ) ++year;
			switch(month){
				case 4: case 6: case 9: case 11:
					if ( resday > 30 ) resday -= 30; else day = resday;
					break;
				case 2:
					if ( year%100 != 0 && year%4 == 0 || year%400 == 0 ){
						if ( resday > 29 ) resday -= 29;else day = resday;
					}
					else {
						if ( resday > 28 ) resday -= 28;else day =	resday;
					}
					break;
				default : 
					if ( resday > 31 ) resday -= 31;else day = resday;
			}
		}

		//输出10000天和20000天的纪念日期
		if ( i == 0 ) cout << "10000天的纪念日期是" << year << "年" << month << "月" << day << "日" << endl;
		else cout << "20000天的纪念日期是" << year << "年" << month << "月" << day << "日" << endl;
	}

	return 0;
}

/*
本题和第9题打印年历类似，可以认为打印年里做的是“加法”，本题做的是“减法”。
由于是输出20000天和10000天，天数有区别，但是计算方法的结构是类似的，所以可以通过for语句来进行两次循环实现，在计算20000天日期时，把第10000天的日期当作新的起始点。对于不同月份的处理，可通过switch语句解决，值得注意是2月要判断当年是否是闰年。月份确定之后，判断剩余天数是否大于0来确定具体日期。
判断计算是否准确可以与 http://bjtime.cn/riqi/ 的计算结果比对，验证后无误。
如果题目里附加了出生日期是星期几（n表示），则判断10000/20000天是星期几只需要增加 date=(n+10000)%7，和打印年历的方法是一样的 
*/
```



**程序设计题18：$\pi$ 值可以通过无穷级数计算：$$ \pi = \frac{4}{1} - \frac{4}{3} + \frac{4}{5} - \frac{4}{7} + \cdots $$**

​	本题其实不难写出程序，对于每一项可以写出通项公式 $$a_i = (-1)^i \frac{4}{2i-1}$$，书中给出的方法是判断i是奇数还是偶数，个人想法是充分利用前一项：已经知道前一项的数值，后一项可以表示为$$a_{i+1} = a_i \times (-1) \times \frac{2i-1}{2i+1}$$，所以可以写成：

```c++
#include<iostream>
using namespace std;

int main()
{
	int i,n;
    double a=4.0/1,pi=0
        
	cout << "请输入项数n：";
    cin >> n;
    
    for ( i=0; i<n ; ++i ){
        pi += a;
        a = a*(-1)*1.0*(2*i-1)/(2*i+1);
    }
    
    cout << "pi的近似值是：" << pi << endl;
    
    return 0;
}
```



## 第五章 批量数据处理——数组

```c++
//教材P90统计一段话有多少个单词
#include<iostream>
using namespace std;

int main()
{
	char sent[ ]="we are family, do you know?", prev=' ';
	int i=0,num=0;
	
	for (i=0;sent[i] != '\0';++i){
		if (prev == ' ' && sent[i] != ' ')++num;
		prev = sent[i];
	}
	
	cout << num << endl;
	return 0;
}

/*
设计思路：
当前字符非空，前一个字符为空，则判定为一个单词，字符串以'\0'结束作为循环终止条件
*/
```

```c++
//教材P80二分查找程序
#include<iostream>
using namespace std;

int main()
{
	int array[ ] = {0,1,2,3,4,5,6,7,8,9};
    int lh = 0, rh = 9, mid,x;
    
    cout << "请输入要查找的整数" << endl;
    cin >> x；
    
    while( lh <= rh ){
        mid = (lh + rh ) / 2;
        if ( x == array[mid] ){
            cout << x << "的位置是" << mid ;
            break;
        }
        if ( x < array[mid] ) rh = mid - 1;
        else lh = mid + 1;
    }
    if ( lh > rh) cout << "没有找到" << endl;
    
    return 0;
}

/*
这里只需要注意一点，因为用if判断了mid的数组值，所以如果不等则左边为mid-1，右边mid+1
*/
```

```c++
//教材P82直接选择排序
#include<iostream>
using namespace std;

int main()
{
    int array[ ] = {2,5,1,9,10,0,4,8,7,6};
    int lh,min,tmp,k;

    for ( lh = 0; lh < 10; ++lh ){
        //min记录最小数值的下标
        min = lh;
        //查找从lh开始数组的最小值
        for ( k = lh; k < 10; ++k){
            if ( array[k] < array[min] ) min = k;
        }
        //交换数组lh和min位置的数值
        tmp = array[lh];
        array[lh] = array[min];
        array[min] = tmp;
    }

    for (k=0;k<10;++k) cout << array[k] << '\t';

    return 0;
}
//本程序是升序排序，相应的降序也应该会
//整体结构：先定义数组，然后排序算法，最后记得要输出排序后的结果
```

```c++
//教材P84冒泡排序
#include<iostream>
using namespace std;

int main()
{
    int array[ ] = {0,3,5,1,8,7,9,4,2,10,6};
    int n=11;
    int i,j,tmp;
    bool flag; //记录一趟起泡过程中有没有发生数据交换

    for ( i=1;i<n;++i ){
        flag = false;
        for ( j=0; j<n-i; ++j ){
            if ( array[j] > array[j+1] ){
                tmp = array[j];
                array[j] = array[j+1];
                array[j+1] = tmp;
                flag = true;
            }
        }
		if ( !flag ) break;
    }

    for (i=0;i<n;++i) cout << array[i] << ' ';

    return 0;
}
/*
通过设置flag来判断一趟起泡中是否发生数据交换，最初犯的错误是没注意到if ( !flag )写在了for循环里面，这样第一次判断0<3，所以flag是false，则直接就输出array了。另一点是注意每一次起泡过程初始都要设置flag = false。同样如果降序则只需要改动if中的条件
*/
```

```c++
//矩阵乘法的两个自编例子
//二维矩阵乘法（方阵型）
#include<iostream>
using namespace std;

int main()
{
    int a[2][2]={2,1,4,3},b[2][2]={1,2,1,0},c[2][2]={0};
    int i,j,k;

    for ( i=0; i<2; ++i ){
        for ( j=0; j<2; ++j ){
            for ( k=0; k <2; ++k ){
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    for ( i=0; i<2; ++i ){
		cout << endl;
        for ( j=0; j<2; ++j ){
            cout << c[i][j] << '\t';
        }
    }

    return 0;
}

//二维矩阵乘法
#include<iostream>
using namespace std;

int main()
{
    int a[2][3]={1,2,3,1,0,-1},b[3][4]={1,0,-1,2,-1,1,3,0,0,-2,-1,3},c[2][4]={0};
    int i,j,k;

    for ( i=0; i<2; ++i ){
        for ( j=0; j<4; ++j ){
            for ( k=0; k < 3; ++k ){
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    for ( i=0; i<2; ++i ){
		cout << endl;
        for ( j=0; j<4; ++j ){
            cout << c[i][j] << '\t';
        }
    }

    return 0;
}
//这里的都是具体了行和列，教材是最大限制了行和列，后面可以动态设置
```



**（教材P87）N阶幻方是一个由N$\times$N的由1到$$\N^2$$之间的自然数构成的矩阵，他的每一行、每一列和对角线之和均相等。构建技巧（限于奇数阶）：**

* 第一个元素放在第一行中间一列
* 下一个元素放在当前元素的上一行、下一列
* 如果上一行、下一列已经有内容，则下一个元素放在当前列的下一行

思路解析：解决此问题主要有关键的两个步骤，第一个是如何表示一个位置没有元素，第二个是如何找到新的位置实现回绕。第一个问题的解决可以设置初始值为0，第二个问题下一行是当前行+1，实现回绕则可以用 (row+1)%N，上一行可以用 (row-1+N)%N 表示，列同理，仅以三阶为例。

```c++
#include<iostream>
using namespace std;

int main()
{
    int col,row,N=3;
    int magic[3][3]={0};
    int i,j;

    row=0;
    col=(N-1)/2;
    magic[row][col] = 1;

    for ( i=2;i<=N*N;++i ){
        //判断上一行下一列是否是0
        if ( magic[ (row-1+N) % N ][ (col+1) % N ] == 0 ) {
            row = (row-1+N) % N; //上一行
            col = (col+1) % N;  //下一列
            magic[row][col] = i;
        }
        else {//放在当前列的下一行
            row = (row+1) % N;
            magic[row][col] = i;
        }
    }

    for (i=0;i<3;++i){  //输出幻方
        for ( j=0;j<3;++j){
            cout << magic[i][j] << '\t';
        }
		cout << endl;
    }

    return 0;
}

```

```c++
//程序设计题1
/*
问题描述：
读入7个裁判的分数，去掉一个最高分和最低分，求出剩余分数的平均值并输出，分别写出使用数组和不使用的程序。
*/
#include<iostream>
using namespace std;

int main()
{ //使用数组
	double socre[7];
	double max=0,min=10,avg=0;

	cout << "请输入7个裁判的分数：";
	for ( i=0; i<7; ++i )
		cin >> socre[i];

	for ( i=0; i<7; ++i){
		avg += socre[i];
		if ( socre[i]>max ) max = socre[i];
		if ( socre[i]<min ) min = socre[i];
	}

	avg = ( avg - (max + min) ) / 5;

	cout << "平均成绩为：" << avg <<endl;

	return 0;
}

/*
解析：
可以先把每个数据存入一个数组，先求出总和，在计算总和的同时就可以得出最大值和最小值，只需要最后减去最大值和最小值再求平均即可
*/

#include<iostream>
using namespace std;

int main()
{ //不使用数组
	double socre=0;
	double max=0,min=10,avg=0;

	cout << "请输入7个裁判的分数：";
	for ( i=0; i<7; ++i )
		cin >> socre;
		avg += socre;
		if ( socre>amx ) max = socre;
		if ( socre<min ) min = socre;

	avg = ( avg - (max + min) ) / 5;

	cout << "平均成绩为：" << avg <<endl;

	return 0;
}

/*
解析：
不使用数组就是只用一个变量score每次存储一个数据，剩余和使用数组的程序类似
*/
```

```c++
//程序设计题3
/*
问题描述：
埃拉托色尼算法：列出2~n所有的数字，第一个元素画圈，表示是素数，如果后面的元素是画圈元素的倍数则画叉，重复以上操作即可得到所有给定范围内的素数，现在n=1000
*/
#include<iostream>
using namespace std;

int main()
{
	bool num[2000001];
	int n=1000,i,j;
	
	for(i=2;i<=n;++i) num[i] = true;
	
	for (i=2;i<=n;++i){
		if (num[i]){
			for (j=2;j*i<=n;++j) num[j*i]=false;
		}
	}
	
	for(i=2;i<=n;++i) 
		if (num[i]) cout << i << '\t';
	
	return 0;
}

/*
难度不大，区别在于将i的倍数设置为false，最初想法是从j=2开始，依次检验每个数，显然不如直接选出i的倍数元素快。这里注意其实是浪费了数组的0和1所在的位置，那么后面在判断位置以及输出的过程中，位置信息和普通的计数规则相同。
*/

//使用set的方法
#include <iostream>
#include <iomanip>
#include <set>
using namespace std;


int main()
{
    int n = 200000;
    set<int> primeSet;
    
    for (int i = 2; i <= n; ++i)
        primeSet.insert(i);
        
    for (int m = 2; m * m <= n; ++m){
        if (primeSet.find(m) != primeSet.end()){
            int i = 2 * m;
            while (i <= n){
                primeSet.erase(i);
                i += m;
            }
        }    
    }
    
    auto iter = primeSet.begin();
    int count = 0;
    while(iter != primeSet.end()){
        ++count;
        cout << setw(5) << *iter;    
        if (count % 10 == 0)
            cout << endl;
        ++iter;
    }
    cout << endl;
}
/*
第二种方法比第一种方法做了优化，只需要比较sqrt(n)个元素即可
*/
```



**程序设计题5 : 随机生成100个0-99之间的随机数，存入数组data，冒泡排序后输出。**

**程序设计题6：随机生成100个0-99之间不同的随机数，存入数组data，冒泡排序后输出。**

两个题目之间的区别在于第一个未要求随机数不同，第二个要求各个随机数之间不相同。程序设计相当于之前内容的小综合，分为三个阶段，第一个是生成0-99之间的随机数，第二个是冒泡排序，第三个是输出排序结果。生成随机数和教材上自动出题类似，冒泡排序固定格式，输出环节一个for循环即可结束。此题目值得积累的是设计题6的解法，此题可有三种方法求解：

1. 第一种方法是每次生成一个随机数，然后和之前存入数组data的元素比较是否相同。很明显，时间性能很差。
2. 第二种方法是再用一个数组mark来标记此数值是否出现过，出现过为1，未出现过为0。性能明显好于第一种，但是也不是最好。
3. 第三种方法是模拟扑克洗牌的过程，注意到生成100个0-99个随机数，其实就是0-99打断顺序后存入到数组data，实际上和扑克洗牌的思想是一致的。先定义一个数组data[100]，data[i]的初值为i，然后进行若干次随机交换将数据打乱。每次随机交换需要产生两个下标i和j，交换data[i]和data[j]，交换的次数越多，数据越乱。

```c++
//第二种方法
#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

int main()
{
	int data[10],mark[10]={0};
	int i,j,tmp;
	bool flag;

	srand(time(NULL));

	//产生100个随机数并存入data[]
	for ( i=0; i<10; ++i){
		do
		{
			data[i] = rand() % 10;
		} while ( mark[ data[i] ] != 0 );
		mark[ data[i] ] = 1;
	}

	//冒泡排序过程
	for ( i=1; i<10; ++i){
		flag = false;
		for ( j=0; j<10-i; ++j ){
			if ( data[j+1]<data[j] ){
				tmp = data[j];
				data[j] = data[j+1];
				data[j+1] = tmp;
				flag = true;
			}
		}
		if (!flag) break;
	}

	//输出排序结果
	for ( i=0; i<10; ++i) cout << data[i] << '\t';

	return 0;
}
```

可以证明，Fisher-Yates算法中每个数字出现在某个位置的概率是相同的，比如n-1出现在最后一个位置就需要产生的a等于n-1，所以概率是$$\frac{1}{n}$$，如果出现在倒数第二个位置，需要第一次换走，第二次换到倒数第二个，所以用概率乘法$$\frac{n-1}{n} \times \frac{1}{n-1} = \frac{1}{n}$$，以此类推可以证明出现在其他位置概率也相同。

---

*To shuffle an array a of n elements ( indices 0 ... n-1 ):*

​	**for** i **from** n-1 **downto** 1 **do**

​		j $$\leftarrow$$ random integer with 0 $$\leq$$ j $$\leq$$ i

​		exchange a[j] and a[i]

---

```c++
//Fisher-Yates洗牌算法
#include<iostream>
#include<ctime>
#include<cstdlib>
using namespace std;

void shuffle_FisherYates(int *arr, const int len);

int main()
{
	int data[100];

	for (int i=0; i < 100; ++i) data[i] = i;

	shuffle_FisherYates(data, 100);

	for (int i=1; i < 100; ++i ){
		bool flag = false;
		
		for (int j=0; j < 100-i;++j){
			if ( data[j] > data[j+1]){
				swap(data[j], data[j + 1]);
				flag = true;
			}
		}
	}

	for (int i=0;i<100;++i) cout << data[i] << '\t';

	return 0;
}

void shuffle_FisherYates(int *arr, const int len)
{
	srand(time(NULL));
	
	for (int i = len-1;i>0;i--)
	{
		int a = rand()%(i+1);
		swap(arr[i], arr[a]);
	}
}
```



**杨辉三角（Pascal三角）**：

输出杨辉三角的办法有两种，一种是使用一维数组来存储数字信息（除了1），另一种是根据递推公式推导出同一行的数字之间的递推关系，这样就不用数组，更加节省空间。

先分析不使用数组的方法，杨辉三角中的数字本质上是$$(x+a)^n$$的展开式的系数$$C_n^k$$，k表示第k项。并且可以得到结论$$C_n^{k+1} = C_n^k \times \frac{n-k}{k+1}$$，所以如果知道首项，就可以直接推出余下的项，而已知每行数字的第一个数是1，所以可以推出每一项。需要注意的一点是程序的17行，这里不可以写成`c *= (i-j) / (j+1);`，理由是如果这么写，计算过程是先计算右边，然后再乘以c的值，但是当`j=i-2`时，`(i-j) / (j+1)=0`，则`j=i-1`时，也是输出0，后两项输出都为0，而写成`c = c*(i-j) / (j+1);`，根据运算的优先级，会先计算`c*(i-j)`，这样就不会出现0了。

```c++
//程序设计题9——不使用数组的解法
#include <iostream>
using namespace std;
 
int main()
{
	int n=6;
	int i,j,c;

	for (i=0;i<n;++i)
	{
		for (j=0;j<n-i;++j) cout << ' ';
		c = 1;
		for (j=0;j<=i;++j)
		{
			cout << c << ' ';
			c = c*(i-j) / (j+1);
		}
		cout << endl;
	}

	return 0;
}
```

使用数组的方法相较于上面的方法会略显复杂，但是更符合出题人的本来目的——考察数组的用法。使用数组的方法把杨辉三角分成四部分来分析：

1. 左边的空白部分（右边的空白部分不用考虑，换行即可）
2. 每行的第一个数字1
3. 每行的最后一个数字1
4. 每行数字除了1以外的数字

逐一分析每个部分的实现，用户输入`n`，算法输出`n`行的杨辉三角，可以先把整个三角看成一个由数字和空格组成的方阵，方阵的边长肯定由第n行来决定，第`n`行`n`个数字和`n-1`个空格，所以长度为`2n-1`。虽然看似是方阵，但是注意到第`i`行与第`i-1`行的关联，而与`i-1`行之前的数值无关，所以只需要一个一维数组存储`i-1`行的信息即可，存储后更新即可。左边空白部分要根据每行的数字信息推出，每行的总长是`2n-1`，第`i`行`i`个数字和`i-1`个空格，所以两边的空格总数为`2n-1-(2i-1)=2(n-i)`，因为数字居中，所以左边空白的数量为`n-i`，显然一个for循环解决每行的第一个1可以通过`a[n-i]`输出，每行除了两个1外还剩下`i-2`个数字，很容易通过for循环输出，但是有个特殊的就是第一行，只有一个1，所以要增加一个if判断。

```c++
//程序设计题9——使用数组的方法
#include <iostream>
#include <iomanip>
using namespace std;
 
int main()
{
	int n=6;
	int a[11];
	int i,j;

	for (i=1;i<=n;++i)
	{
		for (j=0;j<n-i;++j) cout << setw(4) << ' ';
		cout << (a[n-i] = 1);
		for (j=n-i+2;j<n+i-2;j += 2)
			cout << setw(4) << ' ' << (a[j] = a[j-1] + a[j+1]);
		if (i!=1)
			cout << setw(4) << ' ' << (a[n+i-2] = 1);
		cout << endl;
	}

	return 0;
}
```



## 第六章 过程封装——函数

```c++
//教材P121 递归函数之汉诺塔问题
#include<iostream>
using namespace std;

void Hanoi(int n,char start,char finish,char tmp);

int main()
{
	void Hanoi(3,'1','3','2');

	return 0;
}

//作用：将n个盘子从start借助tmp移动到finish
//用法：Hanoi(n,start,finish,tmp)
void Hanoi(int n,char start,char finish,char tmp)
{
	if ( n == 1 ) cout << start << "->" << finish;
	else{
		Hanoi(n-1,start,tmp,finish);
		cout << start << "->" << finish << endl;
		Hanoi(n-1,tmp,finish,start);
	}
}
/*
解析：
移动n个盘子，思路是先将n-1个借助finish移动到tmp，这时候start上只剩下最大的一个盘子，然后输出从start移动到finish，最后借助start把n-1个盘子从tmp移动到finish
*/
```

```c++
//教材P124-P125
//“ABCDE”的全排列的递归实现
#include<iostream>
#include<cstring>
using namespace std;

void perm(char str[],int k);
void swap(char str[],int k,int i);

int main()
{
	char str[] = "ABCDE";

	perm(str,0);

	return 0;
}

//作用：输出从第K个字符到最后一个字符的全排列
//用法perm(str,k)
void perm(char str[],int k)
{
	int i;
	if ( k==strlen(str) ) cout << str << endl;
	else{
		for ( i=k;i<strlen(str);++i){
			swap(str,k,i);
			perm(str,k+1);
			swap(str,k,i);
		}
	}
}

//作用：交换数组str中的第k个和第i个元素
//用法：swap(str,k,i)
void swap(char str[],int k,int i)
{
	char tmp = str[k];
	str[k] = str[i];
	str[i] = tmp;
}
```



**八皇后问题**：在一个8$$\times$$8的棋盘上放8个皇后，使八个皇后中没有两个以上的皇后会出现在同一行、同一列或者同一对角线。

表示棋盘最先想到的是用一个二维数组，但是我们完全可以用col[k]=i来表示第k列的第i行放置了皇后，为了检查皇后的放置是否满足要求，可以定义：

* row[9]，row[i]=true表示第i行上没有皇后
* 数组digLeft[16]，digLeft[i]=true表示右高左低的对角线上没有皇后，从左上角到右下角标号为1-15
* 数组digright[16]，digright[i]=true表示右低左高的对角线上没有皇后，从左下角到右上角标号为1-15

第i行第k列放置了皇后，则row[i]=false, digLeft[k+i-1] =false, digRight[n+k-i]=false。其中对角线的设置仅以对角线右高左低的情况（即digLeft）来推导，以次对角线为分界线，分为上半部和下半部，任何一条对角线与水平方向的夹角都是$$45^o$$，如果出现在对角线上半部，第k列表示距离左边垂直空格有k-1个，i行就已经表示第i条对角线了，所以推导出元素在i+k-1条对角线。其实还应该补充一点，8$$\times$$8的棋盘有15条对角线，推广就是n$$\times$$n棋盘有2n-1条对角线（一个方向，垂直的方向也是2n-1条），因为关注方阵最左边和最下边，这些元素必然在右高左低的不同对角线上，所以是n+n-1=2n-1条。

函数queen表示完成第k列及以后列皇后的放置，k=1即八皇后问题。首先在第一列的第一行放置皇后，相应的row，digLeft和digRight都应变为false，如果k=8了则表示已经找到一种解，否则执行queen(k+1)，回溯的时候应该要清除row，digLeft和digRight的信息，还原为true。代码和书中P127有所不同，这里在queen函数里增加了一个sum引用，用来输出共有多少种解法，因为可以查阅资料知道八皇后问题有92种解法，所以可以通过输出sum来验证。

```c++
//教材P126 八皇后问题——基于回溯法
#include<iostream>
using namespace std;

void queen(int k,int &sum);
int col[9];
bool row[9],digLeft[16],digRight[16];

int main()
{
	int i,sum=0;

	for ( i=0; i<=8; ++i ) row[i] = true;
	for ( i=0; i<=15; ++i ) digRight[i] = digLeft[i] = true;
	queen(1,sum);
	
	cout <<sum;

	return 0;
}

//作用：对第k列到最后一列的皇后完成放置
//用法：queen(k,sum)
void queen(int k,int &sum)
{
	int i,j;

	for ( i=1; i<=8; ++i )
	{
		if ( row[i] && digLeft[k+i-1] && digRight[8+k-i] )
		{
			col[k] = i;
			row[i] = digLeft[k+i-1] = digRight[8+k-i] = false;
			if ( k==8 ){
				++sum;
			}
			else queen(k+1,sum);
			row[i] = digLeft[k+i-1] = digRight[8+k-i] = true;
		}
	}
}

```

```c++
//八皇后问题的另一种精简写法
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int sum = 0;
vector<int> v(8, -1);

bool place(int k, int i)
{
    for (int j = 0; j < k; ++j){
        if (v[j] == i ||
            abs(j - k) == abs(v[j] - i))
            return false;
    }

    return true;
}

void nQueens(int k, int n)
{

    for (int i = 0; i < n; ++i){
        if (place(k, i)){
            v[k] = i;
            if (k == n - 1){
                ++sum;
                return;
            }
            else nQueens(k+1, n);
        }
    }
}

int main()
{
    nQueens(0, 8);

    cout << sum << endl;
    
    return 0;
}
```

和上面程序的主要区别在于，我们不用去考虑棋盘如何表示（即是否选用二维数组），考虑是否在同一对角线上，则或者“行数-列数”的值相同（主对角线平行方向），或者“行数 + 列数”的值相同（副对角线平行方向）。

如果不想把`sum`和`vector`变成全局变量，不妨加一个驱动程序。

```c++
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


//int sum = 0;

bool place(int k, int i, vector<int> &v)
{
    for (int j = 0; j < k; ++j){
        if (v[j] == i || abs(j - k) == abs(v[j] - i))
            return false;
    }

    return true;
}

void nQueens(int k, int n, int &sum, vector<int> &v)
{
    for (int i = 0; i < n; ++i){
        if (place(k, i, v)){
            v[k] = i;
            if (k == n - 1){
                ++sum;
                return;
            }
            else nQueens(k + 1, n, sum, v);
        }
    }
}

int nQueens(int k, int i)
{
    int sum = 0;  
    vector<int> v(8, -1);
    nQueens(k, i, sum, v);
    
    return sum;
}

int main()
{
    int n = 8;
    int s = nQueens(0, n);

    cout << s << endl;

    return 0;
}
```



```c++
//教材P131 快速排序——基于分治法
#include<iostream>
using namespace std;

void quicksort(int a[],int low,int high);
int divide(int a[],int low,int high);

int main()
{
	int i;
	int a[] = {5,7,3,0,4,2,1,9,6,8};
	quicksort(a,0,9);

	for ( i=0; i<10; ++i ) cout << a[i] << '\t';

	return 0;
}

//作用：将数组a中从low到high之间的元素从低到高排序
//用法：quicksort(a,0,n-1)
void quicksort(int a[],int low,int high)
{
	int mid;

	if (low>=high) return;
	mid = divide(a,low,high);
	quicksort(a,low,mid-1);
	quicksort(a,mid+1,high);
}

/*
作用：分段函数将数组分成两段，小于a[0]的放在前一半，大于a[0]的放在后一半，a[0]放中间，返回中间元素的下标
*/
//用法：divide(a,0,n-1)
int divide(int a[],int low,int high)
{
	int k=a[low];

	do{
		while( low < high && a[high] >=k ) --high;
		if (low<high){ a[low] = a[high];++low;}
		while( low<high && a[low] <= k) ++low;
		if (low<high){ a[high] = a[low];--high;}
	}while( low != high );
	a[low] = k;

	return low;
}
```

```c++
//教材P132 最长连续子序列和——基于分治法
#include <iostream>
using namespace std;

int maxSum(int a[],int left,int right);
int maxNum(int a,int b,int c);

int main()
{
	int a[] = {-2,11,-4,13,-5,2};
	int serious;

	serious = maxSum(a,0,5); 

	cout << serious << endl;

	return 0;
}

//作用：找出数组a从下标left到right的最长连续子序列和
//用法：max = maxSum(a,0,n-1)
int maxSum(int a[],int left,int right)
{
	int center;
	int leftSum,rightSum;
	int leftTol=0,rightTol=0;
	int leftTmp=-1,rightTmp=-1;
	int i;

	if ( left>=right ) return a[left] > 0 ? a[left] : 0;
	else center = (left+right) / 2;
	leftSum = maxSum(a,left,center); //计算左半部的最大子序列
	rightSum = maxSum(a,center+1,right); //计算右半部的最大子序列
	for(i=center;i>=left;--i)
	{
		leftTol += a[i];
		if ( leftTol > leftTmp ) leftTmp = leftTol;
	}
	for(i=center+1;i<=right;++i)
	{
		rightTol += a[i];
		if ( rightTol > rightTmp ) rightTmp = rightTol;
	}

	return maxNum(leftSum,rightSum,rightTmp+leftTmp);
}

//作用：找出a,b,b三个数中的最大值
//用法：maxNum(a,b,c)
int maxNum(int a,int b,int c)
{
	int tmp = a;
	if ( b > tmp ) tmp = b;
	if ( c > tmp ) tmp = c;

	return tmp;
}

/*
解析：
最长连续子序列和的问题用分治法求解可分为三种情况：1.最长子序列位于前半部分；2.最长子序列位于后半部分；3.最长子序列从前半部分开始，后半部分结束。函数maxSum就是根据此思路来写的
*/
```



**硬币找零问题**：如果有面值为1，5，10，21，25分的硬币，数量无限多，为了找出63分零钱所需的最少硬币数。

分析：此问题和***贪婪法***中的找硬币问题题型类似，但是思路不同，贪婪法中硬币是1，5，10，20，50，和人民币的面值是吻合的，因为经过特殊设计，所以可以用贪婪法。但是本题因为如果采用贪婪法，则需要25分的2个，10分的1个，1分的3个，总共6个硬币，实际只需要3个21分硬币即可。为了避免重复重复计算，可以定义一个数组coinUsed[]，coinUsed[i]表示零钱数为i的时候所需的最少硬币，用数组coins[]来存储硬币对应的币值，这样从零钱1开始，逐渐增加，把零钱数i分解成coins[j]和coinUsed[i-coins[j]]，coinUsed[i-coins[j]]因为小于i，所以结果已经有了，在所有的分解情况中选择一个硬币数最少的存入到coinUsed[i]，所以当零钱数为63的时候，只需要访问coinUsed[63]就是答案。

```c++
//教材P135 硬币找零——基于动态规划
#include <iostream>
using namespace std;

void makechange(int coins[],int change,int size,int coinUsed[]);

int main()
{
	int coins[] = {1,5,10,21,25};
	int coinUsed[64] = {0};

	makechange(coins,63,5,coinUsed);
	
	cout << coinUsed[63] << endl;

	return 0;
}

/*
作用：change为零钱数，size是所给出硬币选择的种数，coinUsed[i]表示零钱为i时所需的最少硬币数
用法：makechange(coins,63,5,coinUsed)
 */
void makechange(int coins[],int change,int size,int coinUsed[])
{
	for (int cents=1; cents<=change; ++cents)
	{
		int minChange = cents; //零钱都用1分来找
		for (int j=0;j<size;++j) //尝试所有的硬币
		{
			if (coins[j]>cents) continue; //分解成coins[j]和cents-coins[j]
			if ( coinUsed[cents-coins[j]]+1 < minChange ) minChange = coinUsed[cents-coins[j]]+1;
		}
		coinUsed[cents] = minChange; //记录零钱数为cents时所需的最少硬币
	}
}
```



判断一个数是否是素数：一种方法是逐一检验从2-n-1，但是效率太差，实际上只需要检验到$$\sqrt{n}$$，因为加入a是一个因子，则$$\frac{n}{a}$$也是一个因子，最大为$$\sqrt{n}$$，必然是一个偏大一个偏小，只需要检验小的部分即可。这样时间复杂度为$$O(n)$$

```c++
//程序设计题1
//问题描述：判断一个数是否是素数
#include<iostream>
using namespace std;

bool prime(int n);

int main()
{
	int n;
	bool flag;

	cout << "请输入n：";
	cin >> n;

	flag = prime(n);

	cout << flag << endl;

	return 0;
}

bool prime(int n)
{
	#include <cmath>

	int i,limit;

	if (n <= 1) return false;
	if (n == 2) return true;
	if (n % 2 == 0) return false;
	limit = sqrt(n) + 1;
	for (i = 3; i <= limit; i += 2)
		if (n%i == 0) return false;

	return true;
}
```

```c++
//程序设计题5
//问题描述：求两个正整数的最大公约数
#include <iostream>
using namespace std;

int main()
{
	int x=1000005,y=1000000,r;
	int tmp;

	if (x>y) //x为较小的数，y为较大的数
	{
		tmp = x;
		x = y;
		y= tmp;
	}

	r = y % x;
	while(r != 0)
	{
		y = x;
		x = r;
		r = y % x;
	}

	cout << "最大公因数为：" << x << endl;

	return 0;
}

/*
解析：
以上为自己写的欧几里得算法，和书中所给答案略有不同。书中默认了x为两个数中较大者。欧几里得辗转相除法的思路是（默认x为两个数中较大者）：
1. 取x除以y的余数为r
2. 如果r=0，则最大公因数就是y
3. r != 0，则令x=y,y=r，重复上述过程
求解最大公因数还有其他方法，如：质因数分解法、短除法、更相减损术
*/
```

```c++
//程序设计题11
//问题描述：输出第N大的数——冒泡排序的办法
#include <iostream>
using namespace std;

void BubbleSort(int a[],int size,int n)
{
	int i,j,tmp;
	bool flag;

	for (i=1;i<=size-n-1;++i)
	{
		flag = false;
		for(j=0;j<size-i;++j)
		{
			if (a[j+1]>a[j])
			{
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
				flag = true;
			}
			if (!flag) break;
		}
	}

	cout << a[size-n];
}

int main()
{
	int array[] = {9,8,7,6,5,4,3,2,1};

	BubbleSort(array,9,4);

	return 0;
}
//也可以用选择排序，第n次的时候即第N大的数
```

```c++
//程序设计题16
//逆序打印整形参数，如输入12345，输出54321
#include <iostream>
using namespace std;

void reverse(int num)
{
	if (num < 10) cout << num;
	else {
		cout << num % 10;
		reverse(num/10); 
	}	
}

int main()
{
	int a=12345;

	reverse(a);

	return 0;
}

//也可以不用递归实现，直接用while循环即可
```



## 第七章 间接访问——指针

用指针访问数组，如果定义了`int array[5]`，则array代表一个数组，但是也可以直接用作指针，`array`等同于`&array[0]`。所以访问数组的方式有以下五种：

```c++
#include <iostream>
using namespace std;
 
int main()
{
	int array[] = {1,2,3,4,5};
	int *p,i;

	for(i=0;i<5;++i) cout << array[i] << ' ';
	cout << endl;

	for(i=0;i<5;++i) cout << *(array+i) << ' ';
	cout << endl;

	for(p=array;p<array+5;++p) cout << *p << ' ';
	cout << endl;

	for(p=array,i=0;i<5;++i) cout << p[i] << ' ';
	cout << endl;

	for(p=array,i=0;i<5;++i) cout << *(p+i) << ' ';
	cout << endl;

	return 0;
}
```



数组名作为形式参数的时候，比如有一个排序函数`void sort(int a[],int n)`是对数组a[]进行排序，数组中有n个元素，如果`n=10`，则对前5个元素排序是`sort(a,5)`，对后五个元素排序是`sort(a+5,5)`，使程序更加灵活。比如***设计一个函数用分治法在一个整形数组中找出最大值和最小值***。因为函数要返回最大值和最小值，而return语句只能有一个返回值，所以可以定义两个变量`min max`，把他们的地址传给函数，函数中把结果存入到指定的地址，程序如下。

```c++
#include <iostream>
using namespace std;

void minAndMax(int a[],int n,int *minimum,int *maximum)
{
	int min1,min2,max1,max2;

	switch(n)
	{
		case 1: *minimum = *maximum = a[0];return;
		case 2: if(a[0] < a[1]) {*minimum = a[0]; *maximum = a[1];}
				else {*minimum = a[1]; *maximum = a[0];}
				return;
		default: minAndMax(a,n/2,&min1,&max1); //找出前一半的最小值和最大值
				 minAndMax(a+n/2,n-n/2,&min2,&max2); //找出后一半的最小值和最大值
				 if(min1 < min2) *minimum = min1; else *minimum = min2;
				 if(max1 < max2) *maximum = max2; else *maximum = max1;
				 return;
	}
}

int main()
{
	int a[] = {1,2,3,4,5,6,7,8,9};
	int min,max;

	minAndMax(a,9,&min,&max);
	cout << min << '\t' << max;

	return 0;
}
//这里只需要注意程序15行的n-n/2，不能写成n/2，比如n为奇数的时候会漏掉元素
```

```c++
//教材P157
//问题描述：编写一个统计字符串中单词个数的函数
#include <iostream>
using namespace std;

int count(const char *s)
{
	int cnt=0;

	while(*s != '\0')
	{
		while(*s == ' ') ++s; //跳过空白
		if ( *s != '\0')
		{
			++cnt; //找到一个单词
			while(*s != ' ' && *s != '\0') ++s;
		}
	}

	return cnt;
}

int main()
{
	char ch[]="     today is Monday";
	int a;

	 a = count(ch);
	
	cout << a << endl;

	return 0;
}
```

**返回指针的函数：设计一个函数从一个字符串取出一个子串。**

函数的设计需要三个参数，从哪个字符串中取出子串，从字符串的哪里开始，哪里结束。字符串可以用一个指向字符的指针表示，起点和终点是整数。当函数的返回值是针织的时候，返回地址对应的变量可以是全局变量或者动态变量，但不能是被调函数的局部变量。由于函数中有一个动态变量，所以需要手动释放。

```c++
#include <iostream>
#include <cstring>
using namespace std;

char *subString(char *s,int start,int end)
{
	char *sub = new char[end-start+2]; //字符串以'\0'结尾
	strncpy(sub,s+start,end-start+1); //返回值是sub的起始地址
	sub[end-start+1] = '\0';

	return sub;
}

int main()
{
	char ch[]="Hello world!";
	char *p;

	p = subString(ch,6,10);

	delete [] p;

	return 0;
}
```

定义和使用引用类型的变量时，需要注意几点：

1. 定义和使用引用类型的变量时，必须在变量名前加上`&`，以示和普通变量的区别；
2. 定义和使用引用类型的变量时，必须立即对它初始化
3. 引用的初始值可以时一个变量也可以是另一个引用，如`int i; int &j1 =i; int &j2 = j1;`



**引用类型作为函数的参数**：
回顾指针作为函数参数的一个程序：

```c++
void swap(int *a,int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
```

但是每次使用变量的时候都要在指针变量前加上`*`，显得很麻烦，使用引用办法的程序是：

```c++
void swap(int &a,int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}
```

**返回引用的函数**：

```c++
#include <iostream>
using namespace std;

int &index(int a[],int i)
{
	return a[i];
}

int main()
{
	int a[] = {1,2,3,4,5};
	
	cout << index(a,2) << endl;
	
	return 0;
}
```

上述程序中，函数`index`采用了引用返回，可以作为左值，其实还可以把数组a定义为全局变量，这样函数`index`就可以直接返回`return a[i]`，使用返回引用的函数时需要注意几个问题：

1. 定义返回引用的函数，不能返回函数的局部变量；
2. 返回引用值的函数，返回的值也不可以是一个表达式，因为表达式不是左值而是一个临时值
3. 返回引用值的函数返回值可以是程序的全局变量或者动态变量。

**指针数组与多级指针**：

指针数组最常用的是存储一组字符串，比如“*写一个函数用二分法查找某一个城市名在城市表中是否出现，要求用递归实现*”

```c++
//教材P162
//二分查找的递归实现
#include <iostream>
#include <cstring>
using namespace std;

int binarySearch(char *city[],int lh,int rh,char *cityName)
{
	int mid,result; //mid：中间元素下标，result：中间元素和cityName的比较值

	if(lh<=rh)
	{
		mid = (lh + rh) / 2;
		result = strcmp(city[mid],cityName);
		if(result == 0) return mid;
		else if (result > 0) return binarySearch(city,lh,mid-1,cityName);
		else return binarySearch(city,mid+1,rh,cityName);
	}

	return -1; //没有找到
}

int main()
{
	char *city[8]={"Atlanta","Boston","Chicago","Denver","Deroit","Houston","Los Angle","Miami"};
	char name[] = "Chicago";
	int position;

	position = binarySearch(city,0,7,name);
	cout << position << endl;

	return 0;
}

/*
解析：
这个程序最初犯的错误是在16、17行忘记加return了，这样返回值一直是-1，分析一下原因是即使确实找到了cityName，这样返回是mid，赋值给position，但是回溯的时候，执行的binarySearch继续执行下去需要一个return结束，则返回-1，赋值给position，所以一直输出是-1。验证这种思路的办法是，如果一次就找到，则就返回是mid而不是-1，所以可以先删掉16、17行的return，然后把26行的改为Denver，因为lh=0，rh=7，mid=3是Denver，这样修改后运行返回就是3，除了这种特殊情况以外，返回全是-1。
*/
```

**main函数的参数**：

main函数也有两个形式参数：第一个形式参数习惯上称为`argc`，是一个整型参数，他的值是运行程序时命令行中参数个数；第二个形式参数习惯上称为`argv`，是一个指向字符的指针数组，它的每个元素是指向一个实际参数的指针，如下：

```c++
#include <iostream>
using namespace std;

int main(int argc,char *argv[])
{
	int i;

	cout << "argc=" << argc << endl;
	for(i=0;i<argc;++i)
		cout << "argc[" << i << "]=" << argv[i] << endl;
	
	return 0;
}
//命令行中输入参数this is my program
```

和教材区别的一点是，教材中输出的`argv[0]`是第一个`this`，但是运行时输出的却是程序的路径。在调试程序的时候有两种方式：

1. 在VS2017里的`调试 -> 属性`里，在`调试`的`命令行参数`里面键入即可，这时输出的`argv[0]`是生成的`exe`文件所在的路径。
2. 在Developer Command Prompt for VS 2017里调试，我的在F盘，直接键入`F：`路径定位到`F:\ConsoleApplication1\x64\Debug`，然后键入`ConsoleApplication1.exe this is my program`，输出的`argv[0]`则变成了`ConsoleApplication1.exe`

现在存在的问题是==如何让argv[0]的输出变为输入的第一个参数==



编写一个求任意n个正整数的平均数的程序，它的n个数作为命令行的参数。如果该程序对应的可执行文件名为aveg，命令行中输入aveg 10 30 50 20，对应输出30.

```c++
#include <iostream>
using namespace std;

int convertStringToInt(char *);

int main(int argc,char *argv[])
{
	int i,sum=0;

	for(i=1;i<=argc;++i)
		sum += convertStringToInt(argv[i]);

	cout << sum / (argc-1) << endl;
	
	return 0;
}

int convertStringToInt(char *s)
{
	int num = 0;

	while(*s){
		num = num * 10 + *s - '0';
		++s;
	}

	return num;
}
/*
解析：
可以通过argc来得到输入了多少个数据，注意argv[i]是输入的字符串，所以幼定义一个函数来实现转换成数字。
*/
```

**多级指针**：

如定义`char *string[10]`，数组名string本身可以看成一个指针，而数组中的元素本身又是一个指针，所以string本身指向了一个存储指针的单元，称为指向指针的指针。所以通过指向指针的指针访问数组：

```c++
#include <iostream>
using namespace std;

int main()
{
	const char *city[]={"aaa","bbb","ccc","ddd"};
    const char **p;
    
    for(p=city;p<city+4;++p) cout << *p << endl;
    
    return 0;
}
```

这里和书中有一些区别在第6、7行，源程序是没有加上const的，所以回顾一下**指针与常量限定符const**：

为了防止通过指针随意修改变量的值，可以采用const来限制通过指针修改它指向地址中的内容：

1. **指向常量的指针**：是一个指向内容为常量的指针变量。例如定义了`const int *p = &x;`，所以如果出现`*p = 30`则编译器会报错，但是执行`p = &y`是可行的
2. **常指针**：指针本身是个常量，它固定指向某一变量，因此本身的值是不能变的，但是指向的地址是可以变得。通常定义`int * const p = &x;`，执行`*p = 20`可行，但是执行`p = &y`则会报错。
3. **指向常量的常指针**：指针本身不能变，指向的地址的值也不能变。通常定义为`const int * const p = &x;`

此外参照此篇博客（https://blog.csdn.net/takejian/article/details/79751399），比较特殊的是字符串数组，如`const char *ch = 123`，这里指针指向常量字符串123，123的内容不能改变，但是可以改变ch的指向地址，`ch = "Hello"`是可行的，因为这里字符数组名`ch`相当于指向字符数组首字母的指针，存储的是首字符的起始地址，后面相当于指向了`Hello`起始字符的地址，这样也可以写为`char const *ch `，但是如果const出现在*的后面则情况不同。如

```c++
char c[] = "123"
char * const ch = c;
ch[0] ='4'//此时c为“423”
```

这时ch指向的是字符数组的起始地址不能改变，但是可以改变其指向的数值



**多维数组和指向数组的指针**：
一个二维数组如：

`int a[3][4] = {1,2,3,4,5,6,7,8,9,10,11,12}` ，每一行可以通过a[0],a[1],a[2]来访问，每个a[i]是一个由4个元素组成的一维数组，所以***a[i]可以看成一维数组的数组名***，数组名a指向由3行组成的一维数组的第0个元素，所以***a被称为指向一维数组的指针，相当于指向指针的指针***。二维数组的访问通过指针来实现：

```c++
#include <iostream>
using namespace std;

int main()
{
	int a[3][4] = {1,2,3,4,5,6,7,8,9,10,11,12};
	int (*p)[4],*q;

    for(p=a;p<a+3;++p) //p指向每一行
    {
        for(q=*p;q<*p+4;++q)
        {
            cout << *q << '\t';
        }
        cout << endl;
    }
    
    return 0;
}
```

已知可以动态申请一维数组，但是C++不支持动态申请二维数组，所以思路是先定义一个指向指针的指针，然后申请指向每一行首地址的指针，最后为每一行申请空间：

```c++
#include <iostream>
using namespace std;

int  main()
{
    int **a,i,j,k=1;
    
    a = new int *[3]; //申请指向每一行首地址的指针
    for(i=0;i<3;++i)
    {
        a[i] = new int[4];
    }
    
    for(i=0;i<3;++i) //为数组元素赋值
    {
        for(j=0;j<4;++j)
        {
            a[i][j] = k++;
        }
    }
    
    for(i=0;i<3;++i) //数组元素的输出
    {
        for(j=0;j<4;++j)
        {
            cout << a[i][j] << '\t';
        }
        cout << endl;
    }
    
    for(i=0;i<3;++i)
        delete [] a[i]; //释放每一行
    delete [] a; //释放保存每一行首地址指针的数组
    
    return 0;
}
```

**指向函数的指针**：

```c++
//通用快速排序函数的实现
#include <iostream>
#include <cstring>
using namespace std;

template <class T>
int divide(T data[],int low,int high,int (*comp)(T,T))
{
	T k = data[low];

	do{
		while(low < high && comp(data[high],k)>0) --high;
		if(low < high){data[low] = data[high]; ++low;}
		while(low < high && comp(k,data[low])>0) ++low;
		if(low < high) {data[high] = data[low]; --high;}
	} while (low != high);
	data[low] = k;

	return low;
}

template <class T>
void quickSort(T data[],int low,int high,int (*comp)(T,T))
{
	int mid = (low + high) / 2;

	if(low >= high) return; //数组只有一个或零个数，直接返回
	mid = divide(data,low,high,comp); //low作为基准元素，划分数组，返回中间元素的下标
	quickSort(data,low,mid-1,comp); //左一半排序
	quickSort(data,mid+1,high,comp); //右一半排序
}

//对于整型数的排序
int intcmp(int a,int b)
{
	if(a == b) return 0;
	if(a < b) return -1;else return 1;
}

int main()
{
	const char *a[]={"ddd","aaa","ccc","bbb"};
	const char **p;

	quickSort(a,0,3,strcmp);

	for(p=a;p<a+4;++p) cout << *p << '\t';
	cout << endl;

	int b[]={7,9,4,3,8,1,2,5,6,0};
	
	quickSort(b,0,9,intcmp);

	for(int i=0;i<10;++i) cout << b[i] << '\t';

	return 0;
}
```

简答题6：值传递、指针传递和引用传递的区别。

**值传递**：主要作用是作为函数的输入，值传递时计算机为形式参数分配空间，将实际参数作为形式参数的初值，函数中对形式参数的修改不会影响到实际参数的值。

**引用传递**：形式参数是实际参数的别名，形式参数没有自己的空间，它操作的是实际参数的空间。

**指针传递**：形式参数是一个指针变量，参数传递时，计算机为形式参数分配一块空间来保存一个内存地址所需的空间，将实际参数的值作为初值。

程序设计题1：用原型`void getDate(int &dd,int &mm,int &yy);`，写一个函数从键盘读入一个形如dd-mm-yy的日期，其中dd是一个1位或者2位的表示日的整数，mm是月份的三个英文字母的缩写，yy是两位数的年份。

```c++
#include <iostream>
#include <cstring>
using namespace std;

int main()
{
	
	char *month[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	char ch[10];
	int i;

	dd = mm = yy = 0;

	cout << "请输入日期：";
	cin >> ch;

	//如果输入是8位，则最高位为0，需要补位
	if(ch[1] == '-'){
		for(i=9;i>0;--i){
			ch[i] = ch[i-1];
			ch[0] = '0';
		}
	}

	//处理月份
	for(mm=0;mm<12;++mm) if(strncmp(&ch[3],ch[mm],3) == 0) break;
	++mm;

	return 0;
}
```

上面的程序其实并不完善，只是把比较关键的点写出来（偷了懒），是为了注意对于最高位的补位操作和处理月份的技巧。

```c++
//程序设计题3
/*
问题描述：设计一个函数char *itos(int n)，将整型数n转换成一个字符串
*/
#include <iostream>
using namespace std;

char *itos(int n)
{
	int i=10,j;
	int num = 1;

	while(i<n){i *= 10;++num;}

	char *p = new char[num+1];
	for(j=0;j<num;++j){
		i /= 10;
		p[j] = static_cast<char>(n/i+'0');
		n %= i;
	}
	p[num] = '\0';

	return p;
}

int main()
{
	char *point;
	int i=0;

	point = itos(95);

	while(point[i] != '\0'){
		cout << point[i];
		++i;
	}
	delete [] point;

	return 0;
}
/*
解析：
主要思路是由于不确定输入的数字是多少位，所以先用i来判断数字的大小（和第四章课后踢将一个四位数从高位向低位输出很类似），num记录数字的位数，动态申请的数组可以用参数来控制数组大小，并要记得防内存泄漏要归还空间。
*/
```

从string类型转为int，float，double类型的方式：

**方法一： 使用stringstream**

```c++
#include <iostream>  
#include <sstream>    //使用stringstream需要引入这个头文件  
using namespace std;  
  
//模板函数：将string类型变量转换为常用的数值类型（此方法具有普遍适用性）  
template <class Type>  
Type stringToNum(const string& str)  
{  
    istringstream iss(str);  
    Type num;  
    iss >> num;  
    return num;      
}  
  
int main(int argc, char* argv[])  
{  
    string str("00801");  
    cout << stringToNum<int>(str) << endl;  
  
    system("pause");  
    return 0;  
}  
```

**方法二：使用atoi()、 atil() 、atof()函数  -----------------实际上是char类型向数值类型的转换**

**注意**：使用 atoi 的话，如果 string s 为空，返回值为0.则无法判断s是0还是空

**1. atoi():      int atoi ( const char \* str );**

**说明：**Parses the C string *str* interpreting its content as an integral number, which is returned as an `int` value.

**参数：str** ： C string beginning with the representation of an integral number.

**返回值：1.** 成功转换显示一个Int类型的值.  **2.** 不可转换的字符串返回0.  **3.**如果转换后缓冲区溢出,返回 `INT_MAX` or`INT_MIN`

```c++
#include <iostream>  
using namespace std;  
int main ()  
{  
    int i;  
    char szInput [256];  
    cout<<"Enter a number: "<<endl;  
    fgets ( szInput, 256, stdin );  
    i = atoi (szInput);  
    cout<<"The value entered is :"<<szInput<<endl;  
    cout<<" The number convert is:"<<i<<endl;  
    return 0;  
}  
```

**2.aotl():  long int atol ( const char \* str );**

**说明：**C string *str* interpreting its content as an integral number, which is returned as a `long int` value（用法和atoi函数类似，返回值为long int）

**3.atof():  double atof ( const char \* str );**

**参数：**C string beginning with the representation of a floating-point number.

**返回值：**1. 转换成功返回doublel类型的值 2.不能转换，返回0.0。  3.越界，返回`HUGE_VAL`

```c++
/* atof example: sine calculator */  
#include <stdio.h>  
#include <stdlib.h>  
#include <math.h>  
int main ()  
{  
  double n,m;  
  double pi=3.1415926535;  
  char szInput [256];  
  printf ( "Enter degrees: " );  
  gets ( szInput );  
  //char类型转换为double类型   
  n = atof ( szInput );  
  m = sin (n*pi/180);  
  printf ( "The sine of %f degrees is %f\n" , n, m );  
    
  return 0;  
}  
```



程序设计题6：Julian历法是用年及这一年中的第几天来表示日期。设计一个函数将Julian历法表示的日期转换成月和日，如Mar 8（注意闰年的影响）。函数返回一个字符串，即转换后的月和日。

```c++
#include <iostream>
#include <cstring>
using namespace std;

char *Julian(int year,int day)
{
	char *date = new char[7];
	char *month[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	int dayNum[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	int i=0;

	if(year % 400 == 0 || (year % 4 ==0 && year % 100 != 0)) ++dayNum[1];
	while(day > dayNum[i]){
		day -= dayNum[i];
		++i;
	}
	strcpy(date,month[i]);
	date[3] = ' ';
	if(day > 9){
		date[4] = static_cast<char>(day / 10 + '0');
		date[5] = static_cast<char>(day % 10 + '0');
	}
	else{
		date[4] = static_cast<char>(day + '0');
	}
	date[6] = '\0';

	return date;
}

int main()
{
	char *p;
	int i=0;

	p = Julian(1995,200);

	while(p[i] != '\0'){
		cout << p[i];
		++i;
	}

	delete [] p;

	return 0;
}
```

#第八章 数据封装——结构体

```c++
//单链表的建立与访问
#include <iostream>
using namespace std;

struct linkRec {
	int data;
	linkRec *next;
};

int main()
{
	linkRec *p, *head, *rear;
	int x;

	head = rear = new linkRec;

	while (true) {
		cin >> x;
		if (x == 0) break;
		p = new linkRec;
		p->data = x;
		rear->next = p;
		rear = p;
	}

	rear->next = NULL;

	cout << "链表的内容是:" << endl;
	p = head->next;
	while (p->data != NULL) {
		cout << p->data << '\t';
		p = p->next;
	}
	cout << endl;

	return 0;
}
```

**约瑟夫环问题**：n个人围成一圈，从第一个人开始报数1，2，3，凡是报到3的人被淘汰。找出最后留在圈子中的人的序号。如果将n个人用0 ——n-1编号，当n=5时，最后剩下的人的编号是3。

分析：n个人围成一圈相当于一个环，单链表实现的时候尾节点不再指向为NULL，而是指向编号为0。单循环链表里不需要头节点。淘汰人的过程本质就是删除节点的过程。

```c++
//求解约瑟夫环的问题
#include <iostream>
using namespace std;

struct node {
	int data;
	node *next;
};

int main()
{
	int i = 0, n = 5;
	node *head, *p, *q;

	head = p = new node;
	p->data = 0;
	for (i = 1; i<n; ++i) {
		q = new node;
		q->data = i;
		p->next = q;
		p = q;
	}
	p->next = head; //尾节点指向头节点形成环

	cout << "删掉的节点有：" << endl;
	q = head; //报数为1
	while (q->next != q) {
		p = q->next; //报数为2
		q = p->next; //报数为3，需要删掉
		p->next = q->next; //绕过节点q
		cout << q->data << '\t';
		delete q;
		q = p->next; //继续报数为1
	}
	cout << endl;
	cout << "留下的节点序号为：" << q->data;

	return 0;
}
```

## 第九章 模块化开发

### 9.1 自顶向下分解

处理大程序的最重要技术就是逐步细化策略：当遇到一个较大的、复杂的问题时，可以把问题分解为容易解决的几个小部分，然后解决每一个小部分。

逐步细化的实现工具就是函数，将一个问题划分为可管理的分块的过程称为**分解**。

当面临编写程序任务时，最好的策略就是从主程序开始，将大问题分解小问题，这个过程持续到每个程序片段都简单到可以独立解决为止，这个过程称为**自顶向下分解**或**逐步细化**。

### 9.2 模块划分

把大问题分解为小问题在程序设计的很多阶段都会用到，但是程序很复杂时或者由很多函数组成的时候，要在一个源文件中处理如此众多的函数会变得困难。最好的办法就是把程序分成几个小的源文件。由整个程序的一部分组成的较小的源文件称为**模块**。

### 第9章 简答题

3.为什么库的实现文件要包含自己的头文件？

```
保证实现文件中的原型和提供给用户程序用的函数原型完全一致。
```

4.为什么头文件要包含`#ifndef... #endif` 这对预编译指令？

```
这对编译指令表示#ifndef后的标识符已经定义过，则跳过中间所有指令，直到#endif。一个程序可能有很多源文件组成，每个源文件都需要包含库的头文件，如果没有这对指令，则头文件内容可能出现很多遍，造成编译或链接错误。这对指令保证头文件的内容在整个程序只出现一次。
```

5.什么是模块的内部状态？内部状态是怎样保存的？

```
模块的内部状态就是模块内多个函数需要共享的信息，这些信息与其他模块中的函数无关。
内部状态通常表示为源文件中的全局变量，以方便模块中的函数共享。
```

6.为什么要用库？

```
库可以实现代码重用。
```

### 第9章 程序设计题

1.哥德巴赫猜想指出：任何一个大于6的偶数都可以表示成两个素数的和，编写程序列出指定范围内的所有偶数的分解。

```c++
#include <iostream>
#include <set>

using namespace std;

//埃拉托色尼筛选法
//返回n以内的所有素数的集合
set<int> EratosiniScreen(int n)
{
	set<int> primeSet;

	for (int i = 2; i <= n; ++i) primeSet.insert(i);

	for (int m = 2; m * m <= n; ++m){
		if (primeSet.find(m) != primeSet.end()){
            int i = 2 * m;
            while (i <= n){
                primeSet.erase(i);
                i += m;
            }
        }    
	}

	return primeSet;
}

//哥德巴赫猜想分解
void GoldbachDecomposition(int num)
{
	set<int> primeSet = EratosiniScreen(num);
	auto iter = primeSet.begin();
	while (iter != primeSet.end()){
		int tmp = num - *iter;
		if (primeSet.find(tmp) == primeSet.end())
			++iter;
		else{
			cout << *iter << " + " << tmp << endl;
			break;
		}
	}
}

int main()
{
	int left=0, right=20; //指定的范围边界

	if (right <= 7)
		cout << "Range input error" << endl;
    
    if (left % 2 != 0) ++left;
        
	for (int i = max(8, left); i <= right; i += 2){
	    cout << i << " = ";
		GoldbachDecomposition(i);
	}

	return 0;
}
```

```shell
# run result
8 = 3 + 5
10 = 3 + 7
12 = 5 + 7
14 = 3 + 11
16 = 3 + 13
18 = 5 + 13
20 = 3 + 17
```

解析：列出指定范围内的偶数分解，所以需要两个int类型来表示左右边界，判断一个数是不是素数我们可以通过之前写过的埃拉托色尼筛选法来实现，这里我们设计函数`EratosiniScreen`来返回一个包含指定范围内的所有素数，然后利用`find`操作来实现分解，最后就是对于左右边界的判断，因为右边界 <= 7都是不存在偶数的分解的，左边界在确定初始条件时，通过`max(8, left)`来判断。

这种写法存在的问题是每一次都需要调用一次函数`EratosiniScreen`，但是范围内的素数是可以被重复利用的，所以改进的版本是：

```c++
#include <iostream>
#include <set>

using namespace std;

//哥德巴赫分解
void GoldbachDecomposition(int left, int right)
{
	//检查边界条件
	if (right <= 6){
		cout << "Range input error" << endl;
		return;
	}
		 
    if (left % 2 != 0) ++left;

    //得到素数集
	set<int> primeSet;
	
    //素数分解中不可能出现2，所以素数集从3开始
	for (int i = 3; i <= right; ++i) primeSet.insert(i);

	for (int m = 3; m * m <= right; ++m){
		if (primeSet.find(m) != primeSet.end()){
            int i = 2 * m;
            while (i <= right){
                primeSet.erase(i);
                i += m;
            }
        }    
	}

	//在素数集中查找分解
	for (int i = max(8, left); i <= right; i += 2){
		auto iter = primeSet.begin();
		while (iter != primeSet.end()){
			int tmp = i - *iter;
			if (primeSet.find(tmp) == primeSet.end())
				++iter;
			else{
				cout << i << " = "<< *iter << "+" << tmp << endl;
				break;
			}
		}
	}
}

int main()
{
	int left=0, right=20; //指定的范围边界
	GoldbachDecomposition(left, right);

	return 0;
}
```

```shell
# run result
8 = 3 + 5
10 = 3 + 7
12 = 5 + 7
14 = 3 + 11
16 = 3 + 13
18 = 5 + 13
20 = 3 + 17
```

这个版本和上面不同的是把得到素数集和分解过程合并了，实现了素数集的重用，并且改善了参数条件。参考答案的思路是实现一个辅助函数来判断某个数字是否是素数，然后利用双循环，最内层中判断初始数值是否是素数。这种思路的缺点是每一次判断素数的时候都是从3开始试探，然后是+2。这样每次循环时候，很多数值都是不需要测验的，也就是浪费掉了很多已知信息。所以先创造一个素数集，然后在素数集中查找就方便很多。





## 第十章 创建工具——类的定义与使用

面向对象程序设计特点：

* 代码重用
* 实现隐藏：类的使用者不需要知道工具是如何实现的，只需要知道如何使用这些工具就可以了

从C到C++迈出的第一步是允许将函数放入一个结构体，这一步是过程化到面向对象的变化。

**用构造函数、复制构造函数和析构函数检验对象的生命周期**：

```c++
//createAndDestroy类的定义与实现
#ifndef createAndDestroy_h
#define createAndDestroy_h

#include <iostream>
using namespace std;

class createAndDestroy {
private:
	int objectID;

public:
	createAndDestroy(int); //构造函数
	createAndDestroy(const createAndDestroy &obj); //复制构造函数
	~createAndDestroy(); //析构函数
};

createAndDestroy::createAndDestroy(int n)
{
	objectID = n;

	cout << "构造对象：" << objectID << endl;
}

createAndDestroy::createAndDestroy(const createAndDestroy &obj)
{
	objectID = obj.objectID;

	cout << "复制构造函数：" << objectID << endl;
}

createAndDestroy :: ~createAndDestroy()
{
	cout << "析构对象：" << objectID << endl;
}

#endif
```

```c++
//createAndDestroy类的对象验证变量的生命周期
#include "createAndDestroy.h"

createAndDestroy global(0);

void f()
{
	cout << "函数f：" << endl;
	static createAndDestroy obj1(1);
	createAndDestroy obj2(global);
	createAndDestroy obj3 = obj1;
}

int main()
{
	createAndDestroy obj4(4);

	f();
	f();

	return 0;
}
```

```
//输出结果
构造对象：0
构造对象：4
函数f：
构造对象：1
复制构造函数：0
复制构造函数：1
析构对象：1
析构对象：0
函数f：
复制构造函数：0
复制构造函数：1
析构对象：1
析构对象：0
析构对象：4
析构对象：1
析构对象：0
```

**验证对象作为函数参数和函数的返回值**









**常量对象与常量成员函数**

`cosnst Rational r1(1,3)`常量对象只能初始化，并且必须要初始化，否则无法指定常量的值。

c++中可以把一个函数定义为***常量成员函数***，它告诉编译器该成员函数是安全的，不会改变对象成员的数据值，可以被常量对象所调用。常量成员函数的定义是在函数头下面加一个保留字`const`，要说明一个函数是常量的，必须在类定义中的成员函数声明时声明它为常量，同时在成员函数定义时也要声明它时常量的。

```c++
class Rational
{
private:
	int num;
	int den;

	void ReductFraction();

public:
	Rational(int n = 0;int d = 1) { num = n; den = d; ReductFraction();}
	void display() const {cout << num << '/' << den;}
	~Rational();
};
```

例如上面，一旦将一个对象定义为常量，该对象允许调用 的成员函数只有`display`函数。

**常量数据成员**

```c++
class Test
{
private:
	const int size;

public:
	Test(int sz);
	~Test();
};

Test :: Test(int sz) : size(sz) {}
```

常量数据成员表示它在某个对象的生命周期内是常量，如上面例子的`size`，一旦对象生成，常量数据成员的值是不能改变的，所以常量数据成员的值只能在构造函数中设定，并且***只能在构造函数的初始化列表里完成***。

**静态数据成员与静态成员函数**

* 静态数据成员：拥有一块单独的存储区域，不管创建了多少个对象，这些对象的静态数据成员都共享这一块空间，实际上为这些对象提供了一种互相通信的机制。定义只需要在数据成员前加`static`。需要注意的是，类定义只是给出了对象构成的声明，真正的存储空间是在对象定义时分配的。但是静态数据成员属于类而不属于对象，因此系统为对象分配空间时并不包括静态数据成员的空间，所以***静态数据成员的空间必须单独分配***！
* 静态成员函数：用于操作静态数据成员，为类服务而不是对象服务。静态成员函数的声明自需要在类的定义中的函数原型前加上保留字`static`，静态成员函数的定义可以写在类定义中或者外面。在类外定义时，函数定义中不需要加上`static`。

<u>静态成员函数是为类服务的，最大特点就是没有`this`指针，因此静态成员函数不能访问一般的数据成员，只能访问静态数据成员或其他静态成员函数。</u>

**静态常量**

<u>静态常量和常量数据成员的区别是：常量数据成员属于各个对象，不同对象的常量数据成员的值是不同的；静态常量数据成员属于整个类，不同对象的常量数据成员的值是相同的。此外常量数据成员的初始化必须由构造函数的初始化列表来实现，但是静态常量数据成员的初始化可以直接赋值。</u>

## 第十一章 运算符重载

这里为了方便就未采用头文件+源文件的写法。

```c++
#include <iostream>
using namespace std;

class Rational
{
private:
	int num;
	int den;
	void ReductFraction();

public:
	Rational(int n = 0,int d = 1) {num = n; den = d; ReductFraction();}
	Rational operator+(const Rational &r1) const;
	Rational operator*(const Rational &r1) const;
	bool operator<(const Rational &r1) const;
	bool operator==(const Rational &r1) const;
	void display() const {cout << num << '/' << den;}
};

void Rational :: ReductFraction()
{
	int tmp = (num > den) ? den : num;

	for ( ; tmp > 1; --tmp){
		if (num % tmp == 0 && den % tmp == 0){
			num /= tmp;
			den /= tmp;
			break;
 		}
	}
}

Rational Rational :: operator+(const Rational &r1) const
{
	Rational tmp;

	tmp.num = num * r1.den + den * r1.num;
	tmp.den = den * r1.den;
	tmp.ReductFraction();

	return tmp;
}

Rational Rational :: operator*(const Rational &r1) const
{
	Rational tmp;

	tmp.num = num * r1.num;
	tmp.den = den * r1.den;
	tmp.ReductFraction();

	return tmp;
}

bool Rational :: operator<(const Rational &r1) const
{return num * r1.den < den * r1.num;}

bool Rational :: operator==(const Rational &r1) const
{return num == r1.num && den == r1.den;}

int main()
{
	Rational r1(1,6), r2(1,6),r3;

	r3 = r1 + r2;

	r1.display(); cout << "+"; r2.display(); cout << "="; r3.display();
	cout << endl;
}
```

`+ * < == ` 四个运算符也可以重载成全局函数，一般类里面，数据成员都是定义成私有的，所以重载函数都被设为类的友元函数。

```c++
#include <iostream>
using namespace std;

class Rational
{
	friend Rational operator+(const Rational &r1, const Rational &r2);
	friend Rational operator*(const Rational &r1, const Rational &r2);
	friend bool operator<(const Rational &r1, const Rational &r2);
	friend bool operator==(const Rational &r1, const Rational &r2);

private:
	int num;
	int den;
	void ReductFraction();

public:
	Rational(int n = 0,int d = 1) {num = n; den = d; ReductFraction();}
	void display() const {cout << num << '/' << den;}
};

void Rational :: ReductFraction()
{
	int tmp = (num > den) ? den : num;

	for ( ; tmp > 1; --tmp){
		if (num % tmp == 0 && den % tmp == 0){
			num /= tmp;
			den /= tmp;
			break;
 		}
	}
}

Rational operator+(const Rational &r1, const Rational &r2) 
{
	Rational tmp;

	tmp.num = r1.num * r2.den + r1.den * r2.num;
	tmp.den = r1.den * r2.den;
	tmp.ReductFraction();

	return tmp;
}

Rational operator*(const Rational &r1, const Rational &r2) 
{
	Rational tmp;

	tmp.num = r1.num * r2.num;
	tmp.den = r1.den * r2.den;
	tmp.ReductFraction();

	return tmp;
}

bool operator<(const Rational &r1, const Rational &r2) 
{return r1.num * r2.den < r1.den * r2.num;}

bool operator==(const Rational &r1, const Rational &r2) 
{return r1.num == r2.num && r1.den == r2.den;}

int main()
{
	Rational r1(1,6), r2(1,6),r3;

	r3 = r1 + r2;

	r1.display(); cout << "+"; r2.display(); cout << "="; r3.display();
	cout << endl;
}
```

虽然大多数运算符都可以重载成成员函数或者全局函数，但是赋值运算符`=`，下标运算符`[]`，函数调用运算符`()`和成员访问运算符`->`必须重载成成员函数，因为这些运算符的第一个运算对象必须是相应类的对象，定义成成员函数可以保证第一个运算对象的正确性。

具有赋值意义的运算符，如 `++` 和 `--` ，最好重载为成员函数；

具有两个运算对象且计算结果会产生一个新的对象的运算符，比如`+ - < >`等，最好重载成全局函数，这样可以使用更加灵活。比如`2+r1`就是合法的，参数传递时，如果类型不匹配，会自动进行类型转换：首先调用Rational的构造函数，生成一个`num = 2, den = 1`的临时对象，再把这个临时对象作为`operator+`的第一个参数。

#### 11.3.1 赋值运算符的重载

一般来讲，需要定义复制构造函数的类也需要定义赋值运算符重载函数。它们的区别在于：复制构造函数用于创建一个对象时，用另一个已存在的同类对象对其进行初始化。对于两个已存在的对象，可以通过赋值运算用一个对象的值来改变另一个对象的值。

例如r1是一个Rational类的对象，则`Rational r2 = r1`执调用的是复制构造函数，对于另一个已知的Rational类的对象r3，则`r2 = r1`调用的是赋值运算符重载函数。

赋值运算符重载函数的原型是：

```c++
T &operator=(const T &a);
```

#### 11.3.2 下标运算符的重载

下标运算符是一个二元运算符，第一个运算对象是当前对象，第二个运算数是下标值。下标运算符必须重载成为成员函数，函数原型是：

```c++
数组元素类型 &operator[](int 下标值);
```

#### 11.3.3 函数调用运算符重载

调用运算符也是一个二元函数，他的第一个运算对象是函数名，第二个参数是一个表达式，对应于函数调用的形式参数列表。运算的结果是函数返回值。函数原型是：

```c++
函数的返回值 operator() (形式参数表);
```

#### 11.3.4 ++和--运算符的重载

这两种运算符的特殊性在于，既可以作为前缀使用，也可以作为后缀使用，所以需要定义两个版本。

问题在于，两种运算符的重载函数的形式参数个数和类型完全相同，普通重载函数无法区分。为了解决这个问题，C++规定**后缀**运算符重载函数接受一个额外的int型的形式参数。

例如：设计一个报警的计数器类。计数器从0开始计数，当达到设定好的报警值时，计数器发生警报，计数器的值不再增加。

```c++
#include <iostream>
using namespace std;

class counter
{
private:
	int val;
	int alarm;

public:
	counter(int a): val{0}, alarm{a} {}
	counter & operator++ ();
	counter operator++ (int);
	void print() const {cout << val << endl;}
};

counter & counter::operator++()
{
	if (val == alarm)
		cout << "已经超过报警值" << endl;
	else{
		++val;
		if (val == alarm)
			cout << "已经达到报警值" << endl;
	}

	return *this;
}

counter counter::operator++ (int x)
{
	counter tmp = *this;

	if (val == alarm)
		cout << "已经超过报警值" << endl;
	else{
		++val;
		if (val == alarm)
			cout << "已经达到报警值" << endl;
	}

	return tmp;
}

int main()
{
	counter t(3); //报警值设为3

	t.print(); //初始值为0
	++t; //前缀运算，val值+1
	t.print(); //输出1
	(++t).print(); //前缀运算，输出2
	(t++).print(); //后缀运算，先输出达到报警值，再输出2
	t.print(); //输出3
    t++;
	t.print(); //达到报警值数值不会再增加，先输出超过报警值，再输出3
	
	return 0;
}
```

```shell
# run result
0
1
2
已经达到报警值
2
3
已经超过报警值
3
```

#### 11.3.5 输入/输出运算符的重载

C++规定输入/输出运算符必须重载成全局函数，一般将此全局函数声明为类的友元。

**输出运算符的重载**

流插入运算符（<<）被看成时一个二元函数，如：

```c++
int x = 3;
cout << x;
```

两个运算对象分别是cout和x。<<执行的结果是左边的输出流对象的引用。例子里运算结果是对象cout。因为<<是左边的对象的引用，所以允许执行`cout << x << y;`，限制性`cout << x`，执行的结果是`cout `，然后执行`cout << y`。输出运算符重载函数的原型是：

```c++
ostream & operator<<(ostream & os, const T &obj)
{
    os << 要输出的内容;
    
    return os;
}
```

```c++
//Rational类的输出运算符重载函数
ostream & operator<<(ostream & os, const Rational & obj)
{
    os << obj.num << "/" << obj.den;
    
    return os;
}
```

```c++
//插入排序对vector容器的输出运算符重载
#include <iostream>
#include <vector>
using namespace std;

template<class T>
void insertSort(vector<T> &a)
{
    int k;
    T tmp;
    
    for(int j = 1; j < a.size(); ++j){
        tmp = a[j];
        for(k = j - 1; tmp < a[k] && k >=0; --k){
            a[k+1] = a[k];    
        }
        a[k+1] = tmp;
    }
}

template<class T>
ostream & operator<<(ostream & out,vector<T> & src)
{
	for (vector<int>::iterator it = src.begin(); it != src.end(); ++it)
	{
		out << *it << " ";
	}

	return out;
}


int main()
{
    vector<int> a = {9,8,7,6,5,4,3,2,1};
    
    insertSort(a);
    
    cout << a << endl;
    
    return 0;
}
```

```shell
# run result
1 2 3 4 5 6 7 8 9
```



**输入运算符的重载**

输入运算符也是一个二元函数，重载>>时，第一个参数是一个输入流对象的额引用，引用它要读的流，并且返回对同一个流的引用；第二个形式参数是对要读入的对象的非常量引用，该形式参数必须是非常量的，因为输入运算符重载函数的目的是要将数据读入此对象。函数原型是：

```c++
istream & operator>>(istream & is, T &obj)
{
    is >> 对象的数据成员;
    
    return is;
}
```

### 11.4 自定义类型转换

比如`r1=2`是合法的，因为会调用类的构造函数，将2转换为一个rational类的对象，但是如果出现`int x ; x = r1;` 就会报错，因为r1不是内置类型，编译器不知道该如何转换。

#### 11.4.1 内置类型到类类型的转换

构造函数实现了内置类型到类类型的转换。但有时候我们不希望编译器执行这种隐式转换，方法是在构造函数前加上关键字`explicit`，比如counter类里：

```c++
explicit counter(int a): val{0}, alarm{a} {}

t = 6; //报错
t = counter(6); //正确
```

#### 11.4.2 类类型到内置类型的转换

通过定义类型转换函数来实现：

```c++
operator 目标类型名 () const
{
    return (结果为目标类型的表达式);
}
//例子
operator double () const
{
    return (double(num)) / den;
}
```

类型转换函数不指定返回类型，也没有形式参数，它的参数就是当前对象。函数也不会修改当前对象的值，所以是常量成员函数。

#### 11.5.1 完整的Rational类

```c++
//filename: rational.hpp
#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
using namespace std;

class Rational
{
	friend istream & operator>>(istream & is, Rational & obj);
	friend ostream & operator<<(ostream & os, const Rational & obj);  
	friend Rational operator+(const Rational &r1, const Rational &r2);
	friend Rational operator*(const Rational &r1, const Rational &r2);
	friend bool operator<(const Rational &r1, const Rational &r2);
	friend bool operator==(const Rational &r1, const Rational &r2);
	
private:
	int num;
	int den;
	void ReductFraction();

public:
	Rational(int n = 0,int d = 1) {num = n; den = d; ReductFraction();}
	void display() const {cout << num << '/' << den;}
	operator double () const {return (double(num)) / den;} 
};

void Rational :: ReductFraction()
{
	int tmp = (num > den) ? den : num;

	for ( ; tmp > 1; --tmp){
		if (num % tmp == 0 && den % tmp == 0){
			num /= tmp;
			den /= tmp;
			break;
 		}
	}
}

Rational operator+(const Rational &r1, const Rational &r2) 
{
	Rational tmp;

	tmp.num = r1.num * r2.den + r1.den * r2.num;
	tmp.den = r1.den * r2.den;
	tmp.ReductFraction();

	return tmp;
}

Rational operator*(const Rational &r1, const Rational &r2) 
{
	Rational tmp;

	tmp.num = r1.num * r2.num;
	tmp.den = r1.den * r2.den;
	tmp.ReductFraction();

	return tmp;
}

ostream & operator<<(ostream & os, const Rational & obj)
{
    os << obj.num << "/" << obj.den;
    
    return os;
}

istream & operator>>(istream & is, Rational & obj)
{
	is >> obj.num >> obj.den;
	obj.ReductFraction();

	return is;
}

bool operator<(const Rational &r1, const Rational &r2) 
{return r1.num * r2.den < r1.den * r2.num;}

bool operator==(const Rational &r1, const Rational &r2) 
{return r1.num == r2.num && r1.den == r2.den;}

#endif
```

```c++
//filename: rational.cpp
#include <iostream>
#include "rational.hpp"

int main()
{
	Rational r1, r2, r3, r4;
	double x;

	cin >> r1;
	cin >> r2;

	r3 = r1 + r2;
	cout << r1 << "+" << r2 << "=" << r3 << endl;

	r4 = r1 * r2;
	cout << r1 << "*" << r2 << "=" << r4 << endl;

	x = 5.5 - r1;
	cout << 5.5 << "-" << r1 << "=" << x << endl;

	return 0;
}
```

```shell
# input value
8 16
1 4
# run result
1/2+1/4=3/4
1/2*1/4=1/8
5.5-1/2=5
```







## 第十二章 组合与继承



**将派生类对象隐式转换为基类对象**

* **将派生类对象赋给基类对象**：把派生类中的基类部分赋给此基类对象，派生类新增加的成员就被舍弃了。
* **基类指针指向派生类对象**：
* **基类的对象引用派生类的对象**：


 **多态性与虚函数**

* 虚函数在派生类中重定义时，虚函数的函数原型（包括返回类型、函数名、参数个数和参数类型）必须与基类中的虚函数完全相同，否则编译器会认为派生类有两个重载函数

<u>构造函数不能是虚函数，但析构函数可以是虚函数，而且最好是虚函数。</u>

## 第十三章 泛型机制——模板



## 第十四章 输入/输出与文件

### 14.1 流与标准库

**输入流**：字节从设备（如键盘、磁盘）流向内存。

**输出流**：字节从内存流向设备。

**过程式的输入/输出**：通过C语言保留下来的函数库中的输入/输出函数来实现。

**面向对象的输入/输出**：通过C++类库来实现。

`iostream`定义了基于控制台的输入/输出类型

`fstream`定义了基于文件的输入/输出类型

`sstream`定义了基于字符串的输入/输出类型。

所有输入/输出的类都是从一个公共的基类`ios`派生的。

![](F:\Project\Reading-Notes\Cpp\assets/输入输出类的继承.png)

### 14.2 输入/输出缓冲

输入/输出过程由两个阶段组成：程序与输入/输出对象对应的缓冲区之间的信息交互，缓冲区与外围设备之间的信息交互。

### 14.3 基于控制台的输入/输出

#### 14.3.3 格式化的输入/输出

1. 设置整型数的基数

**参数化的流操纵符**：`setbase()`

流的基数值只有被显式更改才会变化，否则一直沿用原有的基数。

```c++
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int a = 100;
    cout << setbase(10) << a << endl;
    cout << setbase(8) << a << endl;
    cout << a << endl;

    return 0;
}
```

```shell
# run result
100
144
144
```

2. 设置浮点数的精度

设置浮点数的精度（即实型数的有效位数）可以用流操纵符`setprecision`或基类的成员函数`precision`来实现。调用了两者中的某一个将影响所有输出的浮点数的精度，直到下一个设置精度的操作为止。

```c++
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    double x = 123.456789, y = 9876.54321;

    for (int i = 9; i > 0; --i){
        cout << setprecision(i)
        << x << '\t' << y << endl;
    }
    /*
    for (int i = 9; i > 0; --i){
    	cout.precision(i);
    	cout << x << '\t' << y << endl;
    }
    */

    return 0;
}
```

```shell
# run result
123.456789	9876.54321
123.45679	9876.5432
123.4568	9876.543
123.457	9876.54
123.46	9876.5
123.5	9877
123	9.88e+03
1.2e+02	9.9e+03
1e+02	1e+04
```

3. 设置域宽

设置域宽可用于输入，也可以用于输出。设置域宽只适用于下一次输入和输出，之后操作的域宽将恢复默认值。如果实际宽度大于指定的宽度，则按实际宽度输出。

```c++
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int a = 123, b = 456;
    cout << a << b << endl;
    cout << setw(5) << a << setw(5) << b << endl;
    cout << a << b << endl;
    cout << setw(3) << 1234 << setw(2) << 56 << endl;

    return 0;
}
```

```shell
# run result
123456
  123  456
123456
123456
```

设置域宽也可由于输入，当输入是字符串时，如果输入的字符个数大于设置的域宽，只读取域宽指定的字符个数。

```c++
char a[9], b[9];
cin >> setw(5) >> a >> setw(5) >> b;
//  intput: abcdefghijklmn
// a: abcd   b: efgh
```

### 14.4 基于文件的输入/输出

```c++
ofstream outfile("file2");
ofstream outfile("file2", ofstream::out);
```

如果文件存在，则会清空文件，不存在则自动创建。如果需要读取一个文件并且把数据写回，则可以：

```c++
fstream iofile("file3", fstream::in | fstream::out)
```

文件同时以`in`和`out`操作打开，不会清空文件。

执行打开文件操作后，应该检查文件是否打开成功，是一个良好的程序设计习惯。

显式的关闭文件也是一个良好的程序设计习惯。

```c++
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

int main()
{
    ofstream out("file");
    ifstream in;

    if (!out) cout << "create file error" << endl;
    for (int i = 0; i < 10; ++i){
        out << i << " ";
    }
    out.close();

    in.open("file");
    if (!in) cout << "open file error" << endl;
    int tmp;
    while (in >> tmp){
        cout << tmp << " ";
    }
    in.close();

    return 0;
}
```

写一个包含各种数据类型的文件操作程序。

```c++
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

int main()
{
    ofstream out("file");
    
    if (!out) cout << "create file error" << endl;
    out << 10 << ' ' << 123.45 << '\t' << "\"This is my program\"\n";
    out.close();

    return 0;
}
```

读一个包含各种类型的文件。

```c++
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    ofstream out("file");
    
    if (!out) cout << "create file error" << endl;
    out << 10 << ' ' << 123.45 << '\t' << "\"This is my program\"\n";
    out.close();

    ifstream in("file");
    if (!in) cout << "open file error" << endl;
    int a; double b; string s, tmp;
    in >> a >> b;
    while (in >> tmp)
        s += tmp + " ";
    cout << a << " " << b << " " << s << endl;

    return 0;
}
```

```shell
# run result
10 123.45 "This is my program"
```























