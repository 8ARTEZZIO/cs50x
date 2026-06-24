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
       char *s = get_string("s: ");
       char *t = get_string("t: ");
   
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
   
   #include <cs50.h>
   #include <ctype.h>
   #include <stdio.h>
   #include <stdlib.h>
   #include <string.h>
   
   int main(void)
   {
       // Get a string
       char *s = get_string("s: ");
   
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
   The `malloc(strlen(s) + 1`
   


   

   




