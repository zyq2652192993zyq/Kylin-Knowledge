> # Weather Observation Station 8

Tags: `Easy` `Basic Select`

Links: https://www.hackerrank.com/challenges/weather-observation-station-8/problem

-----

Query the list of *CITY* names from **STATION** which have vowels (i.e., *a*, *e*, *i*, *o*, and *u*) as both their first *and* last characters. Your result cannot contain duplicates.

**Input Format**

The **STATION** table is described as follows:

![img](https://s3.amazonaws.com/hr-challenge-images/9336/1449345840-5f0a551030-Station.jpg)

where *LAT_N* is the northern latitude and *LONG_W* is the western longitude.

-----

```mysql
SELECT DISTINCT city
FROM station
WHERE city regexp '^[aeiou]' 
AND city regexp '[aeiou]$';
```

第二种写法：

```mysql
SELECT DISTINCT city
FROM station
WHERE city regexp '^[aeiou].*[aeiou]$';
```

同时`RLIKE`是`REGEXP`的同义词。