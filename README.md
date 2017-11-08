A spacegame I do in my free time. 

Linux only for now. 

[Allegro 5](http://liballeg.org/) is required for compiling and running. 

Once allegro is installed simply compile and run with:

```
$ make
$ ./spacegame
```
You can compile with no dependencies using Docker: 

`docker run --rm -v "$PWD":/usr/src/myapp -w /usr/src/myapp dimastopel/allegro5 make`

