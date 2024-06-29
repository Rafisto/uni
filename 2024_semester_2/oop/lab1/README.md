# Prime Number Generator

## Description
The `prime_number_generator` program generates prime numbers up to a specified count and retrieves prime numbers based on the input provided.

## Usage
```
prime_number_generator [ARGUMENTS]
```

## Arguments
- **arg1**: Initial value for the count of prime numbers to generate.

## Options
There are no options for this program.

## Input
The program takes an integer argument `arg1` to specify the count of prime numbers to generate.

## Output
The program prints the specified count of prime numbers and retrieves prime numbers corresponding to the provided input arguments.

## Return Status
The program returns 0 on success, and non-zero values on failure.

## Example
```bash
prime_number_generator 5 2 4 7
```
Output:
```
Successfully initialized PrimeNumbers object of count 5
2 --> 2
4 --> 7
7 --> 17
```

## Errors
- If insufficient arguments are provided, the program displays an error message and exits.
- If an invalid argument is provided, the program displays an error message and continues to process subsequent arguments.