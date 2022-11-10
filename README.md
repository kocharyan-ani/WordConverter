# WordConverter

This is an application which replaces numbers found in their textual form
in the source text by the corresponding numerical form.

## How to build

The prerequisite is to have CMake on the system. Then the application can be built
by simply running the following command after cloning this Git repo locally:

    cd {WordConverter repo folder}
    cmake -B build
    cmake --build build --config release

After the build the executable will be accessible in the following folder:

    bin/release/


## How to run

The application can be run by providing the following arguments:

    word_converter -i <input_file> [-o <output_file>]

The input file contains a text which may have numbers written in textual form.

The modified text will be printed in the console output. If an output file is
provided then the result will be also written in that file.


## Solution

Here are the main architectural decisions for the solution:

1. **Streams**

The input and output are considered to be streams. Incoming text is tokenized into
words, and if a contunius set of words is representing a number, it is converted to
the corresponding numerical form and written into the output stream. Otherwise the
original text with the corresponding spacings is passed to the output stream without
any changes.

2. **Punctuation**

Current implementation recognizes only one symbol - the period ('.'). It is
delimiting sentences. So the text to number parsing will stop if a period is
encountered. All other symbols, such as a comma, a colon or a semicolon, are
currently treated to be part of the words, so an example like this will have the
following conversion:

    one hundred: birds  =>  1 hundred: birds

3. **Grammar**

There are many ways of writing numbers in English, including differences between
American English and British English, differences of the punctuation and the
structure, such as the usage of dash, comma, 'and', etc. It is also possible that
the numbers are written in not a well formed way, with abbreviation, or using non
formal structures.

This application currently supports only a limited set of rules, which are based on
the following wiki page - [English numerals](https://en.wikipedia.org/wiki/English_numerals).
Here are examples which reflect the rules taken into account in the application:

```
0  -  zero
1  -  one
2  -  two
...
10  -  ten
20  -  twenty
30  -  thirty
...
11  -  eleven
12  -  twelve
13  -  thirteen
...
21  -  twenty-one
34  -  thirty-four
57  -  fifty-seven
...
100  -  one hundred
200  -  two hundred
300  -  three hundred
...
101  -  one hundred and one
213  -  two hundred and thirteen
450  -  four hundred and fifty
678  -  six hundred and seventy-eight
...
1000  -  one thousand
12003  -  twelve thousand three
45016  -  forty-five thousand sixteen
700089  -  seven hundred thousand eighty-nine
102314  -  one hundred and two thousand three hundred and fourteen
```