# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

It is, according to Merriam-Webster's Medical Dictionary, a pneumoconiosis caused by the inhalation
of very fine silicate or quartz dust.

TODO

## According to its man page, what does `getrusage` do?

getrusage returns resource usage measures for
the sum of resources used by all threads in the calling process; or
measures for all children of the calling process that have terminated
or been waited for; or, resource measures for the calling thread itself.

TODO

## Per that same man page, how many members are in a variable of type `struct rusage`?

There are 16 members in a struct rusage variable.

TODO

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

TODO

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

TODO

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

TODO

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

TODO
