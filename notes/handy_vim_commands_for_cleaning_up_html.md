For HTML files putting newlines in between opening and closing tags. Especially handy for code copied from websites that you want to reformat. Code copied from websites seems to always have ugly formatting and I want a fast way to do away with this in VIM
Here specifically we place newlines (carriage returns in VIM search and replace specifically) between closing and opening tags for a table cell so our table will look all pretty in our code.
```
%s#</td><td>#</td>\r<td#gc
```
For removing tabs in between two tags
```
:%s#</font>\t</td>#</font></td>#gc

```

Indent all table cells
```
:%s#<td#\t<td#gc

```

Put new table rows on their own lines
```
:%s#</tr><tr#</tr>\r<tr#gc

```

remove all tabs between tags
```
:%s#>\t<#><#gc
```

Newline with indent. Tag with a quotation mark can be edited to refine search
```
:%s#R"><#R">\r<\t#gc

```
Remove spaces before closing tag
```
:%s#\t</td>#</td>#gc
```


