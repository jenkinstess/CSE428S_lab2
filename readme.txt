Tess Jenkins (jenkinstess@wustl.edu)
Sam Saxon (s.saxon@wustl.edu)
Lab 1

Errors:
    - Syntax errors throughout building --> forgotten semi colons, forgotten parentheses, incorrect spacing, brackets left out
    - Commone errors included forgetting to include specific headers and leaving out brackets in switch statements. 
    - One error that took up a lot of time was the one shown below which appeared as a linker error. After looking through the header and cpp files intently, we realized that the header file included the int parameter of the prefix increment operator, but we failed to add that parameter to the method definition in the cpp file. After including the int parameter our issues were resolved.
            /tmp/ccQHSU66.o: In function `PinochleDeck::PinochleDeck()':
            /home/warehouse/s.saxon/CSE428/lab0/CSE428S_lab0/PinochleDeck.cpp:98: undefined reference to `operator++(PinochleRank&, int)'
            /home/warehouse/s.saxon/CSE428/lab0/CSE428S_lab0/PinochleDeck.cpp: 100: undefined reference to `operator++(Suits&, int)
    - An error that took a lot of time to solve was the one shown below. This was confusing as the statement seemed simple enough to not cause errors, but after 
        looking more into shared ptrs we realized that <memory> needed to be included.
            lab1.cpp:24:18: error: ‘shared_ptr’ is not a member of ‘std’
             std::shared_ptr<Game> gamePtr = create(argc, argv);
                  ^~~~~~~~~
    - We spent time looking into the ordering of the functions in the lab1.cpp file due to the error below. To fix this we realized we needed to declaire the function above the main function, but 
        place the definition below the main function to allow access to "HoldEmGame" and "PinochleGame"
            lab1.cpp:53:34: error: ‘HoldEmGame’ was not declared in this scope
            game1 = std::make_shared<HoldEmGame>(argc, argv);
                                    ^~~~~~~~~~




Design decisions
- In printing out the hands for each player we decided to add line breaks between each players hand for readability. 

Observations
- the studios were very helpful in terms of providing a base familiarity for all the main concepts covered in this lab.
- reading about iterators in the textbook and in online sources greatly aided us for navigating using the card sets.
- the code for the classes became much nicer to read and navigate in utilizing inheritence in this lab, as compared to the previous one.

