Tess Jenkins (jenkinstess@wustl.edu)
Sam Saxon (s.saxon@wustl.edu)
Lab 2

Errors:
    - Syntax errors throughout building --> forgotten semi colons, forgotten parentheses, incorrect spacing, brackets left out
    - Commone errors included forgetting to include specific headers and leaving out brackets in switch statements. 
    - Took a while to figure out the best methods of indexing into enums and figuring out the best practices for counting the number of occurrences in a vector.
    - One error that initially took up some time was the permissions issue for accessing the cards protected memeber variables. Upon seeing the announcement to create a method to provide access to this variable, the issue got resolved.
    - A common error was forgetting to index into values in the enumeration, providing the error seen below. Adding the proper :: prior to it resolved these issues.
            PinochleGame.cpp:126:31: error: ‘meld_values’ was not declared in this scope
             os << "dix : " << meld_values[PinochleMelds::dix];
                               ^~~~~~~~~~~
    - Another error that took awhile to figure out was how to properly access the value returned by the method returning access to the cards protected member variable. This was fixed by providing the proper dereferncing syntax, converting from a pointer to an array to just an array.
            PinochleGame.cpp: In member function'void PinochleGame::suit_independent_evaluation(const CardSet<PinochleRank,Suits>&, std: :vector<PinochleMelds>&)'
            PinochleGame.cpp:170:26: error: request for member 'begin' in 'temp_cards' which is of non-class type 'std: :vector<Card<PinochleRank,
            Suits>, std: :allocator<Card<PinochleRank, Suits>> › CardSet<PinochleRank, Suits>::*
                for (it = temp_cards.begin(); it < temp_cards.end(); it++) {
                                    ^~~~~~~~~~~



Design decisions
- In printing out the hands for each player we decided to add line breaks between each players hand for readability. 
- In printing out the possible melds for each hand in pinochle we chose to place them a line underneath the print out of the users hand. If there were multiple melds for a hand each occupied their own line for better readability.
- The string member of the nested struct I chose to make not a reference despite instructions because of compiler issues synthesizing default operations.

- Poker Hand Evaluation Strategy: 
    I used this site: https://jonathanhsiao.com/blog/evaluating-poker-hands-with-bit-math as reference when creating the holdem evaluation to greatly simplify the implementation with bit math

    This stragegy uses 2 ints, one representing the unique ranks and one representing the frequency of each rank.

        Ex. A A K K 3 
            => card_freq = 0011 0011 0000 0000 0000 0000 0000 0000 0000 0000 0000 0001 0000
            => unique_cards = 1100000000010

    by taking card_freq % 15, most of the evaluations can be immediately determined because % 15 has the effect of adding together the values of each group of 4 bits.

        Ex. for the above example, card_freq % 15 = 3 + 3 + 1 = 7 => two pair

    Straights can be determined by normalizing unique_cards and checking to see if the result is 11111 (31), meaning the cards have adjacent ranks

    Flushes are determined by checking if the number of unique suits is 1

    For ties, the ranks are sorted first by frequency then by value and are shifted over depending on the order.

        Ex. A K 3 A K sorted to => A A K K 3 => 1100 1100 1011 1011 0011

    This number can be compared directly between hands with the same evaluation to determine which hand is better

Observations
- the studios were very helpful in terms of providing a base familiarity for all the main concepts covered in this lab.
- reading about iterators in the textbook and in online sources greatly aided us for navigating using the card sets.
- the code for the classes became much nicer to read and navigate in utilizing inheritence in this lab, as compared to the previous one.
- indexing into enumerations became a lot more clear as the lab progressed. 

