Filter Graphs

A filterchain consists of a sequence of connected filters, each one connected to the previous one in the sequence. A filterchain is represented by a list of "," separated filter descriptions.

A filtergraph consists of a sequence of filterchains. A sequence of filterchains is reidpresented by a list of ";" separated filterchain descriptions.

A fil_link1ter is represented by a string of the form: [in_link_1]...[in_link_N]filter_name@=arguments
 _[out]...[out_link_M]

filter_name is the name of the filter class of which the described filter is an instance of, and has to be the name of one of the filter classes registered in the program optionally followed by "@id". The name of the filter class is optionally followed by a string of "=arguments"

arguments is a string which contains the parameters used to initalize the filter instance.
It may have one of two forms:
A ':' separated list of key=value pairs
A ':' separated list of value.

We are using the scale filter to resize the input video, using the libwscale library.

-1: select interlaced aware scaling depending on whether the source frames are flagged as interlaced or not.
It seems like we are scaling down to 1080, with interlacing awareness turned on by passing these two args:
``` 
'-vf', 'scale=-1:1080'
```


