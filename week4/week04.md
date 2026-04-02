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

   
