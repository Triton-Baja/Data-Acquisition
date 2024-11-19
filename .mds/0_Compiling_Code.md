# Compiling code
We will be using `g++`, part of the [GNU Compiler Collection](https://en.wikipedia.org/wiki/GNU_Compiler_Collection) to compile our `C/C++` code. Let's try with a classic example, `HelloWorld.cpp`. 

## Writing code
First let's create a new directory where we'll store our code, just to keep things tidy and organized
```
mkdir code
```

Let's go into it
```
cd code
```

Create and open the `HelloWorld.cpp` file
```
sudo nano HelloWorld.cpp
```

```C++
#include <cstdio>

int main(){
        printf("Hello, World!\n");
        return 0;
}
```

Now we can close nano through `Ctrl + S`, `Ctrl + X`. 

## Compiling and running
The structure in which we compile code with `g++` is as follows
```
g++ source.cpp -o executable_name
```

In most cases we want the executable name to be the same as the source
```
g++ source.cpp -o source
```

Let's compile `HelloWorld.cpp`
```
g++ HelloWorld.cpp -o HelloWorld
```

We should see the executable now
```
ls
```

In Linux, we run executables by
```
./executable
```

Run `HelloWorld`
```
./HelloWorld
```
