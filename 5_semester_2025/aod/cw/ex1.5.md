Create LP instance of a problem described in exercise 5.

## Problem Description

A salad is any combination of the following ingredients: **tomatoes, lettuce, spinach, carrots, and oil**. Each salad must satisfy the following nutritional constraints:

* At least **15 grams of protein**
* Between **2 and 6 grams of fat**
* At least **4 grams of carbohydrates**
* At most **100 milligrams of sodium**
* No more than **50% of the salad’s mass** can be greens (lettuce or spinach)

The nutritional content of each ingredient (per 100 grams) is given in the table below:

| Ingredient | Energy (kcal) | Protein (g) | Fat (g) | Carbohydrates (g) | Sodium (mg) |
| ---------- | ------------- | ----------- | ------- | ----------------- | ----------- |
| Tomato     | 21            | 0.85        | 0.33    | 4.64              | 9.00        |
| Lettuce    | 16            | 1.62        | 0.20    | 2.37              | 8.00        |
| Spinach    | 371           | 12.78       | 1.58    | 74.69             | 7.00        |
| Carrot     | 346           | 8.39        | 1.39    | 80.70             | 508.20      |
| Oil        | 884           | 0.00        | 100.00  | 0.00              | 0.00        |

We want to create a salad with the **minimum number of calories** while satisfying all the above nutritional constraints.

## Problem Solution

Use simplex solver at https://www.emathhelp.net/calculators/linear-programming/simplex-method-calculator

```
min Z = 21x_1 + 16x_2 + 371x_3 + 346x_4 + 884x_5
subject to
0.85x_1 + 1.62x_2 + 12.78x_3 + 8.39x_4 + 0.00x_5 >= 15,
0.33x_1 + 0.20x_2 + 1.58x_3 + 1.39x_4 + 100.00x_5 >= 2,
0.33x_1 + 0.20x_2 + 1.58x_3 + 1.39x_4 + 100.00x_5 <= 6,
4.64x_1 + 2.37x_2 + 74.69x_3 + 80.70x_4 + 0.00x_5 >= 4,
9.00x_1 + 8.00x_2 + 7.00x_3 + 508.20x_4 + 0.00x_5 <= 100,
0.50x_2 + 0.50x_3 - 0.50x_1 -0.50x_4 -0.50x_5 <= 0
```

Answer (approx): 

```
x_1 (Tomato) = 298.36g
x_2 (Lettuce) = 0g
x_3 (Spinach) = 308.51g
x_4 (Carrot) = 10.14g
x_5 (Oil) = 0g
```