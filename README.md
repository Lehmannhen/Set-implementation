## ----------------------- Set implementation -----------------------
This is a C program that implements a mathematical  set as an ADT.
The set is built using a sorted linked list of positive ints. To run the program the
user have to provide the maximum number of sets on the command line.
When the program is running the user gets prompted for a command that the program should carry out.
The commands are:
* 'm' or 'M'
    * User gets prompted for a subscript corresponding to that set (0 to n - 1)
      where n is the number provided on the command line
    * Then for what value in the set to look for
    * A message telling if the value exists in the set gets printed
* 'e' or 'E'
    * User gets prompted for subscript to the first set
    * User gets prompted for subscript to the second set
    * A message telling if the sets are equal gets printed
* 'u' or 'U'
    * User gets prompted for subscript to the first set
    * User gets prompted for subscript to the second set
    * The union of these two sets gets stored in a new set
    * A new subscript to this set is given
* 'i' or 'I'
    * User gets prompted for subscript to the first set
    * User gets prompted for subscript to the second set
    * The intersection of these two sets gets stored in a new set
    * A new subscript to this set is given
* 's' or 'S'
    * User gets prompted for subscript to the first set
    * User gets prompted for subscript to the second set
    * The set difference (set1 - set2) of these two sets gets stored in a new set
    * A new subscript to this set is given
* 'n' or 'N'
    * User can create a new set by typing numbers on the command line
    * Each number typed should have a return after and the sequence should be increasing
    * E.g: 1 (enter), 2 (enter), 3 (enter) -1 (enter) A negative number is typed when done
    * A new subscript to this set is given
* 'p' or 'P'
    * User can print any set at any time by entering this command
    * User gets prompted for subscript to the set
    * The set is printed
* 'd' or 'D'
    * User gets prompted for the subscript to the set to be deleted
    * The set at that position is deleted
* 'a' or 'A'
    * All sets are deleted
* 'q' or 'Q'
    * Quits the program

## ------------------------------------------------------------
Example run of program:

![run](https://raw.githubusercontent.com/Lehmannhen/Bisection-and-Newton-method/master/images/tty.gif)


## ----------------- How to use the program --------------
* compile: gcc -g -Wall -o sets sets.c
* run: ./sets \<number of sets>

