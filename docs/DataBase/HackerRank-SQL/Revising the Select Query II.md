> # Revising the Select Query II

Tags: `Easy`

Links: https://www.hackerrank.com/challenges/revising-the-select-query-2/problem

---

Query the names of all American cities in **CITY** with populations larger than `120000`. The *CountryCode* for America is `USA`.

**Input Format**

The **CITY** table is described as follows:

![CITY.jpg](https://s3.amazonaws.com/hr-challenge-images/8137/1449729804-f21d187d0f-CITY.jpg)

----

```mysql
SELECT name
FROM city
WHERE countrycode = 'USA' AND population > 120000;
```

