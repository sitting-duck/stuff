4. If a designer wishes to create an inner join, but the two tables do not have a commonly named attribute, he can use a JOIN ON clause.

JOIN ON returns only the rows that meet the condition indicated in the ON clause.

Think ON to mean "on these conditions" like your mother would say. 

Let's review the types of INNER JOINS while were here.

Natural Join - only the rows with matching values in the matching columns. The matching columns must have the same names and similar data types. 

JOIN USING - returns only the results from the indicated columns

JOIN ON - returns only the rows that meet the join condition indicated in the ON clause.

The LEFT JOIN, RIGHT JOIN AND FULL JOIN clauses are all outer joins, 

Natural, USING, and ON, are the inner joins.

16. In the context of SELECT subquery types, a SINGLE VALUE is returned when an UPDATE subquery is used. 

Let's look at this example:
```
UPDATE PRODUCT 
SET P_PRICE = SELECT AVG(P_PRICE) FROM PRODUCT) 
WHERE V_CODE IN (SELECT V_CODE FROM VENDOR
WHERE V_AREACODE = '615')
```

Remember that a subquery will only ever return, 
- a single value
- a list of values
- a virtual table, 

it will always be one of these 3 things, 

An update, when you assign a new value to an attribute, you are assigning a single value, not a list of them. Therefore, the subquery must only return one value (one columnn, one row) If the query returns multiple values, the DBMS will generate an error.

20. An **updatable view** is a view that can be used to update attributes in the base tables that are used in the view.

Note: the old style join is the same as a CROSS join, and this appears to also be the most common kind of join. 

The Cartesian Product - also referred to as the CROSS JOIN, returns all rows in all the tables listed in the query. Each row in the first table is paried with all the rows in the second table. This happens when there is no relationship defined between the two tables. 

Both the AUTHOR and STORE tables have ten rows. If we use a Cartesian join in these two tables, we will get back 100 rows.

Most of the time, we not want a Cartesian join, and we end up with one because we failed to provide a filter on the join. 

If we actually want a cartesian join, then we should use the ANSI cross join to tell others reading the script that we actually wanted a Cartesian join.


28. An alternate syntax for a join is: 
```
SELECT columnlist FROM table1 JOIN table2 USING commonColumn
```

29. A UNION ALL query can be used to produce a relation that retains the duplicate rows.

30. The Orcacle string concatenation operator is ||

31. The use of the ALL operator allows you to compare a single value with a list of values returned by the first subquery using a comparison operator other than EQUALS (such as the greater than operator)

37. The IN operator could be used in place of INTERSECT if the DBMS does not support it.

45. The natural join determines the common attribute or attributes by looking for identically named attributes and compatible data types.

46. The HAVING clause is used to restrict the output of a GROUP BY query by applying a conditional criteria to the grouped rows.

54. When using the Oracle TO_DATE function, the code MON represents a three letter month name. 


