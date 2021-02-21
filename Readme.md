# My Word Book

## data

- **word**: consists of its name, meanings, and example.

    - **name**: use a string to represent.
    - **meaning**: represented by a vector of string.
        - When displayed, it looks like A;B;C, etc.

    - **example**: represented by a string.

- **group**: consists of its ID, words, group reason.
    - **ID**: unsigned.
    - **words**: a vector of word.
    - **reason**: contains a bool value which determines whether the words are grouped by shape or meaning.
        - if by shape, there's nothing to say anymore, 
        - otherwise, clarify which meaning the words are grouped by.



## functions

### file represent

At the beginning and during the program, we write in and read from two files: `words.bk` and `groups.bk`.

Every word is a struct type value, which is stored as `"name/meaning1;meaning2;...meaningn;/example\n"`, when read, start from the begin of a row and end with a `'\n'`, get three strings and convert the middle into a vector of string, and then initialize a word.

Similarly, every group is also a struct type value stored as `"ID/word1;word2;...wordn;/" + (isShape?(""):reason) + "\n"`, when read, also start from the beginning of a row and end with a `'\n'`, get three or two strings and convert the middle... oh I don't want to waste time writing this. if the last string is `""`, it meanings this group is a shape group, so it won't cause a bug.

All the words are stored in a `map<string, word>`, whose string is actually `word.name`. And it should be initialized at the beginning of program. The group only need to use the `name` of each `word` it has, when use, find it in `map`.

### tools needed

- **Words** and **groups**:
    - **Initialize**: `word newWord()` are used to provide an interactive way to initialize a new word, and `word newWord(string name, vector<string> meanings, string example)` is used for the program itself to initialize the program from files. groups also have two similar functions, for user and for program.
    - **File I/O**: used to read and write files.
    - **Display**: to print a word or a group on screen.
    - `//Because the project didn't require this project to support word/group deleting, I don't consider that.`

- **User GUI**:

    Consider treating the whole program as a **Linked List**, each node of which contains `function, next, last`, note that `next` and `last` are arrays of `node` pointers, and `function` is a function pointer. This way I do not need to write tons of `switch` and `goto` because numbers can be directly used as indexes of arrays, while making the program easier to understand. 

    `// However I still have to write tons of display functions, Hell!`

    