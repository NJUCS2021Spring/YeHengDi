# My Word Book

## data

- **word**: consists of its name, meanings, and example.

    - **name**: use a string to represent.
    - **meaning**: represented by a vector of string.
        - When displayed, it looks like A;B;C, etc.

    - **example**: represented by a string.

- **group**: consists of its ID, words, group reason.
    - **ID**: unsigned.
    - **words**: a vector of string.
    - **reason**: contains a bool value which determines whether the words are grouped by shape or meaning.
        - if by shape, there's nothing to say anymore, 
        - otherwise, clarify which meaning the words are grouped by.



## functions

### file represent

At the beginning and during the program, we write in and read from two files: `words.w` and `groups.w`.

Every word is a struct type value, which is stored as `"name/meaning1;meaning2;...wordn;/example\n"`, when read, start from the begin of a row and end with a `'\n'`, get three strings and convert the middle into a vector of string, and then initialize a word.

Similarly, every group is also a struct type value stroed as `"ID/word1;word2;...wordn;/" + (isShape?(""):reason) + "\n"`, when read, also start from the beginning of a row and end with a `'\n'`, get three or two strings and convert the middle... oh I don't want to waste time writing this. if the last string is `""`, it meanings this group is a shape group, so it won't cause a bug.

All the words are stored in a `map<string, word>`, whose string is actually `word.name`. And it should be initialized at the beginning of program. The group only need to memorize the `name` of each `word` it has, when use, find it in `map`.

### tools needed

`to be continued...`

 

