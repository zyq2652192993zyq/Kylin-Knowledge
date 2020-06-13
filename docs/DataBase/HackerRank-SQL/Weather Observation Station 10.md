> # Weather Observation Station 10

Tags: `Basic Select` `Easy`

Links: https://www.hackerrank.com/challenges/weather-observation-station-10/problem

-----

Query the list of *CITY* names from **STATION** that *do not end* with vowels. Your result cannot contain duplicates.

**Input Format**

The **STATION** table is described as follows:

![img](https://s3.amazonaws.com/hr-challenge-images/9336/1449345840-5f0a551030-Station.jpg)

where *LAT_N* is the northern latitude and *LONG_W* is the western longitude.

-----

```mysql
SELECT DISTINCT city
FROM station
WHERE city REGEXP '[^aeiou]$';
```

正则表达式的元字符，负值范围匹配`[^xyz]`匹配不包含`xyz`的字符串。