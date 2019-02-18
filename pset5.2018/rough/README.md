# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

It is, according to Merriam-Webster's Medical Dictionary,
a pneumoconiosis caused by the inhalation of very fine silicate or quartz dust.


## According to its man page, what does `getrusage` do?

The `getrusage()` function returns resource usage measures. In the case of *speller.c*,
measures for `RUSAGE_SELF`, which is the sum of resources used by all threads in the process.


## Per that same man page, how many members are in a variable of type `struct rusage`?

There are **16** members in a struct rusage variable.


## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

The arguments required for the `getrusage()` function to work properly are an integer, and a pointer to struct rusage structure.
The resource usages, according to the getrusage man page, are returned in the structure that the pointer in the argument list points to.
Pointers are passed to functions by reference, not by value, so this is why `before` and `after` are passed to the `getrusage()` function by reference.

Passing them by reference also saves time and memory because the program doesn't have to make copies of `before` and `after`
to pass to the callee.


## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

`main` uses the `for` loop to read text from the file one character at a time.
* It first checks if the character is an alphabet, or if it's an apostrophe and the word index isn't the first index;
if this check evaluates to true, it appends that character to the word array and increments its index.

  * If after this index is increased, its value exceeds the value of the longest word in the dictionary, the `fgetc` function
is called in a `while` loop until the end of that particular word is reached. Then the index is reset to zero to prepare
for the new word to be checked.

* However, if the character turns out to be a digit, the `fgetc` function is called in a while loop and gets subsequent
characters in that word until its end is reached; after which it resets the word array index to zero to prepare for the
new word.

* If none of the above is the case, and the word index is not the first index of that array, then we can be sure that a
word has been found. That particular word element will be assigned the null zero, and the word variable will be incremented
by one to keep track of the number of words in the text being spell checked.

* The word is passed to the `check` function to see if it exists in the dictionary.
  * If it does exist, the check function will return true, or return false if it doesn't.
  * The return value of the check function will be negated and that new value will be
  stored in the variable `misspelled`.

* If `misspelled` evaluates to `true` in the `if` statement that follows, then the contents of the
word array will be printed on the screen to display what word was misspelled. Afterward, the index is
initialized to zero to prepare for the new word.


## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

If `fscanf` were to be used, we'd need to create a temporary array to hold each word that would be read
from the file. This temporary buffer would be large enough to hold the size of the longest word in
our dictionary. If however, the file being read from, contains a word longer than the capacity of this
temporary buffer, we could potentially overwrite information in memory when we read that word from the
file.

Another reason is that, if a word has some punctuation mark at the end, `fscanf` will read in the
punctuation as part of the word, thus making such words, if not represented in the dictionary that way,
impossible to find.


## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

The parameters for both functions are declared as constants to ensure that the location pointed to will not be changed
through the pointers *word* and *dictionary*.