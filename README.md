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
    *  A new subscript to this set is given
