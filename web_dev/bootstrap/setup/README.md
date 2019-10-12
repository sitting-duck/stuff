### Notes on my Experience with Setting Up Bootstrap 4  (06/21/2019)

There is pre compiled css and javascript source code according to the website. I find this very confusing already because I thought Javascript was interpreted as opposed to compiled. 
These are "compiled and minified css bundles" and "compiled and minified JavaScript plugins"

You can download the source itself but hten you need to also download the Sass compiler as well as Autoprefixer. 

Or you can do the eaiest thing in the world and use BootstrapCDN: 

I always see this in the HEAD section of the HTML doc:
```
<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css" integrity="sha384-ggOyR0iXCbMQv3Xipma34MD+dH/1fQ784/j6cY/iJTQUOhcWr7x9JvoRxT2MZw1T" crossorigin="anonymous">
```

And this is usually linked in at the bottom:
```
<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js" integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM" crossorigin="anonymous"></script>
```

The site mentions that if I am using their compiled JS, not to forget to include CDN versions of jQuery and Popper.js before the two includes above: 
```
<script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.7/umd/popper.min.js" integrity="sha384-UO2eT0CpHqdSJQ6hJty5KVphtPhzWj9WO1clHTMGa3JDZwrnQq4sF86dIHNDz0W1" crossorigin="anonymous"></script>
```

At this point I am a bit familiar with jquery, but not terribly familiar with popper. 



