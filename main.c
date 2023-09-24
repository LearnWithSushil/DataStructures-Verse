/******************************************************************************
*******************************************************************************
**************************** DataStructures Verse *****************************
*******************************************************************************
*******************************************************************************
*********** Developed By : Sushil Kumar ***************************************
*******************************************************************************
*******************************************************************************
********** This Program deals with different Data Structures        ***********
**********   1. Queue implemented with Array                        ***********
**********   2. Queue implemented with Linked list                  ***********
**********   3. Sorted List Implemented using a singly linked List  ***********
**********   4. BST implemented                                     ***********
*******************************************************************************
*******************************************************************************
*******************************************************************************
*** Description : This program takes input from the user for the next *********
*** Data Structure operation. Gets the elements from the user too, in *********
*** the form of direct input or a file with inputs. This is done in a *********
*** loop, till the user decides to Exit from the program, by choosing *********
*** option 16. The Data structure operations supported are Insert /   *********
*** ENQUEUE, Delete / DEQUEUE, Find and inorder traversal for BST.    *********
*******************************************************************************
*******************************************************************************
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h>
#include <errno.h>
#include <string.h>
#include <getopt.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <string.h>


// A linked list Element to store a queue entry
struct ListElementType
{
  int Value;
  struct ListElementType *Next;
};

// The queue, front stores the front node of the Linked List
// rear stores the last node of the Linked List
struct Queue_List_Type
{
  struct ListElementType *Front, *Rear;
};

/**************************************************************************************
************************ Function Declaration Section Starts **************************
***************************************************************************************/

// Function definitions related to Queue implemented using Array
int Build_Queue_Array_From_File (int Queue_Array[], int Rear_Position,
				 char File_Name[]);
int ENQUEUE_Element_Array (int Queue_Array[], int Rear_Position,
			   int New_Element_Value);
int DEQUEUE_Element_Array (int Queue_Array[], int Rear_Position,
			   int Front_Position);
bool Search_Element_Array (int Queue_Array[], int Rear_Position,
			   int New_Element_Value);
void Display_Element_Array (int Queue_Array[], int Rear_Position);

// Function definitions related to Queue implemented using Linked List
// Front stores the first element in the Queue, rear stores the last node of the Queue
void Build_Queue_From_File (struct Queue_List_Type *Queue_List,
			    char File_Name[]);
void ENQUEUE_Element (struct Queue_List_Type *Queue_List,
		      int New_Element_Value);
void DEQUEUE_Element (struct Queue_List_Type *Queue_List);
bool Search_Element (struct Queue_List_Type *Queue_List,
		     int New_Element_Value);
void Display_Elements (struct Queue_List_Type *Queue_List);

// Sorted List Handling Related Function Definitions
// Sorted List has a List_Head Node, this is implemented a singly linked_list
struct ListElementType *Build_SL_From_File (struct ListElementType *List_Head,
					    char File_Name[]);
struct ListElementType *Insert_Element_SL (struct ListElementType *List_Head,
					   int New_Element_Value);
struct ListElementType *Delete_Element_SL (struct ListElementType *List_Head,
					   int Element_Value);
bool Find_Element_SL (struct ListElementType *List_Head,
		      int New_Element_Value);
void Display_Elements_SL (struct ListElementType *List_Head);

/* 
Takes a string as input
Returns true if it is a number else false
If Null, then returns false
If it is a decimal with '.', still returns false
*/
bool
isIntegerNumber (char *StringNumber)
{
  int i = 0;			// Temp variable for the 'For' loop
  bool IsNumber = false;	// Boolean variable, to store 'true' if it is a number

  if (StringNumber[0] == '-')
    {				// If negative number, move to next character
      i++;
    }

  for (; StringNumber[i] != '\0'; i++)
    {				// Go till the end of the string, reach each character
      if (StringNumber[i] == '.')
	{			// If it has a '.' decimal, as part of the string
	  IsNumber = false;	// Return 'false' as this is not an integer number
	  break;		// Exit the for loop
	}
      if (isdigit (StringNumber[i]) == false)
	{			// Is this character is a proper digit ?
	  IsNumber = false;	// If not a digit, not a number
	  break;		// Exit the loop
	}
      else
	{
	  IsNumber = true;	// If this is a digit, continue
	}
    }
  return IsNumber;		// Return true or false, based on our result
}

/***************************BST Functions starts**************************************/
//Function definitions - start
struct node *newNode (int item);
struct node *insert (struct node *node, int key);
void free_bst (struct node *root);
void inorder (struct node *root);
struct node *minValueNode (struct node *node);
struct node *deleteNode (struct node *root, int key);
struct node *Build_BST_From_File (struct node *root, char File_Name[]);
void Find_operation_time_for_different_data_Structures ();
//Function definition - ends

//BST data structures
struct node
{
  int key;
  struct node *left, *right;
};

// A utility function to create a new BST node
struct node *
newNode (int item)
{
  struct node *temp = (struct node *) malloc (sizeof (struct node));
  temp->key = item;
  temp->left = temp->right = NULL;
  return temp;
}

// A utility function to insert
// a new node with given key in BST
struct node *
insert (struct node *node, int key)
{
  // If the tree is empty, return a new node
  if (node == NULL)
    return newNode (key);

  // Otherwise, recur down the tree
  if (key < node->key)
    node->left = insert (node->left, key);
  else if (key > node->key)
    node->right = insert (node->right, key);

  // Return the (unchanged) node pointer
  return node;
}

void
free_bst (struct node *root)
{
  if (root != NULL)
    {
      free_bst (root->left);
      free (root);
      free_bst (root->right);
    }
}

// A utility function to do inorder traversal of BST
void
inorder (struct node *root)
{
  if (root != NULL)
    {
      inorder (root->left);
      printf ("%d ", root->key);
      inorder (root->right);
    }
}

/* Given a non-empty binary search
   tree, return the node
   with minimum key value found in
   that tree. Note that the
   entire tree does not need to be searched. */
struct node *
minValueNode (struct node *node)
{
  struct node *current = node;

  /* loop down to find the leftmost leaf */
  while (current && current->left != NULL)
    current = current->left;

  return current;
}

/* Given a binary search tree
   and a key, this function
   deletes the key and
   returns the new root */
struct node *
deleteNode (struct node *root, int key)
{
  // base case
  if (root == NULL)
    return root;

  // If the key to be deleted
  // is smaller than the root's
  // key, then it lies in left subtree
  if (key < root->key)
    root->left = deleteNode (root->left, key);

  // If the key to be deleted
  // is greater than the root's
  // key, then it lies in right subtree
  else if (key > root->key)
    root->right = deleteNode (root->right, key);

  // if key is same as root's key,
  // then This is the node
  // to be deleted
  else
    {
      // node with only one child or no child
      if (root->left == NULL)
	{
	  struct node *temp = root->right;
	  free (root);
	  return temp;
	}
      else if (root->right == NULL)
	{
	  struct node *temp = root->left;
	  free (root);
	  return temp;
	}

      // node with two children:
      // Get the inorder successor
      // (smallest in the right subtree)
      struct node *temp = minValueNode (root->right);

      // Copy the inorder
      // successor's content to this node
      root->key = temp->key;

      // Delete the inorder successor
      root->right = deleteNode (root->right, temp->key);
    }
  return root;
}

// C function to search a given key in a given BST
struct node *
search (struct node *root, int key)
{
  // Base Cases: root is null or key is present at root
  if (root == NULL || root->key == key)
    return root;

  // Key is greater than root's key
  if (root->key < key)
    return search (root->right, key);

  // Key is smaller than root's key
  return search (root->left, key);
}

struct node *
Build_BST_From_File (struct node *root, char File_Name[])
{
  int New_Element_Value = 0;
  char New_Word[250];
  FILE *File_Pointer;

  if (File_Pointer = fopen (File_Name, "r"))
    {
      if (strstr (File_Name, ".csv"))
	{			// Check if it is a '.csv' file
	  printf ("\n This is a .csv File\n");
	  while (fscanf (File_Pointer, "%d,", &New_Element_Value) == 1)
	    {			// Read each integer from the file
	      root = insert (root, New_Element_Value);
	    }
	}
      else
	{
	  printf ("\n This is a .txt File\n");
	  while (fscanf (File_Pointer, "%1023s ", New_Word) == 1)
	    {
	      New_Element_Value = atoi (New_Word);
	      root = insert (root, New_Element_Value);
	    }
	}
      fclose (File_Pointer);
    }
  else
    {
      printf ("\n No Such File Exist \n");
    }
  return root;
}

void
Find_operation_time_for_different_data_Structures ()
{
  int array[10] =
    { 5268, 6389, 3621, 8879, 6961, 4282, 2258, 1732, 0576, 5938 };
  int Queue_Array[1000];
  int User_Input_Element = 0, Queue_Rear_Position = -1, Queue_Front_Position =
    0;
  struct ListElementType *List_Head = NULL;
  int i = 0;
  double total_time_BST = 0, total_time_SL = 0, total_time_Array_Q =
    0, total_time_linked_list = 0;
  struct node *root = NULL;
  clock_t t;
  printf ("=================================================\n");
  for (i = 0; i < 10; i++)
    {
      t = clock ();
      insert (root, array[i]);
      t = clock () - t;
      total_time_BST = total_time_BST + ((double) t) / CLOCKS_PER_SEC;
    }
  printf ("Average Insertion time in BST: %lf\n", total_time_BST);
  total_time_BST = 0;
  for (i = 0; i < 10; i++)
    {
      t = clock ();
      search (root, array[i]);
      t = clock () - t;
      total_time_BST = total_time_BST + ((double) t) / CLOCKS_PER_SEC;
    }
  printf ("Average Searching time in BST: %lf\n", total_time_BST);
  total_time_BST = 0;
  for (i = 0; i < 10; i++)
    {
      t = clock ();
      deleteNode (root, array[i]);
      t = clock () - t;
      total_time_BST = total_time_BST + ((double) t) / CLOCKS_PER_SEC;
    }
  printf ("Average Deletion time in BST: %lf\n", total_time_BST);
  total_time_BST = 0;
  printf ("=================================================\n");
  for (i = 0; i < 10; i++)
    {
      t = clock ();
      Queue_Rear_Position =
	ENQUEUE_Element_Array (Queue_Array, Queue_Rear_Position, array[i]);
      t = clock () - t;
      total_time_Array_Q = total_time_Array_Q + ((double) t) / CLOCKS_PER_SEC;
    }
  printf ("Average Insertion time in QUEUE: %lf\n", total_time_Array_Q);
  total_time_Array_Q = 0;
  for (i = 0; i < 10; i++)
    {
      t = clock ();
      Queue_Rear_Position =
	DEQUEUE_Element_Array (Queue_Array, Queue_Rear_Position,
			       Queue_Front_Position);
      t = clock () - t;
      total_time_Array_Q = total_time_Array_Q + ((double) t) / CLOCKS_PER_SEC;
    }
  printf ("Average Deletion time in QUEUE: %lf\n", total_time_Array_Q);
  printf ("=================================================\n");
  for (i = 0; i < 10; i++)
    {
      t = clock ();
      List_Head = Insert_Element_SL (List_Head, array[i]);
      t = clock () - t;
      total_time_linked_list =
	total_time_linked_list + ((double) t) / CLOCKS_PER_SEC;
    }
  printf ("Average Insertion time for Sorted List: %lf\n",
	  total_time_linked_list);
  total_time_linked_list = 0;
  for (i = 0; i < 10; i++)
    {
      t = clock ();
      Find_Element_SL (List_Head, array[i]);
      t = clock () - t;
      total_time_linked_list =
	total_time_linked_list + ((double) t) / CLOCKS_PER_SEC;
    }
  printf ("Average Searching time for Sorted List: %lf\n",
	  total_time_linked_list);
  total_time_linked_list = 0;
  for (i = 0; i < 10; i++)
    {
      t = clock ();
      List_Head = Delete_Element_SL (List_Head, array[i]);
      t = clock () - t;
      total_time_linked_list =
	total_time_linked_list + ((double) t) / CLOCKS_PER_SEC;
    }
  printf ("Average Deletion time for Sorted List: %lf\n",
	  total_time_linked_list);
  total_time_linked_list = 0;
  printf ("=================================================\n");
}

/***************************BST Functions Ends****************************************/

/**************************************************************************************
************ Main funciton has the key User Options, about the next action ************
***************************************************************************************
* Step-1 : Get User Input, on the next data structure operation
* Step-2 : Get User input, either 'File Name' or 'Element Value', based on the user option
* Step-3 : Perform the user requested operation
* Step-4 : Continue in a while loop, till the user chooses the exit option '16'
* *************************************************************************************
***************************************************************************************/
int
main ()
{
  /* Variable Declarations */
  int User_Option = 0;		// For the user to choose his next Option
  int User_Input_Element = 0, Queue_Rear_Position = -1, Queue_Front_Position = 0;	// User Input Element, Array Queue Rear and Front position
  char File_Name[30], User_Input_String[30];	// String to get user input for the file name
  int Queue_Array[1000];	// Queue implemented with Array
  struct Queue_List_Type *Queue_List = NULL;	// Queue using Linked list
  struct ListElementType *List_Head = NULL;	// Sorted List
  int item = 0;			// Used for BST
  struct node *root = NULL;
  struct node *search_node = NULL;
  char file_path[1024] = { 0 };
  bool Present = false;		// Boolean variable to identify if the element is present in the list

  /* Create and initialize the Queue with linked list */
  Queue_List = (struct Queue_List_Type *) malloc (sizeof (struct Queue_List_Type));	// Create the Queue using list
  Queue_List->Front = Queue_List->Rear = NULL;	// Initialize Front and Rear to 'NULL'

  printf ("\nThe Program has Started\n");

  while (User_Option != 16)	// Continue the execution in loop, till the Exit option is chosen by the user
    {
      /* Display all the available options to the user */
      printf
	("\n 1. Input into Array Queue from File (Multiple elements).\n2. Input into Array Queue from command line (Single Element).\n3. Remove element from Array Queue (Single Element).\n4. Input into List Queue from File.\n5. Input into List Queue from command line.\n6. Remove element from List Queue.\n7. Input into Sorted List from File.\n8. Input into Sorted List from command line.\n9. Find element in Sorted List.\n10. Remove element in Sorted List.\n11: Input into BST from File.\n12: Input into BST from command line.\n13: Find element in BST.\n14: Remove element From BST.\n15: Print BST in order.\n16: Quit\n");
      printf ("Enter your choice : ");
      scanf ("%d", &User_Option);
      switch (User_Option)
	{
	case 1:
	  printf
	    ("\n1. Input into Array Queue from File (Multiple elements).\n");
	  printf ("\n Enter the File Name :\n");
	  scanf ("%s", File_Name);
	  Queue_Rear_Position = Build_Queue_Array_From_File (Queue_Array, Queue_Rear_Position, File_Name);	// Call the ENQUEUE function for all the elements in a file

	  break;
	case 2:
	  printf
	    ("\n2. Input into Array Queue from command line (Single Element).\n");
	  printf ("\nEnter the element :\n");
	  scanf ("%s", User_Input_String);
	  if (isIntegerNumber (User_Input_String))
	    {
	      User_Input_Element = atoi (User_Input_String);
	      Queue_Rear_Position = ENQUEUE_Element_Array (Queue_Array, Queue_Rear_Position, User_Input_Element);	// Call the ENQUEUE function for the element
	    }
	  else
	    {
	      printf ("\nInvalid input. Please enter an integer.\n");
	    }
	  break;
	case 3:
	  printf ("\n3. Remove element from Array Queue (Single Element).\n");
	  Queue_Rear_Position = DEQUEUE_Element_Array (Queue_Array, Queue_Rear_Position, Queue_Front_Position);	// Call the DEQUEUE function
	  break;
	case 4:
	  printf ("\n4. Input into List Queue from File.\n");
	  printf ("\n Enter the File Name :\n");
	  /* File_Name = Get_File_Name_From_User (); */
	  scanf ("%s", File_Name);
	  Build_Queue_From_File (Queue_List, File_Name);	// Call the ENQUEUE function for all the elements in a file
	  break;
	case 5:
	  printf ("\n5. Input into List Queue from command line.\n");
	  printf ("\n Enter the element :\n");
	  scanf ("%s", User_Input_String);
	  if (isIntegerNumber (User_Input_String))
	    {
	      User_Input_Element = atoi (User_Input_String);
	      ENQUEUE_Element (Queue_List, User_Input_Element);	// Call the ENQUEUE function for the element
	    }
	  else
	    {
	      printf ("\nInvalid input. Please enter an integer.\n");
	    }
	  break;
	case 6:
	  printf ("\n6. Remove element from List Queue.\n");
	  DEQUEUE_Element (Queue_List);	// Call the DEQUEUE function to remove the front element
	  break;
	case 7:
	  printf ("7. Input into Sorted List from File.\n");
	  printf ("\n Enter the File Name :\n");
	  /* File_Name = Get_File_Name_From_User (); */
	  scanf ("%s", File_Name);
	  List_Head = Build_SL_From_File (List_Head, File_Name);	// Call the Insert function for all the elements in a file, for insertion in to a sorted list
	  break;
	case 8:
	  printf ("8. Input into Sorted List from command line.\n");
	  printf ("\n Enter the element :\n");
	  scanf ("%s", User_Input_String);
	  if (isIntegerNumber (User_Input_String))
	    {
	      User_Input_Element = atoi (User_Input_String);
	      List_Head = Insert_Element_SL (List_Head, User_Input_Element);	// Call the Insert function for the element, for insertion in to a sorted list
	    }
	  else
	    {
	      printf ("\nInvalid input. Please enter an integer.\n");
	    }
	  break;
	case 9:
	  printf ("9. Find element in Sorted List.\n");
	  printf ("\n Enter the element :\n");
	  scanf ("%s", User_Input_String);
	  if (isIntegerNumber (User_Input_String))
	    {
	      User_Input_Element = atoi (User_Input_String);
	      Present = Find_Element_SL (List_Head, User_Input_Element);	// Call the Find function for the element, in the given sorted list
	    }
	  else
	    {
	      printf ("\nInvalid input. Please enter an integer.\n");
	    }
	  break;
	case 10:
	  printf ("10. Remove element in Sorted List.\n");
	  printf ("\n Enter the element :\n");
	  scanf ("%s", User_Input_String);
	  if (isIntegerNumber (User_Input_String))
	    {
	      User_Input_Element = atoi (User_Input_String);
	      List_Head = Delete_Element_SL (List_Head, User_Input_Element);	// Call the Delete function for the element, from the given sorted list
	    }
	  else
	    {
	      printf ("\nInvalid input. Please enter an integer.\n");
	    }
	  break;
	case 11:
	  printf ("11: Input into BST from File.\n");
	  printf ("Please enter the file path : ");
	  scanf ("%s", file_path);
	  root = Build_BST_From_File (root, file_path);
	  break;
	case 12:
	  printf ("12: Input into BST from command line.\n");
	  printf ("Please enter the number : ");
	  scanf ("%d", &item);
	  root = insert (root, item);
	  break;
	case 13:
	  printf ("13: Find element in BST.\n");
	  printf ("Please enter the number : ");
	  scanf ("%d", &item);
	  search_node = search (root, item);
	  if (search_node != NULL)
	    {
	      printf ("Found the element : %d\n", search_node->key);
	      search_node = NULL;
	    }
	  else
	    {
	      printf ("Element not present in BST\n");
	    }
	  break;
	case 14:
	  printf ("14: Remove element From BST.\n");
	  printf ("Please enter the number : ");
	  scanf ("%d", &item);
	  root = deleteNode (root, item);
	  break;
	case 15:
	  printf ("15: Print BST in order.\n");
	  inorder (root);
	  printf ("\n");
	  break;
	case 16:
	  printf ("16: Quit\n");
	  free_bst (root);
	  goto clean_out;
	  break;
	case 17:
	  Display_Element_Array (Queue_Array, Queue_Rear_Position);	// Debug Function to Display the Queue elements, implemented in the Array
	  break;
	case 18:
	  Display_Elements (Queue_List);	// Debug Function to Display the Queue elements implemented using the Linked_List
	  break;
	case 19:
	  Display_Elements_SL (List_Head);	// Debug Function to Display the elements inserted in the Sorted List
	  break;
	case 20:
	  Find_operation_time_for_different_data_Structures ();	// Debug Function to find the time taken for different operations
	  break;
	default:
	  printf ("Please enter correct option\n");	// Display this, if the user enters a wrong option
	  break;
	}
    }
clean_out:
  return 0;
}

/*************************** Main Function Ends **************************************/

/**************************************************************************************
******************* Queue and Sorted List Function Definitions Start ******************
***************************************************************************************/

/* Step 1 : Queue_Array and the Rear_Position are received as input parameters
Step 2 : The File corresponding is opened
Step 3 : Read word by word from the file
Step 4: Convert the word to an integer
Step 5 : Call function “ENQUEUE_Element_Array” for ENQUEUE to the Queue
Step 6 : If this element is ENQUEUE’d, the new ‘Rear_Position’ is returned back from “ENQUEUE_Element_Array” function
Step 7 : Once the complete file is read, close the file
Step 8 : Return the latest ‘Rear_Position’, after adding all the new elements
*/
int Build_Queue_Array_From_File (int Queue_Array[], int Rear_Position, char File_Name[]) {
    // Variable Declarations
	int New_Element_Value = 0; // New Element
	char New_Word[250]; // Word read from the file
    FILE *File_Pointer; // File pointer to open the user given file


    if (File_Pointer = fopen(File_Name,"r")) { // Open the File
        if(strstr(File_Name,".csv")) { // Check if it is a '.csv' file
            printf ("\n This is a .csv File\n");
            while (fscanf(File_Pointer, "%d,", &New_Element_Value) == 1) { // Read each integer from the file
                printf("%d\n", New_Element_Value);
                Rear_Position = ENQUEUE_Element_Array (Queue_Array, Rear_Position, New_Element_Value); // Insert the element in the Queue, in the Rear Position
            }
        } else {
            printf ("\n This is a .txt File\n");
        while ( fscanf(File_Pointer,"%1023s ",New_Word) == 1) { // Read each word till the last word from the file
	        New_Element_Value = atoi(New_Word); // Convert the word to integer
	        Rear_Position = ENQUEUE_Element_Array (Queue_Array, Rear_Position, New_Element_Value); // Insert the element in the Queue, in the Rear Position
        }
        }
        fclose(File_Pointer); // Close the file, after reading all the numbers from the file
    }
    else {
        printf("\n No Such File Exist \n");
    }
    return Rear_Position; // Return the updated new Rear Position, after insertion
}

/*
Step 1 : Queue_Array, the Rear_Position and the Input_Element_Value are received as input parameters
Step 2 : Check whether the element is a valid element
	If not return the current ‘Rear_Position’
Step 3 : Check whether the element is a duplicate
	If yes return the current ‘Rear_Position’
Step 4 : Increment the ‘Rear_Position’
Step 5 : Copy the Input_Element_Value to the new ‘Rear_Position’
Step 6 : Return the new ‘Rear_Position’
*/
int ENQUEUE_Element_Array (int Queue_Array[], int Rear_Position, int New_Element_Value) {
	if (Search_Element_Array(Queue_Array, Rear_Position, New_Element_Value) == false) {
	    //printf("\n New Element : Position %d : %d", Rear_Position, New_Element_Value);
	    Rear_Position++;
	    Queue_Array [Rear_Position] = New_Element_Value;
	} else {
	    printf("\n Duplicate Element \n");
    }
    //printf("Position %d : %d\n", Rear_Position, New_Element_Value);
    return Rear_Position;
}

/*
Step 1 : Queue_Array, the Rear_Position and the Input_Element_Value are received as input parameters
Step 2 : Check whether the Input_Element_Value is a valid element
	If not return the current ‘Rear_Position’
Step 3 : Check whether the element is a duplicate
	If yes return the current ‘Rear_Position’
Step 4 : Decrement the ‘Rear_Position’
Step 5 : Return the new ‘Rear_Position’
*/
int DEQUEUE_Element_Array (int Queue_Array[], int Rear_Position, int Front_Position) {

	if (Rear_Position < Front_Position) { // Check if the Queue is empty
		printf("\n The Queue is Empty \n");
		return Rear_Position;
	}
	//printf("\n Deleted Element : %d \n",Queue_Array[0]);
    for(int i=0;i<Rear_Position;i++){ 
		Queue_Array[i] = Queue_Array[i+1]; // Copy all elements till rear element
	}
	Rear_Position--; // Reduce the Queue size by 1, as one element is deleted

    return Rear_Position; // Return the new Rear Position
}

/*
Step 1 : Queue_Array, the Rear_Position and the Input_Element_Value are received as input parameters
Step 2 : Check whether the element is already present
	If yes return ‘true’
Step 3 : After the complete list is searched, return 'false', as the element is not present
*/
bool Search_Element_Array (int Queue_Array[], int Rear_Position, int New_Element_Value) {
	bool Present = false;
	if (Rear_Position < 0) { // If Rear Position is < 0, that means the Queue is empty 
		printf("\n The Queue is Empty \n");
	}
    for(int i=0;i<=Rear_Position;i++){ // Walk through the whole Queue
		if (Queue_Array [i] == New_Element_Value) { // Check if the 'New Element' is already present in the Queue
			Present = true;
		}
	}
    return Present; // Return the Search result
}

/*
Step 1 : Queue_List Pointer is received as input parameters
Step 2 : Create a Queue_Pointer ‘Display_Element_Pointer’
Step 3 : Assign the address of the current ‘Queue_Front_Pointer’ to the ‘Display_Element_Pointer’
Step 4 : Display the 'Value' from the 'Display_Element_Pointer'
Step 5 : Assign ‘Display_Element_Pointer’, the next Element’s Address
Step 6 : Continue till the last element
*/
void Display_Element_Array (int Queue_Array[], int Rear_Position) {
	if (Rear_Position < 0) { // If Rear Position is < 0, that means the Queue is empty 
		printf("\n The Queue is Empty \n");
	}
    for(int i=0;i<=Rear_Position;i++){ // Walk through the whole Queue
		printf("%d ",Queue_Array [i]); // Display each of the Queue Element
	}
    return;
}

/*
Step 1 : Queue_Rear_Pointer, Queue_Front_Pointer and File_Name are received as input parameters
Step 2 : The corresponding File is opened
Step 3 : Read word by word from the file
Step 4 : Convert the word to an integer
Step 5 : Call function “ENQUEUE_Element” for ENQUEUE to the Queue
Step 6 : If this element is ENQUEUE’d, the new ‘Queue_Rear_Pointer’ is returned back from “ENQUEUE_Element” function
Step 7 : Once the complete file is read, close the file
Step 8 : Return the latest ‘Queue_Rear_Pointer’, after adding all the new elements
*/
void Build_Queue_From_File (struct Queue_List_Type* Queue_List, char File_Name[]) {
	int New_Element_Value = 0; // Variable for the current element
	char New_Word[250]; // Variable for the current string read from the file
    FILE *File_Pointer; // File Pointer for opening the input file
 
    if (File_Pointer = fopen(File_Name,"r")) { // if the file is valid, opened successfully
        if(strstr(File_Name,".csv")) { // Check if it is a '.csv' file
            printf ("\n This is a .csv File\n");
            while (fscanf(File_Pointer, "%d,", &New_Element_Value) == 1) { // Read each integer from the file
                ENQUEUE_Element (Queue_List, New_Element_Value); // Insert the element in to the Queue
            }
        } else {
            printf ("\n This is a .txt File\n");
            while ( fscanf(File_Pointer, "%1023s ",New_Word) == 1) { // Till the last word in the file, continue to read
    	        New_Element_Value = atoi(New_Word); // Convert the number in the word format to integer format
	            ENQUEUE_Element (Queue_List, New_Element_Value); // Insert the element in to the Queue 
            }
        }
        fclose(File_Pointer); // Close the file pointer, after reading
    } else {
        printf("\nNo Such File Exists \n"); // Intimate the user, if the file does not exist
    }
    return;
}

/*
Step 1 : Queue_Rear_Pointer, Queue_Front_Pointer, New_Element_Value are received as input parameters
Step 2 : Create a new_Element_Pointer
Step 3 : Check whether the ‘New_Element_Value’ passed on, is a valid element
	If not, return the current ‘Queue_Rear_Pointer’
Step 4 : Check whether the element is a duplicate
	If yes, return the current ‘Queue_Rear_Pointer’
Step 5 : Create a new ‘Queue_Element’, and assign it’s address to ‘new_Element_Pointer’
Step 6 : Update the Queue_Rear_Pointer’s ‘next’ as ‘New_Element_Pointer’
Step 7 : Copy the Input_Element_Value to the new_Element ‘value’
Step 8 : Make the New_Element_Pointer’s ‘next’ as ‘NULL’
Step 9 : Return the new ‘New_Element_Pointer’ as the new ‘Queue_Rear_Pointer’
*/
void ENQUEUE_Element (struct Queue_List_Type* Queue_List, int New_Element_Value) {
    struct ListElementType* New_Queue_Element; // New Queue Element Pointer declaration

	if (Search_Element(Queue_List, New_Element_Value) == false) { // Only if the element is not present already, move forward with insertion
	    New_Queue_Element = (struct ListElementType*)malloc(sizeof(struct ListElementType)); // Create structure to store the new element
        New_Queue_Element->Next = NULL; // For now, make the next to be 'NULL'
	    New_Queue_Element->Value = New_Element_Value; // Copy the new input value from the user
	    
	    if (Queue_List ->Rear != NULL) { // If the Queue is not empty, insert the element in the end of the Queue
	        Queue_List ->Rear->Next = New_Queue_Element;
	    }
        Queue_List->Rear = New_Queue_Element; // Update the Rear pointer to the latest element inserted
        if (Queue_List->Front == NULL) { // If the Queue was empty, make front to point to this new element
            Queue_List->Front = New_Queue_Element;
        }
	} else { // If this is a duplicate element, intimate the user; do not insert into the Queue
	    printf("\n Duplicate Element \n");
	}
    return;
}

/*
Step 1 : Queue_List_Pointer is received as input parameters
Step 2 : Create a Queue_Pointer ‘Deleted_Element_Pointer’
Step 3 : Assign the address of the current ‘Queue_Front_Pointer’ to the ‘Deleted_Element_Pointer’
Step 4 : Assign ‘Queue_Front_Pointer’, the next Element’s Address
Step 5 : Free the memory assigned to the ‘Deleted_Element_Pointer’
Step 6 : Return the new ‘Queue_Front_Pointer’
*/
void DEQUEUE_Element (struct Queue_List_Type* Queue_List) {
    struct ListElementType* Deleted_Element; // Queue element Pointer declaration
    
    if (Queue_List->Front != NULL) { // if the Queue is not empty, proceed with deletion of the first element
        Deleted_Element = Queue_List->Front; // Copy the address of the first element
        //printf("\nDeleted Element : %d\n", Deleted_Element->Value);
	    Queue_List->Front = Queue_List->Front->Next; // The front is now updated to the next element, as this will be the new first element
	    if (Queue_List->Front == NULL) { // If the Queue becomes empty, copy the same to the Rear, as the old Rear is removed from the Queue now
	       Queue_List->Rear = NULL;
	    }
	    free(Deleted_Element); // Free the memory allocated for the deleted Queue Element
    } else { // Intimate the user, if the Queue is empty
        printf("\nQueue is Empty \n");
    }
    return;
}

/*
Step 1 : Queue and the Input_Element_Value are received as input parameters
Step 2 : Check whether the element is already present
	If yes return ‘true’
Step 3 : After the complete list is searched, return 'false', as the element is not present
*/
bool Search_Element (struct Queue_List_Type* Queue_List,int New_Element_Value) {
	struct ListElementType* Search_Element; // Pointer for the current Queue element
	bool Present=false; // Boolean to store the search result
	
	Search_Element = Queue_List->Front; // Start the search from the first element 'Front'
	while (Search_Element != NULL ) { // Go to each element in the Queue, till the last element
		if (Search_Element->Value == New_Element_Value) { // See if the new element is same as the current element in the Queue
			Present = true; // Mark the element as already present in the Queue
		}
		Search_Element = Search_Element->Next; // Move to the next element in the Queue
	}
	return Present; // Return the search result
}

/*
Step 1 : Queue_List Pointer is received as input parameters
Step 2 : Create a Queue_Pointer ‘Display_Element_Pointer’
Step 3 : Assign the address of the current ‘Queue_Front_Pointer’ to the ‘Display_Element_Pointer’
Step 4 : Display the 'Value' from the 'Display_Element_Pointer'
Step 5 : Assign ‘Display_Element_Pointer’, the next Element’s Address
Step 6 : Continue till the last element
*/
void Display_Elements (struct Queue_List_Type* Queue_List) {
	struct ListElementType* Display_Element; // Pointer declaration for the current element to be displayed
	
	Display_Element = Queue_List->Front; // Start the search from the first element 'Front'
	if (Queue_List->Front == NULL) { // if the Queue is empty, intimate the user
	    printf("\n Queue is Empty\n");
	}
	while (Display_Element != NULL ) { // Go to each element in the Queue, till the last element
		printf("%d ",Display_Element->Value); // Display the current element
		Display_Element = Display_Element->Next; // Move to the next element in the Queue
	}
	return;
}

/*
Step 1 : List_Head_Pointer and File_Name are received as input parameters
Step 2 : The corresponding File is opened
Step 3 : Read word by word from the file
Step 4 : Convert the word to an integer
Step 5 : Call function “Insert_Element” to Insert the new element to the 'Sorted List'
Step 6 : If this element is inserted and the first element of the 'Sorted List' changes,
            the new ‘List Head’ is returned back from the “Insert_Element” function
Step 7 : Once the complete file is read, close the file
Step 8 : Return the latest ‘List Head’ Pointer, after adding all the new elements
*/
struct ListElementType* Build_SL_From_File (struct ListElementType* List_Head, char File_Name[]) {
	int New_Element_Value = 0; // To hold the current element value
	char New_Word[250]; // To hold the current word read from the file
    FILE *File_Pointer; // File pointer to open the file
 
    if (File_Pointer = fopen(File_Name,"r")) { // If the file is valid and opened successfully, move forward with the next steps
        if(strstr(File_Name,".csv")) { // Check if it is a '.csv' file
            printf ("\n This is a .csv File\n");
            while (fscanf(File_Pointer, "%d,", &New_Element_Value) == 1) { // Read each integer from the file
                List_Head = Insert_Element_SL (List_Head, New_Element_Value); // Insert the new element in to the 'Sorted List'
            }
        } else {
            printf ("\n This is a .txt File\n");
            while ( fscanf(File_Pointer, "%1023s ",New_Word) == 1) { // If the current word is read successfully
    	        New_Element_Value = atoi(New_Word); // Convert the word to an integer
	            List_Head = Insert_Element_SL (List_Head, New_Element_Value); // Insert the new element in to the 'Sorted List'
            }
        }
        fclose(File_Pointer); // Close the file after completion of reading
    } else { // Intimate the user, if the given file doesn't exist or not able to open it
        printf("\nNo Such File Exists \n");
    }
    return List_Head; // Return the new 'List_Head'
}

/*
Step 1 : List_Head Pointer, New_Element_Value are received as input parameters
Step 2 : Create a new_Element; allocate memory
Step 3 : If the list is empty, consider this as the first element
Step 4 : If the new element is smaller than the first element, make new element as the first element
Step 5 : Check whether the new element is a duplicate
	If yes, do not add the new element, return the current ‘List Head’
	If your current element from the list is smaller than your new element, you know that 
	    "There is no chance of finding your new element, in the list, as this is a sorted list"
	    So, come out of the loop
Step 5 : Create a new ‘Queue_Element’, and assign it’s address to ‘new_Element_Pointer’
Step 6 : Update the Queue_Rear_Pointer’s ‘next’ as ‘New_Element_Pointer’
Step 7 : Copy the Input_Element_Value to the new_Element ‘value’
Step 8 : Make the New_Element_Pointer’s ‘next’ as ‘NULL’
Step 9 : Return the new ‘New_Element_Pointer’ as the new ‘Queue_Rear_Pointer’
*/
struct ListElementType* Insert_Element_SL (struct ListElementType* List_Head, int New_Element_Value) {
    struct ListElementType *New_Element, *Current_Element; // Pointers for the List elements, new element and the current element from the list
	
	New_Element = (struct ListElementType*)malloc(sizeof(struct ListElementType)); // Allocate memory for the new element
    New_Element->Next = NULL; // Temporarily make the next of the new element as 'NULL'
	New_Element->Value = New_Element_Value; // Copy the new element value

	if (List_Head == NULL) { // If the list is empty, consider this as the first element
	    printf("\n First Element \n");
	    List_Head = New_Element;
	    return List_Head; // return the 'List_Head', the new element pointer
	} else if (List_Head->Value > New_Element_Value) { // If the new element is smaller than the first element
	    printf("\n Smaller than the First Element \n");
	    New_Element->Next = List_Head; // Make the List_Head as the next element to the new element
	    return New_Element; // return the 'New Element' as the first element 'List_Head'
	}
	Current_Element = List_Head; // Start from the first element in the list
	while (Current_Element->Next != NULL) { // Till the last element in the list continue
	    if (Current_Element->Value < New_Element_Value) { // If the new element is bigger than the current element in the list, continue
	        // printf("\n New Element %d is bigger than the Current Element %d",New_Element_Value,Current_Element->Value);
	        Current_Element = Current_Element->Next; // Move to the next element
	    } else { // If the new element is smaller than the current element, then you have no chance of find your element in the rest of the 'Sorted List'
	        printf("\n New Element %d is not bigger than the Current Element %d",New_Element_Value,Current_Element->Value);
	        break; // Come out of the Search loop
	    }
	    
	}
	if (Current_Element->Value == New_Element_Value) { // If the element is alreday present, declare it as duplicate
	   printf("\n Duplicate Element : %d \n", New_Element_Value); // Display the duplicate value
	   free (New_Element); // Free the memory allocated, as we are not adding a new element here
	} else if (Current_Element->Value > New_Element_Value) { // If the current element is bigger than the new element
	        printf("\n New Element %d is smaller than the Current Element %d",New_Element_Value,Current_Element->Value);
	        New_Element->Value = Current_Element->Value; // Copy the current element value to the new element
	        Current_Element->Value = New_Element_Value; // Copy the new element value to the current element
	        New_Element->Next = Current_Element->Next; // Make the current element's next element as the 'next element to the new element'
	        Current_Element->Next = New_Element; // Make the new element as the next element to the current element
	} else if (Current_Element->Next == NULL) { // If we are at the end of the list, the new element is the biggest
	        printf("\n New Element %d is the last element. bigger than the Current Element %d",New_Element_Value,Current_Element->Value);
	        Current_Element->Next = New_Element; // Make the element as the last element in the list
	    }
    return List_Head; // Send the new Header element Pointer back
}

/*
Step 1 : List Header pointer and the 'to be deleted' element value are received as input parameters
Step 2 : Create Pointers for the New Head, Current Element and also the previous element (to the current element)
Step 3 : If the list is empty intimate the user
Step 4 : If the first element is to be deleted, Change the 'List_Head' pointer; Free the old Head Node
Step 5 : Search the entire list from first to last, for the element 'to be deleted'
    If you find a current element value to be bigger than the given element value, exit the loop
        as this is a sorted list, you can't find your element post this.
Step 6 : If you found your element
        Update the 'next' pointer in the previous element to the new next element
        delete the element; free the memory
Step 7 : If the element given by the user is not found, intimate the user
Step 8 : Return the updated List_Head pointer
*/
struct ListElementType* Delete_Element_SL (struct ListElementType* List_Head, int Element_Value) {
    struct ListElementType *Current_Element=NULL, *New_Head=NULL, *Previous_Element=NULL; // Pointer Declarations for the First / Header List element, Current and previous List elements
    
    if (List_Head == NULL) { // If the List is empty, intimate the user
        printf("\n List is Empty \n");
	    return List_Head; // return the same NULL
	} else if (List_Head->Value == Element_Value) { // If the element to be deleted is the first element
	    printf("\n Element Identified is the Head Node: %d \n", Element_Value);
	    New_Head = List_Head->Next; // Change the Head Node pointer
	    free (List_Head); // Free the memory allocated to the deleted Head node
	    return New_Head; // return the new head pointer
	}
	Current_Element = List_Head; // Start from the first element
	
	while (Current_Element->Next != NULL) { // Search till the last element in the list
	    if (Current_Element->Value < Element_Value) { // Continue only if the current value is smaller than the element being searched, as this is a sorted list
	        Previous_Element = Current_Element; // Store the Current Element, to the 'Previous Element' pointer
	        Current_Element = Current_Element->Next; // Move to the next element
	    } else { // If the search element is smaller than the current element, exit the loop; as this is a sorted list, no scope of finding this element, after this
	        break;
	    }
	    
	}
	if (Current_Element->Value == Element_Value) { // Wolaah, we found the element to be deleted
	   printf("\n Element Identified : %d \n", Element_Value);
	   Previous_Element->Next = Current_Element->Next; // Update the 'next' pointer in the previous element to the new next element
	   free (Current_Element); // Free the memory allocated to the deleted element
	} else { // Intimate the user, if the element is not found
	        printf("\n Element Not Found : %d \n", Element_Value);
	}
    return List_Head; // return the new Head Node, of the sorted list
}

/*
Step 1 : List Header Pointer and the 'to be Found' element value are received as input parameters
Step 2 : Create Pointer for the Current Element ;
        Create a boolean variable for 'Present' : If the given element is present in the sorted list or not
Step 3 : If the list is empty intimate the user
Step 4 : If the 'to be found' element is the first element return 'true'
Step 5 : Search the entire list from first to last, for the element 'to be deleted'
    If you find a current element value to be bigger than the given element value, exit the loop
        as this is a sorted list, you can't find your element post this.
Step 6 : If you found your element
        Update the 'next' pointer in the previous element to the new next element
        delete the element; free the memory
Step 7 : If the element given by the user is found, intimate the user; if not found, intimate the user as well
Step 8 : Return the result, whether the given element is found in the 'Sorted List' or not
*/
bool Find_Element_SL (struct ListElementType* List_Head,int Element_Value) {
	struct ListElementType* Current_Element=NULL; // Create Pointer for the Current Element
	bool Present=false; // Create a boolean variable for 'Present' : If the given element is present in the sorted list or not
    
    if (List_Head == NULL) { // If the list is empty intimate the user
        printf("\n List is Empty \n");
	    return false;
	} else if (List_Head->Value == Element_Value) { // If the 'to be found' element is the first element return 'true'
	    printf("\n Element Identified is the Head Node: %d \n", Element_Value);
	    return true;
	}
	Current_Element = List_Head; // Start from the first element
	while (Current_Element->Next != NULL) { // Search till the end of the list
	    if (Current_Element->Value < Element_Value) { /*If you find a current element value to be bigger than the given element value, exit the loop
                                                            as this is a sorted list, you can't find your element post this. */
	        Current_Element = Current_Element->Next; // Move to the next element
	    } else { // Come out of the loop, if the current element is bigger than the given element value
	        break;
	    }
	}
	if (Current_Element->Value == Element_Value) { // If the given element value is found, intimate the user
	   printf("\n Element Identified : %d \n", Element_Value);
	   Present=true;
	} else { // If the given element value is not found, intimate the user
	        printf("\n Element Not Found : %d \n", Element_Value);
	        Present=false;
	}
	return Present; // Return the result, whether the element is found in the 'Sorted List' or not
}

/*
Step 1 : List Header Pointer is received as input parameters
Step 2 : Create Pointer for the Current Element
Step 3 : If the list is empty intimate the user
Step 4 : Display the entire list from first to last
*/
void Display_Elements_SL (struct ListElementType* List_Head) {
	struct ListElementType* Display_Element; // Create Pointer for the Current Element to be displayed
	
	Display_Element = List_Head; // Start from the first element
	if (List_Head == NULL) { // If the list is empty intimate the user
	    printf("\n List is Empty\n");
	}
	while (Display_Element != NULL ) { // Display the entire list from first to last
		printf("%d ",Display_Element->Value); // Display the element
		Display_Element = Display_Element->Next; // Move to the next element
	}
	return;
}

/**************************************************************************************
********************************** End of the Program *********************************
***************************************************************************************/
