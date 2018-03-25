My make file compiles two different programs. They share the same files
but the difference is the is the read in file differnce. The ony files
the two programs don't share are "serial_wordCount.c" and "thread_wordCount.c"

Now I did get threads to work but I wasn't able to parallize it. Also for 
some reason when I call qsort it does move the items around but not correctly
and I don't know how to fix it because my compare is either a string compare
or the int and so there really isn't much for me todo.

To run the code you need to give the filename and for sorting alphabet you
need to add "alpha" if you want to by cout type "count" but really if you don't
type in that command correctly it will default by "count" although qsort also
doesn't do that correctly.

for example:

./serial testfile2 alpha -->this for serial alphabet
./serial testfile2 count -->this for serial count
./thread testfile2 alpha -->this for thread alphabet
./thread testfile2 count -->this for thread count
