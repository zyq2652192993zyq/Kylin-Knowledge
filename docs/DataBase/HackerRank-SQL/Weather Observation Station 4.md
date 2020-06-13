> # Weather Observation Station 4

Tags: `Easy`

Links: https://www.hackerrank.com/challenges/weather-observation-station-4/problem

-----

Let $N$ be the number of *CITY* entries in **STATION**, and let $N^{'}$ be the number of distinct *CITY* names in **STATION**; query the value of $N - N^{'}$ from **STATION**. In other words, find the difference between the total number of *CITY* entries in the table and the number of distinct *CITY* entries in the table.

**Input Format**

The **STATION** table is described as follows:

![img](https://s3.amazonaws.com/hr-challenge-images/9336/1449345840-5f0a551030-Station.jpg)

----

```mysql
SELECT COUNT(city) - COUNT(DISTINCT city)
FROM station;
```

参见《MySQL必知必会》的12.1.2 `COUNT`函数。