> # Weather Observation Station 6

Tags: `Easy`  `Basic Select`

Links: https://www.hackerrank.com/challenges/weather-observation-station-6/problem

-----

Query the list of *CITY* names starting with vowels (i.e., `a`, `e`, `i`, `o`, or `u`) from **STATION**. Your result *cannot* contain duplicates.

**Input Format**

The **STATION** table is described as follows:

![img](https://s3.amazonaws.com/hr-challenge-images/9336/1449345840-5f0a551030-Station.jpg)

where *LAT_N* is the northern latitude and *LONG_W* is the western longitude.

-----

```mysql
SELECT DISTINCT city
FROM station
WHERE city regexp '^[aeiou]';
```

涉及正则表达式。