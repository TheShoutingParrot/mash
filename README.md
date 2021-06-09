# mash

mash (or My own hASH) is a simple hash program that generates a 64 character hash string from any input.

**NOTE: This hashing algorithm was made for fun and as an example of what a very stupid hashing algorithm could look like! Please do not use this for actual hashing!**

### Compilation

After installing and when in the mash directory you can compile by running `make all`. This will install an executable for this program called `mash`.

### Usage

To hash a string you must just run the program with the second argument being the string you want to hash, like this:

```
./mash "string to be hashed"
``` 

If you would like to hash the string "Hello there!" you would do this:

```
./mash "Hello there!"
```

and the output should be: `9I8qkELlXXo4ED1bylqayzaIhXs-LvvI2XIGgCaF3QIDjUW46w8yPx7MlmtSpCuM`.

To read the string from input (stdin) you must run the program like this:

```
./mash -
```

To hash a file it can be done simply by running:

```
cat file | ./mash -
```

For example to hash this README.md file you must run:

```
cat README.md | ./mash -
```

#### Testing the program

To check that this program is working properly please hash the [HASHME.txt](HASHME.txt) file by running:

```
cat HASHME.txt | ./mash -
```

The hash of [HASHME.txt](HASHME.txt) should be `76vEcuNyxkiKJUsEcTH-Zdw1lFzapdOINcYNnPOXad0qjYZZN54TCLQgygeYimwQ`
