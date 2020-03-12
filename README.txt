This program creates a spellchecker using one of three probes. Created a quadratic probing class that implements the quadratic probing method to handle collisions. Then from that class, derived the linear probing and double probing classes. To check our spelling, we can read through a dictionary and hash each word to add to a hash table. My chosen method is quadratic probing. Then the program reads through a chosen document. The words are made lowercase and some punctuation was removed for more accurate results. To check spelling we have three cases, add characters, remove characters and swap characters. 

- One issue I had with Spell check was some confusion on how to handle punctuation. 
- Originally had trouble getting the right amount of probes before realizing I was counting total amount of probes rather than the amount of probes needed before finding position x. To solve this, I reset the amount of probes when contains is called so FindPos(x) would count the probes properly. 


To run the program:
Compile everything by typing
- make clean
- make all

To run create_and_test_hash:
./create_and_test_hash <words file name> <query words file name> <flag>
	./create_and_test_hash words.txt query_words.txt quadratic
	./create_and_test_hash words.txt query_words.txt linear
	./create_and_test_hash words.txt query_words.txt double

To run spell_check:
./spell_check <document file> <dictionary file>
	./spell_check document1_short.txt wordsEn.txt
	./spell_check document1.txt wordsEn.txt

By typing make clean - you delete all .o files and executables.

Input files:
	document1_short.txt
	document1.txt
	query_words.txt
	words.txt
	wordsEn.txt
Output file:
	expected_output.txt