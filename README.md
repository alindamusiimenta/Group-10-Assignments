# Group 10 - Rolling Operations

This assignment implements common rolling and moving calculations in C++. Each program works on the same sample data and prints the input values followed by the calculated result.

## Task Requirements

The programs implement:

1. `rolling_min` - the minimum value in each rolling window.
2. `rolling_max` - the maximum value in each rolling window.
3. `rolling_std` - the standard deviation in each rolling window.
4. `moving_average` - the arithmetic mean in each rolling window.
5. `exponential_moving_average` - a weighted average that gives more importance to recent values.

For the first four operations, a result is produced only after a complete window is available. Earlier positions are displayed as `None`. The exponential moving average starts with the first data value.

## Implementation Strategy

- Store input and output values in `std::vector<double>`.
- Move through the data one position at a time.
- For the rolling minimum and maximum, compare all values in the current window.
- For the moving average, add the values in the current window and divide by the window size.
- For the rolling standard deviation, calculate the window mean, squared differences, variance, and square root.
- For the exponential moving average, update the previous result using:

	`EMA_t = alpha * x_t + (1 - alpha) * EMA_(t-1)`

- Use `NaN` internally for rolling results that do not yet have enough values, and print those values as `None`.

## Key Decisions and Approaches

- A window size of `3` is used in the examples.
- Rolling calculations use complete windows only.
- `rolling_std` uses sample standard deviation by default (`ddof = 1`). Passing `ddof = 0` would calculate population standard deviation.
- The exponential moving average uses a span of `3`, converted to an alpha value with:

	`alpha = 2 / (span + 1)`

- The first exponential moving average value is set equal to the first input value, which provides the initial history required for the calculation.
- Each program is kept in a separate source file so that every operation can be compiled and tested independently.

## Files

| File | Operation |
| --- | --- |
| `group10_1_rolling_min.cpp` | Rolling minimum |
| `group10_2_rolling_max.cpp` | Rolling maximum |
| `group10_3_rolling_std.cpp` | Rolling standard deviation |
| `group10_4_moving_average.cpp` | Moving average |
| `group10_5_exponential_moving_average.cpp` | Exponential moving average |

## Testing Procedures

Compile each file using a C++11-or-newer compiler. For example, with `g++`:

```bash
g++ -std=c++11 group10_1_rolling_min.cpp -o rolling_min
./rolling_min
```

Repeat the same process for the other four `.cpp` files. Check that:

1. The input data is printed correctly.
2. The first two rolling positions are `None` when the window is `3`.
3. Each later rolling value is calculated from exactly three consecutive values.
4. The standard deviation values are rounded to three decimal places.
5. The exponential moving average begins at `10.000` and changes gradually toward the new input values.

## Working Examples

All examples use this input:

```text
[10, 12, 9, 15, 20, 18, 22, 25, 19, 30]
```

### Rolling Minimum

Command:

```bash
g++ -std=c++11 group10_1_rolling_min.cpp -o rolling_min
./rolling_min
```

Output:

```text
Data:              [ 10, 12, 9, 15, 20, 18, 22, 25, 19, 30 ]
rolling_min(w=3):  [ None, None, 9.000, 9.000, 9.000, 15.000, 18.000, 18.000, 19.000, 19.000 ]
```

### Rolling Maximum

```text
rolling_max(w=3):  [ None, None, 12.000, 15.000, 20.000, 20.000, 22.000, 25.000, 25.000, 30.000 ]
```

### Rolling Standard Deviation

```text
rolling_std(w=3):  [ None, None, 1.528, 3.000, 5.508, 2.517, 2.000, 3.512, 3.000, 5.508 ]
```

### Moving Average

```text
moving_average(w=3): [ None, None, 10.333, 12.000, 14.667, 17.667, 20.000, 21.667, 22.000, 24.667 ]
```

### Exponential Moving Average

With `span = 3`, `alpha = 0.5`:

```text
exponential_moving_avg: [ 10.000, 11.000, 10.000, 12.500, 16.250, 17.125, 19.562, 22.281, 20.641, 25.320 ]
```