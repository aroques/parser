# Parser

A recursive descent parser written in C++. 

## Usage

To build the project run:
```
make
```

To run the project you must provide a file that contains source code. There are 3 ways to do this:  
1. Provide a source code file with the extension `.fs182`.
```
parser filename
```    
2. Provide the source code file to stdin using redirection:
```
parser < filename.fs182
```    
3. Or, provide source code via the keyboard (stdin) and press ctrl-d to enter the EOF character when done: 
```
parser
```    
