The output will vary from run to run. We only tests the following conditions.

1. All cells walked.
2. The sum of steps match the sum of all number in the cells.

# Example Input
a 2 2
a 2 3
a 3 2
b 1
b 2
q

# Example Output
15
   3   1
   6   5
11
   1   2   1
   3   3   1
28
   1   1
   6   4
   9   7
2703
  12  24  18  11   3   6   6   7   6   5   2   3   5   7   1
  19  25  20  15  17  10  13  15   5   6   6   6   7   8   5
  18  19  19  13  13  15  10  10   7   4   7   6   9   9   6
  22  31  11   8   8   5  10   8   8   8   4   6   5   9   4
  21  29  21  14  13   3   5  12   6  10   5   3   9   5   2
  19  37  31  18  11   8   8   3   9   7   6  12   3   4   4
  18  21  23  18  15   4  13   9   9  14   9   8   3   4   4
  20  23  19  12   5   8  10  11   7   9   9   6  12   6   1
  13  17  12   9   4  12   6   9   5   8   7   8   6   6   4
  12  19  18  12   8  10   8   3   4   5   6   9   7  12  10
  13  19  15  10  10  13  14   8   5   4   4  17  21  22  19
  13  28  21  18  14  18  20  11  10   8  10  23  18  27  22
   7  14  14  19  18  17  20  17  14  12  27  25  22  17  24
   5   7  14  21  22  21   8  13  11  19  42  24  20  24  25
   3   9  16  13  10   7   4   3   6  18  26  17   6  14  11
11582
  11  27  14   6   1   2   5   4   5   6   2   4   3   3   4   5   4   5   1
  19  18  23  16   9   6   7  10   6   6   6   8  11   7   7   5   9   4   2
  11  14  13  13  13   5   2   6   8   5   3   6   7   9   6   7   9  11   4
  20  18  12  13   7   3   6   5   3   3   3   5  11   9  15  19   9  17   9
  16  21  14   6  11   8   9   8   5   3   5   7   8  12  23  22  18  14   8
  13  19  11   9   7   6   9  11   5   7   6   7  13  22  27  15  16  13  12
   8  16  11   9   9   9   6  13   7   5   4   7  12  21  14  23  23  16  12
  11  13  12  15  12  11   5  10   8   8   5   8   7  17  26  14  22  18  18
   5  11  14  10  12  11   5  16   8   6   7  10  14  10  16  27  21  19  17
   4  14  11  14  13  13  13  12   8   7  14  11  13  18  19  23  21  26  16
  11  15  17  18  21  11  13  13  13   7  13  15  18  17  14  19  16  19  14
  13  15  12  16  10  12  17  17  12  10  14  18  11  16  14  14  16  23  19
   9  13  15  15  17  11  13  15  11  14  15  23  12  12  14  15  20  32  18
   3  12   9  13  17  16   9   8  11  15  19  11  14  15  14  16  34  27  17
   7  12  11   9  16  14   7   5   6  23  12  10  23  20  18  21  25  31  12
   8  13  12  17  13  16  12   8  14  17  14  20  20  17  14  23  20  22  18
   8  12  16   9  12   9  10  10  11  16  14  17  12  20  20  22  19  16  13
  14  26  15  20  13  10   9   7  16  10  14  15  15  23  21  13  20  20  17
  18  24  24  17  10   9   9  10   8  11  10  16  12  14   9  15  22  17  16
  15  20  13   7  11  11   7   6   7  10  10  12   9   8  15  20  22  18   8
  11  15  17  12  12   8   8   7   3  14  18   9   7  15  21  23  20  17  15
   9  11  14   9  17  15   8  11   7   7   9  14  14  12  11  32  30  27  21
   8  12  14  17  15  19  13   5   9   7  10  11  12  16  21  38  49  35  21
  10   8  17  22  17  18  14   8  12   4   6   5  15  25  29  47  41  35  17
   6  14  11  14  14  12  15  18   5   4   8   5  15  24  21  37  27  22  12
   7  17  14  11  12  13  18  10  13   6  10  15   7  21  25  19  26  21   9
  10  13  21   9  12  12  16  18  18  16  16  17  12  16  26  22  23  16  10
  14  25  19  13  18  17  10  10  23  26  23  17  18  25  25  16  20  19   6
  14  25  26  18  22  23  15  16  22  17  23  17  18  15  17  16  12  19  11
  18  25  27  28  23  20  21  29  21  20  20  20  18  22  13   7  14  18  10
  24  29  21  18  17  22  14  22  23  18  27  26  20  16  13  18  13  10  10
  30  40  20  16  19  19  15  13  22  32  31  29  23  17  21  15  18  13   9
  32  38  28  27  23  19  25  14  20  24  27  37  24  21  20  16  18  17   9
  24  36  29  29  20  20  19  17  17  21  19  28  19  15  18  18  21  14   9
  20  31  27  31  20  14  19  20  23  20  20  17  18  14  19  19  22  24  14
  14  28  35  28  14  13  13  23  29  25  31  23  18  21  17  24  23  30  14
  16  29  26  22  15  12  10  13  37  34  30  33  27  26  31  28  35  28  20
  10  23  18  13   7  15  18  25  31  24  30  24  21  33  41  37  36  38  14
   6  11   9   4   4   5  14  14  12  18  13  11  14  24  37  24  15  25  14
