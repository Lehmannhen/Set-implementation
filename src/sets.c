/********************************************************
 * File: sets.c
 * Purpose: Implement a set ADT using singly-linked lists
 *          of positive ints. Store the multpiple sets
 *          in an array of pointers to the heads of the sets
 *
 * Compile: gcc -g -Wall -o sets sets.c
 * Run:     ./sets <number of sets>
 *
 * Input: m, e, u, i, s, n, p, d, a, or q
 *  m: Prompts for a set and a value and checks if the set
 *     contains the value
 *
 *  e: Prompts for subscripts of two sets and prints if they 
 *     are equal or not
 *
 *  u: Prompts for subscripts of two sets and creates the union
 *     between the sets. 
 *   
 *  i: Prompts for subscripts of two sets and creates the 
 *     intersectionbetween the sets.
 *     
 *  s: Prompts for subscripts of two sets and creates the 
 *     set difference between the sets.
 *     
 *  n: Creates a new by prompting for positive integers
 *     and stops when a negative int is entered. 
 *     
 *  p: Prompts for a subsrcipt to a set to be printed
 *
 *  d: Deletes a set at a specified position
 *
 *  a: Deletes all sets
 *
 *  q: quit the program
 *
 * Output:
 *  m: prints if the set contain the value or not
 *  
 *  e: prints if the two sets are equal or not
 *
 *  u: prints the new union-set and its position in array
 *
 *  i: prints the intersection-set and its position in array
 *
 *  s: prints the set-difference and its position in array
 *
 *  n: prints the newly created set and its position in array
 *
 *  p: prints the set at the specified position in array
 *
 *  d: None
 *
 *  a: None
 *         
 *  q: None
 *
 *  Errors: Delete_all must be called with the head to the
 *          first set in the array of sets, the set at 
 *          position 0. If not a segmentation fault can
 *          occur.
 *
 * Author: Henrik Lehmann
 * 
 ********************************************************/
#include <stdio.h>
#include <stdlib.h>

struct elt_node_s {
    int elt;
    struct elt_node_s *next_elt_p;
};

typedef struct elt_node_s elt_node_t;

void Usage(char prog_name[]);
int get_value(char cmd_type);
int get_subscript(int MAX_SETS);
char get_command();
void Print(elt_node_t *set_head_p, int set_int);
void new_elt_node(elt_node_t **head_pp, elt_node_t **tail_pp, int val);
int Member(elt_node_t *set_i_p, int val);
elt_node_t* Intersection(elt_node_t *set_i_p, elt_node_t *set_j_p);
elt_node_t* Union(elt_node_t *set_i_p, elt_node_t *set_j_p);
int Equal(elt_node_t *set_i_p, elt_node_t *set_j_p);
elt_node_t* Set_difference(elt_node_t *set_i_p, elt_node_t *set_j_p);
void Delete(elt_node_t **head_pp);
void Delete_all(elt_node_t **head_pp, int MAX_SETS);

int main(int argc, char* argv[]) {    
    char user_input;
    int MAX_SETS, i, val, set_i, set_j;
    int free_pos = 0;
    elt_node_t *temp_tail_p;
    elt_node_t **sets_pp;
    
    if (argc != 2) {
        Usage(argv[0]);
    }
    MAX_SETS = strtol(argv[1], NULL, 10);
    sets_pp = malloc(MAX_SETS * sizeof(elt_node_t*));
      
    for (i = 0; i < MAX_SETS; i++) {
        sets_pp[i] = NULL;
    }    
    
    user_input = get_command();    
    while (user_input != 'Q' && user_input != 'q' ) {
        switch (user_input) {
            case 'm':
            case 'M':                   
                set_i = get_subscript(MAX_SETS);               
                val = get_value(user_input);
                
                if (Member(sets_pp[set_i], val)) {
                    printf("%d is in the set\n", val);
                }
                else {
                    printf("%d is not in the set\n", val);
                }
                break;
            case 'e':    
            case 'E':              
                set_i = get_subscript(MAX_SETS);
                set_j = get_subscript(MAX_SETS);
                if (Equal(sets_pp[set_i], sets_pp[set_j])) {
                    printf("The sets are equal\n");
                }
                else {
                    printf("The sets are not equal\n");
                }                
                break;
            case 'u':    
            case 'U':                
                set_i = get_subscript(MAX_SETS);             
                set_j = get_subscript(MAX_SETS);
             
                printf("\nUnion of the sets:\n ");
                sets_pp[free_pos] = Union(sets_pp[set_i], sets_pp[set_j]);
  
                Print(sets_pp[free_pos], free_pos);
                free_pos++;
                break;
            case 'i':    
            case 'I':
                set_i = get_subscript(MAX_SETS);                                
                set_j = get_subscript(MAX_SETS);
                               
                printf("\nIntersection of the sets:\n ");
                sets_pp[free_pos] = Intersection(sets_pp[set_i], sets_pp[set_j]);

                Print(sets_pp[free_pos], free_pos);
                free_pos++;
                break;
            case 'n':
            case 'N':
                printf("Enter an int, <= 0 to stop\n");
                val = get_value(user_input);
                
                temp_tail_p = NULL;
                while (val > 0) {
                    new_elt_node(&sets_pp[free_pos], &temp_tail_p, val);                   
                    val = get_value(user_input);                    
                }
                Print(sets_pp[free_pos], free_pos);
                free_pos++;
                break;
            case 'p':    
            case 'P':
                set_i = get_subscript(MAX_SETS);                              
                Print(sets_pp[set_i], set_i);
                break;
            case 's':
            case 'S':
                set_i = get_subscript(MAX_SETS);                                              
                set_j = get_subscript(MAX_SETS);
               
                printf("\nSet difference:\n");
                sets_pp[free_pos] = Set_difference(sets_pp[set_i], sets_pp[set_j]);
                Print(sets_pp[free_pos], free_pos);
                free_pos++;
                break;
            case 'd':
            case 'D':                
                set_i = get_subscript(MAX_SETS);
                Delete(&sets_pp[set_i]);
                break;
            case 'a':    
            case 'A':
                Delete_all(&sets_pp[0], MAX_SETS);
                free_pos = 0;
                break;
                              
            default:
                printf("No match of %c\n", user_input);                
        }
        user_input = get_command();        
    }
    Delete_all(sets_pp, MAX_SETS);
    free(sets_pp);
    sets_pp = NULL;
    
    return 0;
}






/********************************************************
 * Function: Usage
 * Purpose: If the user runs the program without specifying
 *          the maximum number of sets, a message gets
 *          printed to tell the user how to start the program
 *
 * In args: prog_name[]: This is argv[0] 
 *
 * Out args: None
 * Return val: None
 *
 ********************************************************/
void Usage(char prog_name[]) {
    fprintf(stderr, "usage: %s <max number of sets>\n", prog_name);
    exit(0);
}






/********************************************************
 * Function: get_value
 * Purpose: Get integer value from stdin
 * Return value: the next int in stdin
 *
 ********************************************************/
int get_value(char cmd_type) {
    int user_val;
   
    printf("Enter a value: ");
    scanf("%d", &user_val);

    return user_val;
}






/********************************************************
 * Function: get_command
 * Purpose: Get a char from stdin
 * Return value: The next char in stdin
 *
 ********************************************************/
char get_command() {
    char user_input;
    
    printf("Enter a char (m, e, u, i, s, n, p, d, a, q): ");
    scanf(" %c", &user_input);
    return user_input;
}






/********************************************************
 * Function: Print
 * Purpose: Print out the set starting at set_head_p and
 *          its corresponding position in array set_int
 *
 * Input args: set_head_p: start of the set
 *             set_int: sets position in the set array
 *
 * Return val: None
 *
 ********************************************************/
void Print(elt_node_t* set_head_p, int set_int) {    
    elt_node_t *curr_p = set_head_p;
    
    printf("Set at pos %d: ", set_int);
    while (curr_p != NULL) {
        printf("%d ", curr_p -> elt);
        curr_p = curr_p -> next_elt_p;
    }
    printf("\n");
}






/********************************************************
 * Function: new_elt_node
 * Purpose: Creates a new element node and appends it on
 *          tail of the set 
 *
 * Input args: val: new value to be appended
 * In/out args: head_pp: pointer to the head of the set
 *              tail_pp: pointer to the tail of the set
 *
 ********************************************************/
void new_elt_node(elt_node_t **head_pp, elt_node_t **tail_pp, int val) {
    elt_node_t *temp_p = malloc(sizeof(elt_node_t));
     
    temp_p -> elt = val;
    temp_p -> next_elt_p = NULL;
    
    if (*head_pp == NULL) {
        *head_pp = temp_p;
        *tail_pp = temp_p;
    }
    else {
        (*tail_pp) -> next_elt_p = temp_p;
        *tail_pp = temp_p;
    }
}






/********************************************************
 * Function: Member
 * Purpose: checks if val is in the set set_i_p
 * Input args: set_i_p: pointer to the head of set at
 *             position i in the array
 *             val: the value to search for in the set
 * 
 * Return value: An int 1 if val is in the set, 0 else.
 *
 ********************************************************/
int Member(elt_node_t *set_i_p, int val) {
    elt_node_t *curr_p = set_i_p;

    while (curr_p != NULL) {
        if (curr_p -> elt == val) {
            return 1;
        }
        curr_p = curr_p -> next_elt_p;
    }
    return 0;
}






/********************************************************
 * Function: Union
 * Purpose: Form the union of two sets
 * Input args: set_i_p, set_j_p
 * Return value: pointer to the union of the two sets
 *
 * Note: Assumes that the sets are sorted in increasing
 *       order of positive ints
 *       i and j represents one of the sets
 *       in the range 0 to MAX_SETS - 1
 *
 ********************************************************/
elt_node_t* Union(elt_node_t *set_i_p, elt_node_t *set_j_p) {
    elt_node_t *curr1_p = set_i_p, *curr2_p = set_j_p;
    elt_node_t *new_head_p = NULL, *new_tail_p = NULL;
    
    while (curr1_p != NULL && curr2_p != NULL) {
        if (curr1_p -> elt == curr2_p -> elt) {
            new_elt_node(&new_head_p, &new_tail_p, curr1_p -> elt);
            curr1_p = curr1_p -> next_elt_p;
            curr2_p = curr2_p -> next_elt_p;         
        }
        else if (curr1_p -> elt < curr2_p -> elt) {
            new_elt_node(&new_head_p, &new_tail_p, curr1_p -> elt);
            curr1_p = curr1_p -> next_elt_p;            
        }
        /* curr1_p -> elt > curr2_p -> elt */
        else {
            new_elt_node(&new_head_p, &new_tail_p, curr2_p -> elt);
            curr2_p = curr2_p -> next_elt_p;
        }       
    }

    /* All elements left belong to the union */
    while(curr1_p != NULL) {
        new_elt_node(&new_head_p, &new_tail_p, curr1_p -> elt);        
        curr1_p = curr1_p -> next_elt_p;        
    }

    while (curr2_p != NULL) {
        new_elt_node(&new_head_p, &new_tail_p, curr2_p -> elt);
        curr2_p = curr2_p -> next_elt_p;
    }
    return new_head_p;
}






/********************************************************
 * Function: Intersection
 * Purpose: Form the intersection of two sets
 * Input args: set_i_p, set_j_p
 * Return value: pointer to the intersection of the two sets
 *
 * Note: Assumes that the sets are sorted in increasing
 *       order of positive ints
 *       i and j represents one of the sets
 *       in the range 0 to MAX_SETS - 1
 *
 ********************************************************/
elt_node_t* Intersection(elt_node_t *set_i_p, elt_node_t *set_j_p) {
    elt_node_t *curr1_p = set_i_p, *curr2_p = set_j_p;
    elt_node_t *new_head_p = NULL, *new_tail_p = NULL;
    
    while (curr1_p != NULL && curr2_p != NULL) {
        if (curr1_p -> elt == curr2_p -> elt) {
            new_elt_node(&new_head_p, &new_tail_p, curr1_p -> elt);
            curr1_p = curr1_p -> next_elt_p;
            curr2_p = curr2_p -> next_elt_p;
        }
        else if (curr1_p -> elt < curr2_p -> elt) {
            curr1_p = curr1_p -> next_elt_p;

        }
        /* curr1_p -> elt > curr2_p -> elt */
        else {            
            curr2_p = curr2_p -> next_elt_p;
        }
    }
    return new_head_p;
}






/********************************************************
 * Function: Equal
 * Purpose:  Determine whether two sets are equal or not
 * Input args:   set_i_p, set_j_p
 * Return value: an int 1 if the sets are equal and 0 
 *               if they're not 
 *
 * Note: Assumes that the sets are sorted in increasing
 *       order of positive ints
 *       i and j represents one of the sets
 *       in the range 0 to MAX_SETS - 1
 *
 ********************************************************/
int Equal(elt_node_t *set_i_p, elt_node_t *set_j_p) {
    int equal = 0;
    elt_node_t *curr1_p = set_i_p;
    elt_node_t *curr2_p = set_j_p;

    while (curr1_p != NULL && curr2_p != NULL) {
        if (curr1_p -> elt != curr2_p -> elt) {           
            return equal;
        }
        curr1_p = curr1_p -> next_elt_p;
        curr2_p = curr2_p -> next_elt_p;
    }
    /* The sets are equal if both sets have been traversed */
    if (curr1_p == NULL && curr2_p == NULL) {
        equal = 1;
    }
    return equal;
}






/********************************************************
 * Function: Set_difference
 * Purpose:  Form the set difference between two sets
 * Input args: set_i_p: pointer to the set i
 *             set_j_p: pointer to the set j
 * Return value: pointer to the set difference of the two sets
 *
 * Note: Assumes that the sets are sorted in increasing
 *       order of positive ints.
 *       i and j represents one of the sets
 *       in the range 0 to MAX_SETS - 1
 *
 ********************************************************/
elt_node_t* Set_difference(elt_node_t *set_i_p, elt_node_t *set_j_p) {
    elt_node_t *new_head_p = NULL, *new_tail_p = NULL;
    elt_node_t *curr1_p = set_i_p, *curr2_p = set_j_p;

    while (curr1_p != NULL && curr2_p != NULL) {
        if (curr1_p -> elt < curr2_p -> elt) {
            new_elt_node(&new_head_p, &new_tail_p, curr1_p -> elt);
            curr1_p = curr1_p -> next_elt_p;
        }
        else if (curr1_p -> elt > curr2_p -> elt) {
            curr2_p = curr2_p -> next_elt_p;
        }
        /* curr1_p -> elt == curr2_p -> elt */
        else {
            curr1_p = curr1_p -> next_elt_p;
            curr2_p = curr2_p -> next_elt_p;
        }
    }

    /* Add what's left in the set i since there are no more elements in set j */
    while (curr1_p != NULL) {
        new_elt_node(&new_head_p, &new_tail_p, curr1_p -> elt);
        curr1_p = curr1_p -> next_elt_p;
    }
    return new_head_p; 
}






/********************************************************
 * Function: Delete
 * Purpose:  Delete a set
 * In/out args: head_pp: pointer to the head of the set
 * 
 * Note: The head in the set will be NULL after this call
 * 
 ********************************************************/
void Delete(elt_node_t **head_pp) {
    elt_node_t *curr_p = *head_pp;
    elt_node_t *temp_p;

    while (curr_p != NULL) {
        temp_p = curr_p;
        curr_p = curr_p -> next_elt_p;
        free(temp_p);
    }
    *head_pp = NULL;
}






/********************************************************
 * Function:    Delete_all
 * Purpose:     Delete all the sets
 * Input args:  MAX_SETS: number of sets to delete
 * In/out args: head_pp: pointer to the head of the set 
 *
 * Note: head_pp should point to the pointer to the first
 *       set when making this call, the set at position 0
 *       (&sets_pp[0]) in order to not go outside array boundaries      
 *      
 *      
 * 
 ********************************************************/
void Delete_all(elt_node_t **head_pp, int MAX_SETS) {  
    int i;
    
    for (i = 0; i < MAX_SETS; i++) {
        Delete(head_pp + i);       
    }
}






/********************************************************
 * Function: get_subscript
 * Purpose:  get a subscript int from stdin that specifies
 *           which set to work with
 *         
 * Input args: MAX_SETS: the maximum number of sets
 * 
 * Return value: the next int in stdin
 *
 ********************************************************/
int get_subscript(int MAX_SETS) {
    int set_int;

    printf("Enter a subscript (0 to %d)\n", MAX_SETS - 1);
    scanf("%d", &set_int);
    
    return set_int;
}
