# Calculator

Calculator is an app that reads from file the mathematical expression, parses it and calculates its value.

## Compile

Navigate to the app directory and run the following command:

```bash
make
```
For cleaning generated files type:

```bash
make clean
```

For running tests:

```bash
make test
./test
```

## Usage

Create the `expression.txt` file containing the mathematical expression with following format.<br />
- mathematical `Expression` | names of `variables` and `parameters` | values of `variables` and `parameters` <br/> Separate by comma.

E.g.
```
sin(ax)+cos(bx)+pow(x,c) | x,a,b,c | 2,15,30,3
```


Run

```bash
./executable
```

## Available mathematical functions

* *, /, -, +
* pow(x, y)
* log(x, y)
* sin(x)
* cos(x)
* tg(x)
* ctg(x)
