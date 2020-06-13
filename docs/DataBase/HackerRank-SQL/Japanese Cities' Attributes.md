> # Japanese Cities' Attributes

Tags: `Easy`

Links: https://www.hackerrank.com/challenges/japanese-cities-attributes/problem

---

Query all attributes of every Japanese city in the **CITY** table. The *COUNTRYCODE* for Japan is `JPN`.

**Input Format**

The **CITY** table is described as follows:

![img](https://s3.amazonaws.com/hr-challenge-images/8137/1449729804-f21d187d0f-CITY.jpg)

---

```mysql
SELECT *
FROM city
WHERE countrycode = 'JPN';
```

