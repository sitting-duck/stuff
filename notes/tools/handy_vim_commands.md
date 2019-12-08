For HTML files putting newlines in between opening and closing tags. Especially handy for code copied from websites that you want to reformat. Code copied from websites seems to always have ugly formatting and I want a fast way to do away with this in VIM
Here specifically we place newlines (carriage returns in VIM search and replace specifically) between closing and opening tags for a table cell so our table will look all pretty in our code.
```
%s#</td><td>#</td>\r<td#gc
```

