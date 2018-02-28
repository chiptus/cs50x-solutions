# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

pneumonoultramicroscopicsilicovolcanoconiosis is an invented long word. It means a lung disease cause by inhaling hash

## According to its man page, what does `getrusage` do?

getrusage will calculate resource usage measures

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

Passing a struct by value means copying the value which can cause performance issues - either size or speed.
  It's mostly recommended to pass struct with a pointer to overcome this issues.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

Main is reading words from the file in the for loop that is declared in lines 71 to 128.
It reads the file's characters one at a time.
If a character is a digit it will skip the following sequence of alphanumeric characters (basically until it gets to a space or a new line)
If it's an alphabetical character (or an apostrophes), it will append that to the current found word, but if the word is too long (more then the LENGTH const), it will skip it.
Otherwise - it's not an alphanumeric value, then it's a space or new line and the word is read completely, thus it will check its spelling and start a new word.


## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

I think the using `fscanf` can cause our program to load also words with numbers or other non alphabetical (or apostrophes) inside. In that case we would need to check every character in every word anyway.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

I think the use of const in function parameters is to signal that the parameters won't be changed.
