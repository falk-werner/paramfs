# paramfs

Fuse based filesystem to access parameters.

## Build and Run

````
cmake -B build
cmake --build build
````

````
mkdir /tmp/param
paramfs -f /tmp/param
````
