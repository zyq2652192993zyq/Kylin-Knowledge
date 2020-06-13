> # Weather Observation Station 9

Tags: `Easy` `Basic Select`

Links: https://www.hackerrank.com/challenges/weather-observation-station-9/problem

------

Query the list of *CITY* names from **STATION** that *do not start* with vowels. Your result cannot contain duplicates.

**Input Format**

The **STATION** table is described as follows:

![img](https://s3.amazonaws.com/hr-challenge-images/9336/1449345840-5f0a551030-Station.jpg)

where *LAT_N* is the northern latitude and *LONG_W* is the western longitude.

-----

```mysql
SELECT DISTINCT city
FROM station
WHERE city REGEXP '^[^aeiou]';
```

使用正则表达式元字符中的负值范围`[^xyz]`，匹配不包含在`[]`内的字符。