# Figure Generator

## Description
The `figure_generator` program generates various geometric figures based on the input provided and calculates their area and perimeter.

## Usage
```
figure_generator [OPTIONS] [ARGUMENTS]
```

## Options
- **-o**: Generate a circle.
- **-c**: Generate a quadrilateral (square, rhombus, or rectangle).
- **-p**: Generate a pentagon.
- **-s**: Generate a hexagon.

## Arguments
For each option, additional arguments are required:
- **-o**: Takes one argument: radius of the circle.
- **-c**: Takes four arguments: four side lengths and an angle (in degrees) of the quadrilateral.
- **-p**: Takes one argument: side length of the pentagon.
- **-s**: Takes one argument: side length of the hexagon.

Note: All arguments must be provided as floating-point numbers.

## Exit Status
The `figure_generator` program returns 0 on success, and non-zero values on failure.

## Examples
- To generate a circle with radius 5:
  ```
  figure_generator -o 5
  ```
- To generate a square with side lengths 4, 4, 4, 4, and an angle of 90 degrees:
  ```
  figure_generator -c 4 4 4 4 90
  ```
- To generate a pentagon with side length 6:
  ```
  figure_generator -p 6
  ```
- To generate a hexagon with side length 7:
  ```
  figure_generator -s 7
  ```

# Java Test

```bash
java -ea Test
```