which two SQL data types can represent images or sounds?

BINARY and TINYBLOB


soundblob is not a thing.

Refer to the given SQL syntax: 
```
ALTER TABLE tbl_name action [, action];
```

what does this syntax allow?
With ALTER TABLE we can drop an index, and changing column types is also correct answer here. 


You messed up teh question about adding an index becuase

```
ALTER TABLE 'Salesperson' ADD INDEX 'city_index'(city)
```

This is the correct answer, you put UNIQUE before INDEX. 
Your dumb mind figured that putting a fancy thing on the end would make a better fancier query, 
you shouldn't use UNIQUE for an index for city, bc it is perfectly fine that two Salespeople could live in the same city and this would not be an error. Context clues hun. Database isn't just about syntax, it's also about usage.

What is the name of the special internal database where the query optimizer finds information?

relational catalog

What is the correct way to use the DROP INDEX command to drop a primary key from a table?

```
DROP INDEX PRIMARY ON tblname
```

What action deletes all rows from a table?
Omitting the WHERE clause from a DELETE statement.
Not DELETE *

You would never have to do that, you just do DELETE table if you want to delete all the rows.

What is the difference between COUNT(*) and COUNT(colname) for specified column names?

COUNT(*) counts every column selected and COUNT(col_name) counts only non null values. 

COUNT() basically counts the number of rows returned by some query. Remember, a query always just returns rows.


