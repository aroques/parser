# Parser

This scanner implements option 3: FSA table and driver. 

## Usage

To build the project run:
```
make
```

To run the project you must provide a file that contains tokens. There are 3 ways to do this:  
1. Provide a text file that contains strings. The file should have the extension `.fs182`.
```
scanner filename
```    
2. Provide the text file to stdin using redirection:
```
scanner < filename.fs182
```    
3. Or, provide strings via the keyboard (stdin) and press ctrl-d to enter the EOF character when done: 
```
scanner
```    
