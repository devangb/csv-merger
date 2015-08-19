# csv-merger
A script to merge CSVs intelligently

## Usage
####Compilation
```
make
```
or
```
g++ -o mergecsv mergecsv.cpp
```

####Run
```
./mergecsv input.csv input1.csv input2.csv .... inputX.csv output.csv
```
or
```
./mergecsv
```
and follow the interface on the terminal

####Merge types
######Row wise
Table 1:
| Header1 | Header2 |
 --------- ---------
| Value1  | Value2  |

Table 2:
| Header3 | Header4 |
 --------- ---------
| Value3  | Value4  |

Merged Table:
| Header1 | Header2 | Header3 | Header4 |
 --------- --------- --------- ---------
| Value1  | Value2  | Value3  | Value4  |

######Column wise
Table 1:
| Header1 | Header2 |
 --------- ---------
| Value1  | Value2  |

Table 2:
| Header3 | Header4 |
 --------- ---------
| Value3  | Value4  |

Merged Table:
| Header1 | Header2 |
 --------- ---------
| Value1  | Value2  |
 --------- ---------
| Header3 | Header4 |
 --------- ---------
| Value3  | Value4  |
