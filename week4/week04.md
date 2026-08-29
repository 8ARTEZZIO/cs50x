## Memory

---

**Hexadecimal**

1. RGB is just a proportion of red, green and blue.

   ![](https://cs50.harvard.edu/x/notes/4/cs50Week4Slide016.png)
   
   Notice how the amount of those ingredients changes the main colour.

2. As shown in the image above the RGB value can be represented in hexadecimal
   as well (255 is represented as FF).

   ```0 1 2 3 4 5 6 7 8 9 A B C D E F```

   Notice that F represents 15.

3. Hexadecimal is also known as *base-16*.
4. `0` = `00`
   `1` = `01`
   `9` = `09`
   `10` = `0A`
   `15` = `0F`
   `16` = `10`
   `255` = `FF`
5. Hexadecimal allows to represent numbers using fewer digits.

---

**Memory**

1. Below is the representation of a block of a memory.

   ![](https://cs50.harvard.edu/x/notes/4/cs50Week4Slide066.png)

   By convention, `0x` begins all hexadecimal numbers.

---

**Pointers**

1. The C language has two powerful operators that relate to memory:
   ```
    `&` Provides the address of something stored in memory.
    `*` Instructs the compiler to go to a location in memory.
   ```
2. We can leverage this knowledge by modifying our code as follows:
   ```addresses.c
    // Prints an integer's address

    #include <stdio.h>

    int main(void)
    {
        int n = 50;
        printf("%p\n", &n);
    }
   ```
   To illustrate the use of `*` operator, consider the following:
   ```pointer.c
    // Stores and prints an integer's address

    #include <stdio.h>

    int main(void)
    {
        int n = 50;
        int *p = &n;
        printf("%p\n", p);
    }
   ```

3. Pointer is usually stored as an 8-byte value.

---

**Strings**

1. Modify your code as follows:
   ```
   // Prints a string
   
   #include <cs50.h>
   #include <stdio.h>
   
   int main(void)
   {
       string s = "HI!";
       printf("%s\n", s);
   }
   ```
   Notice that a string `s` is printed.

2. Recall that a string is simply an array of characters.
   `string s = "HI!"1` can be represented as follows:
   ![](https://cs50.harvard.edu/x/notes/4/cs50Week4Slide085.png)

3. `s` is just a pointing towards the beginning of the string.
4. Modify your code as follows:
   ```
   // Prints a string's address as well the addresses of its chars
   
   #include <cs50.h>
   #include <stdio.h>
   
   int main(void)
   {
       string s = "HI!";
       printf("%p\n", s);
       printf("%p\n", &s[0]);
       printf("%p\n", &s[1]);
       printf("%p\n", &s[2]);
       printf("%p\n", &s[3]);
   }
   ```
   Notice that the above code prints the memory locatoins of each character in
   the string `s`.
   The `&` symbol is used to show the address of each element of the string.

5. The original C code representing the string would look in the following way:
   ```
   // Declares a string without CS50 Library
   
   #include <stdio.h>
   
   int main(void)
   {
       char *s = "HI!";
       printf("%s\n", s);
   }
   ```

---

**Pointer Arithmetic**

1. Pointer arithmetic is allowing doing math on different locations in memory.

---

**String Comparison**

1. A string of characters is _simply_ an array of chararters identified by the location of its first byte.
2. 
3. The following code compare integers:

   ```compare.c
   // Compares two integers

   #include <cs50.h>
   #include <stdio.h>
   
   int main(void)
   {
       // Get two integers
       int i = get_int("i: ");
       int j = get_int("j: ");
   
       // Compare integers
       if (i == j)
       {
           printf("Same\n");
       }
       else
       {
           printf("Different\n");
       }
   }
   ```
   But if there's a string, however, the code cannot use `==` operator.
   In this case the `==` will compare memory locations but not the strings themselves.
   
4. The following code will NOT work with strings:
   
   ```compare_strings.c
   // Compares two strings' addresses

   #include <cs50.h>
   #include <stdio.h>
   
   int main(void)
   {
       // Get two strings
       char s[50];
       printf("s: \n");
       scanf("%s", s);
       char t[50];
       printf("t: \n");
       scanf("%s", t);
   
       // Compare strings' addresses
       if (s == t)
       {
           printf("Same\n");
       }
       else
       {
           printf("Different\n");
       }
   }
   ```
   E.g. `HI!` for both strings will output `Different\n`.
   
5. To understand why are these strings different we need to understand how the memory works.
   Each string has it's own address.

   ![](https://cs50.harvard.edu/x/notes/4/cs50Week4Slide115.png)

6. By using `strcmp` we can correct our code.

---

**Copying and malloc**

1. We can use the following code to create an authentic copy of our string as follows:

   ```copy.c
   // Capitalizes a copy of a string
   
   #include <ctype.h>
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   
   int main(void)
   {
       // Get a string
       char s[50];
       printf("s: \n");
       scanf("%s", s);
   
       // Allocate memory for another string
       char *t = malloc(strlen(s) + 1);
   
       // Copy string into memory, including '\0'
       for (int i = 0, n = strlen(s); i <= n; i++)
       {
           t[i] = s[i];
       }
   
       // Capitalize copy
       t[0] = toupper(t[0]);
   
       // Print strings
       printf("s: %s\n", s);
       printf("t: %s\n", t);
   }
   ```
   The `malloc(strlen(s) + 1` creates a block o memory that is the length or string plus one.
   And this allows the inclussion of the _null_ `\0` character.
   The for loop assigns each value to that same location on the string `t`.

2. The C language has a built-in function to copy strings called `strcpy`.

   ```strcpy.c
   // Capitalizes a copy of a string using strcpy
   
   #include <ctype.h>
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   
   int main(void)
   {
       // Get a string
       char s[50];
       printf("s: \n");
       scanf("%s", s);
   
       // Allocate memory for another string
       char *t = malloc(strlen(s) + 1);
   
       // Copy string into memory
       strcpy(t, s);
   
       // Capitalize copy
       t[0] = toupper(t[0]);
   
       // Print strings
       printf("s: %s\n", s);
       printf("t: %s\n", t);
   }
   ```

3. The function `malloc` returns `NULL` if something goes wrong.
   Let's edit our code to catch this error.
   I will also add a `free` function to empty the memory block
   after running the code.

   ```copy_final.c
   // Capitalizes a copy of a string using strcpy
   
   #include <ctype.h>
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   
   int main(void)
   {
       // Get a string
       char s[50];
       printf("s: \n");
       scanf("%s", s);
   
       // Allocate memory for another string
       char *t = malloc(strlen(s) + 1);
       if (t == NULL)
       {
          return 1;
       }
   
       // Copy string into memory
       strcpy(t, s);
   
       // Capitalize copy
       if (strlen(s) > 0)
       {
          t[0] = toupper(t[0]);
       }
   
       // Print strings
       printf("s: %s\n", s);
       printf("t: %s\n", t);

      // Free the memory
      free(t);
      return 0;
   }

---

**Valgrind**

1. _Valgrind_ is a tool that allows the programmer to check if there are any
   leaks in memory through checking memory heap blocks.
   It especially checks if you used the `free` correctly.

2. If you type `make memory` followed by `valgrind ./memory`, you will get a report
   from valgrind that'll report where the memory has been lost.

3. Example usage of `valgrind`:
   
   ```example.c
   // Demonstrates memory errors via valgrind

   #include <stdio.h>
   #include <stdlib.h>
   
   int main(void)
   {
       int *x = malloc(3 * sizeof(int));
       x[0] = 72;
       x[1] = 73;
       x[2] = 33;
       free(x);
   }
   ```

---

**Garbage Values**

1. Whenever we are trying to access a specific location in a memory,
   it is a good (and necessary) practice to initialize memory first.
   There is no guarantee that requested block of memory will be empty.

2. It is very possible that the memory you allocated was previously utilized by
   computer. It is so called _junk_ or _garbage value_.

3. To show it in practice we can iterate through a random chunk of memory:

   ```mem.c
   #include <stdio.h>
   #include <stdlib.h>
   
   int main(void)
   {
       int scores[1024];
       for (int i = 0; i < 1024; i++)
       {
           printf("%i\n", scores[i]);
       }
   }
   ```
   Not every value is equal 0.

---

**Pointer Fun with Binky**

https://www.youtube.com/watch?v=5VnDaHBi8dM

---

**Swapping**

1. Let's try to swap two values:
   
   ```swap.c
   // Fails to swap two integers

   #include <stdio.h>
   
   void swap(int a, int b);
   
   int main(void)
   {
       int x = 1;
       int y = 2;
   
       printf("x is %i, y is %i\n", x, y);
       swap(x, y);
       printf("x is %i, y is %i\n", x, y);
   }
   
   void swap(int a, int b)
   {
       int tmp = a;
       a = b;
       b = tmp;
   }
   ```
   Out:
   `x is 1, y is 2
   x is 1, y is 2`

   In this scenario the values will fail to swap.
   The reason - scope.
   The values x, y initiated inside of the main function
   are locked inside of that function.

2. `main` and `swap` have two separate _frames_ or areas of memory
   To make it work we'll have to use _pointers_

   ```swap.c
   // Swaps two integers using pointers
   
   #include <stdio.h>
   
   void swap(int *a, int *b);
   
   int main(void)
   {
       int x = 1;
       int y = 2;
   
       printf("x is %i, y is %i\n", x, y);
       swap(&x, &y);
       printf("x is %i, y is %i\n", x, y);
   }
   
   void swap(int *a, int *b)
   {
       int tmp = *a;
       *a = *b;
       *b = tmp;
   }
   ```

   Basically, variables are not passed by value but by !_REFERENCE_!
      
   ![memory pointers](https://cs50.harvard.edu/x/notes/4/cs50Week4Slide198.png)

---

**Overflow**


   


   


   

   




