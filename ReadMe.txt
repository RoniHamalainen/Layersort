
By: Roni Hämäläinen

How this works?

Lets suppose that we need to sort this list of integers:

sortme = [3, 5, -1]

// Short visual explanation with example //

[3, 5, -1]

-> height matrix

    3  5 -1
-1 [1, 1, 1]
 0 [1, 1, 0]
 1 [1, 1, 0]
 2 [1, 1, 0]
 3 [1, 1, 0]
 4 [0, 1, 0]
 5 [0, 1, 0]

 -> push ones to right

-1 [1, 1, 1]
 0 [0, 1, 1]
 1 [0, 1, 1]
 2 [0, 1, 1]
 3 [0, 1, 1]
 4 [0, 0, 1]
 5 [0, 0, 1]

 -> sum columns

 [1, 5, 7]

 -> list - offset

 [-1, 3, 5]

 Sorted!

// long explanation with example //

1. step:
- calculate min and max elements of sortme:
min = min(sortme)
min = -1

max = max(sortme)
max = 5

2. step:
- calculate x and y axel lengths:
xlen = len(sortme)
xlen = 3

// +1 because otherwise zero would not be taken into account
ylen = max - min + 1
ylen = 7

3. step:
- calculate offset
- how many more ones you need to represent for example if offset = -3 you need 3 more ones
offset = min - 1
offset = -2

4. step:
- create reference list which length is ylen and values start from zero and grow 1 at a time
referenceList = [0, 1, 2, 3, 4, 5, 6]

5. step:
- create reference map where referenceList item n points to minium sortme item + n
referenceMap = {
	-1 : 0
	 0 : 1
	 1 : 2
	 2 : 3
	 3 : 4
	 4 : 5
	 5 : 6
}

6. step:
- create matrix of ones and zeroes where one represents that current sortme[n] item is the same or larger than referenceMap[n] item
matrix = 
[
[1, 1, 1]
[1, 1, 0]
[1, 1, 0]
[1, 1, 0]
[1, 1, 0]
[0, 1, 0]
[0, 1, 0]
]

7. step:
- push matrix ones to right
-- fast way:
-- calculate sum of [1, 0, 1]
-- sum = 2
-- add two ones starting from last position
-- we get [0, 1, 1]

matrix = 
[
[1, 1, 1]
[0, 1, 1]
[0, 1, 1]
[0, 1, 1]
[0, 1, 1]
[0, 0, 1]
[0, 0, 1]
]

8. step:
- calculate column sums and put them to list
columnSums = [1, 5, 7]

9. step:
- calculate actual value from columnSums by adding offset to each of values
sorted = [1 + (-2), 5 + (-2), 7 + (-2)]
sorted = [-1, 3, 5]

Sorted!
