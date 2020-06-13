> # Weather Observation Station 3

Tags: `Easy`

Links: https://www.hackerrank.com/challenges/weather-observation-station-3/problem

-----

Query a list of *CITY* names from **STATION** with even *ID* numbers only. You may print the results in any order, but must exclude duplicates from your answer.

**Input Format**

The **STATION** table is described as follows:

![img](https://s3.amazonaws.com/hr-challenge-images/9336/1449345840-5f0a551030-Station.jpg)

-----

```mysql
SELECT DISTINCT city
FROM station
WHERE ID % 2 = 0;
```

