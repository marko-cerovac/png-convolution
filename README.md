# 🚧 BMP image convolution - WIP 🚧

### Usage:

```text
Program arguments:
  -h [ --help ]                            print this help message
  -i [ --input ] arg (=./input.png)        infput file (PNG)
  -o [ --output ] arg (=./output.png)      output file (PNG)
  -c [ --cores ] arg (=8)                  number of CPU cores to use (defaults to the max number the CPU has)
  -k [ --kernel ] arg (=0,0,0,0,1,0,0,0,0) convolution kernel parameters as a list (eg. 0,0,1,0,0,1,0,0,1)
```

### Example

Example of using a Gaussian blur kernel for 25 passes:
```text
| 0.0625, 0.125, 0.0625 |
| 0.125,  0.25,  0.125  |
| 0.0625, 0.125, 0.0625 |
```

![2025-03-12-14:47:15-screenshot](https://github.com/user-attachments/assets/2096b6ff-5250-40bf-b42d-9ec6c2725e38)
