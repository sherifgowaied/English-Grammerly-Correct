# English-Grammerly-Correct</br>
Finding the wrong words in the article by downloading all the English language words through the Hash Table data structure with Hash function for speed of processing. And produce a report on the wrong words with their correction and produce output   statement of the number of wrong words and thier count in the article and the speed of the program


### Implement a program that spell-checks a file, a la the below, using a hash table.</br>

$ ./speller texts/lalaland.txt</br>
MISSPELLED WORDS</br>

[...]</br>
AHHHHHHHHHHHHHHHHHHHHHHHHHHHT</br>
[...]</br>
Shangri</br>
[...]
fianc</br>
[...]</br>
Sebastian's</br>
[...]</br>
</br>
WORDS MISSPELLED:</br>
WORDS IN DICTIONARY:</br>
WORDS IN TEXT:</br>
TIME IN load:</br>
TIME IN check:</br>
TIME IN size:</br>
TIME IN unload:</br>
TIME IN TOTAL:</br>


# Understanding
Theoretically, on input of size n, an algorithm with a running time of n is “asymptotically equivalent,” in terms of O, to an algorithm with a running time of 2n. Indeed, when describing the running time of an algorithm, we typically focus on the dominant (i.e., most impactful) term (i.e., n in this case, since n could be much larger than 2). In the real world, though, the fact of the matter is that 2n feels twice as slow as n.</br>

The challenge ahead of you is to implement the fastest spell checker you can! By “fastest,” though, we’re talking actual “wall-clock,” not asymptotic, time.</br>

In speller.c, we’ve put together a program that’s designed to spell-check a file after loading a dictionary of words from disk into memory. That dictionary, meanwhile, is implemented in a file called dictionary.c. (It could just be implemented in speller.c, but as programs get more complex, it’s often convenient to break them into multiple files.) The prototypes for the functions therein, meanwhile, are defined not in dictionary.c itself but in dictionary.h instead. That way, both speller.c and dictionary.c can #include the file. Unfortunately, we didn’t quite get around to implementing the loading part. Or the checking part. Both (and a bit more) we leave to you! But first, a tour.</br>

dictionary.h</br>
Open up dictionary.h, and you’ll see some new syntax, including a few lines that mention DICTIONARY_H. No need to worry about those, but, if curious, those lines just ensure that, even though dictionary.c and speller.c (which you’ll see in a moment) #include this file, clang will only compile it once.</br>

Next notice how we #include a file called stdbool.h. That’s the file in which bool itself is defined. You’ve not needed it before, since the CS50 Library used to #include that for you.</br>

Also notice our use of #define, a “preprocessor directive” that defines a “constant” called LENGTH that has a value of 45. It’s a constant in the sense that you can’t (accidentally) change it in your own code. In fact, clang will replace any mentions of LENGTH in your own code with, literally, 45. In other words, it’s not a variable, just a find-and-replace trick.</br>

Finally, notice the prototypes for five functions: check, hash, load, size, and unload. Notice how three of those take a pointer as an argument, per the *:</br>

bool check(const char *word);</br>
unsigned int hash(const char *word);</br>
bool load(const char *dictionary);</br>
Recall that char * is what we used to call string. So those three prototypes are essentially just:
</br>
bool check(const string word);</br>
unsigned int hash(const string word);</br>
bool load(const string dictionary);</br>
And const, meanwhile, just says that those strings, when passed in as arguments, must remain constant; you won’t be able to change them, accidentally or otherwise!</br>

dictionary.c</br>
Now open up dictionary.c. Notice how, atop the file, we’ve defined a struct called node that represents a node in a hash table. And we’ve declared a global pointer array, table, which will (soon) represent the hash table you will use to keep track of words in the dictionary. The array contains N node pointers, and we’ve set N equal to 1 for now, meaning this hash table has just 1 bucket right now. You’ll likely want to increase the number of buckets, as by changing N, to something larger!</br>

Next, notice that we’ve implemented load, hash, check, size, and unload, but only barely, just enough for the code to compile. Your job, ultimately, is to re-implement those functions as cleverly as possible so that this spell checker works as advertised. And fast!</br>

speller.c</br>
Okay, next open up speller.c and spend some time looking over the code and comments therein. You won’t need to change anything in this file, and you don’t need to understand its entirety, but do try to get a sense of its functionality nonetheless. Notice how, by way of a function called getrusage, we’ll be “benchmarking” (i.e., timing the execution of) your implementations of check, load, size, and unload. Also notice how we go about passing check, word by word, the contents of some file to be spell-checked. Ultimately, we report each misspelling in that file along with a bunch of statistics.</br>

Notice, incidentally, that we have defined the usage of speller to be</br>

Usage: speller [dictionary] text
where dictionary is assumed to be a file containing a list of lowercase words, one per line, and text is a file to be spell-checked. As the brackets suggest, provision of dictionary is optional; if this argument is omitted, speller will use dictionaries/large by default. In other words, running
</br>
$ ./speller text</br>
will be equivalent to running</br>

$ ./speller dictionaries/large text</br>
where text is the file you wish to spell-check. Suffice it to say, the former is easier to type! (Of course, speller will not be able to load any dictionaries until you implement load in dictionary.c! Until then, you’ll see Could not load.)</br>

Within the default dictionary, mind you, are 143,091 words, all of which must be loaded into memory! In fact, take a peek at that file to get a sense of its structure and size. Notice that every word in that file appears in lowercase (even, for simplicity, proper nouns and acronyms). From top to bottom, the file is sorted lexicographically, with only one word per line (each of which ends with \n). No word is longer than 45 characters, and no word appears more than once. During development, you may find it helpful to provide speller with a dictionary of your own that contains far fewer words, lest you struggle to debug an otherwise enormous structure in memory. In dictionaries/small is one such dictionary. To use it, execute</br>

$ ./speller dictionaries/small text</br>
where text is the file you wish to spell-check. Don’t move on until you’re sure you understand how speller itself works!</br>

Odds are, you didn’t spend enough time looking over speller.c. Go back one square and walk yourself through it again!</br>

texts/</br>
So that you can test your implementation of speller, we’ve also provided you with a whole bunch of texts, among them the script from La La Land, the text of the Affordable Care Act, three million bytes from Tolstoy, some excerpts from The Federalist Papers and Shakespeare, and more. So that you know what to expect, open and skim each of those files, all of which are in a directory called texts within your pset5 directory.</br>

Now, as you should know from having read over speller.c carefully, the output of speller, if executed with, say,</br>

$ ./speller texts/lalaland.txt</br>
will eventually resemble the below.</br>

Below’s some of the output you’ll see. For information’s sake, we’ve excerpted some examples of “misspellings.” And lest we spoil the fun, we’ve omitted our own statistics for now.</br>

MISSPELLED WORDS</br>

[...]</br>
AHHHHHHHHHHHHHHHHHHHHHHHHHHHT</br>
[...]</br>
Shangri</br>
[...]</br>
fianc</br>
[...]</br>
Sebastian's</br>
[...]</br>
</br>
WORDS MISSPELLED:</br>
WORDS IN DICTIONARY:</br>
WORDS IN TEXT:</br>
TIME IN load:</br>
TIME IN check:</br>
TIME IN size:</br>
TIME IN unload:</br>
TIME IN TOTAL:</br>
TIME IN load represents the number of seconds that speller spends executing your implementation of load. TIME IN check represents the number of seconds that speller spends, in total, executing your implementation of check. TIME IN size represents the number of seconds that speller spends executing your implementation of size. TIME IN unload represents the number of seconds that speller spends executing your implementation of unload. TIME IN TOTAL is the sum of those four measurements.</br>

Note that these times may vary somewhat across executions of speller, depending on what else CS50 IDE is doing, even if you don’t change your code.</br>

Incidentally, to be clear, by “misspelled” we simply mean that some word is not in the dictionary provided.</br>

Makefile</br>
And, lastly, recall that make automates compilation of your code so that you don’t have to execute clang manually along with a whole bunch of switches. However, as your programs grow in size, make won’t be able to infer from context anymore how to compile your code; you’ll need to start telling make how to compile your program, particularly when they involve multiple source (i.e., .c) files, as in the case of this problem. And so we’ll utilize a Makefile, a configuration file that tells make exactly what to do. Open up Makefile, and you should see four lines:</br>

The first line tells make to execute the subsequent lines whenever you yourself execute make speller (or just make).</br>
The second line tells make how to compile speller.c into machine code (i.e., speller.o).</br>
The third line tells make how to compile dictionary.c into machine code (i.e., dictionary.o).</br>
The fourth line tells make to link speller.o and dictionary.o in a file called speller.</br>
