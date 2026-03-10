# Lexer
This is my attempt at creating a lexer in C++

There is still a lot of documentation to do about my implementation and also there are improvements to be made. But for now, know that to use it you need to specify your tokens in the `lang.reg` file. The program will read your tokens and your regular expressions from it and build a finite automata to identify the specified language. And the input file must be sent through the standard input. 

You can use the lang file as an example to build your own regular expressions. My implementation is a bit rough and it was all done for learning purposes. So any contributions are welcome.

Some useful resources:

[Regular Expression Matching Can Be Simple And Fast](https://swtch.com/~rsc/regexp/regexp1.html) by Russ Cox

[Visualizing Thompson’s Construction Algorithm for NFAs, step-by-step](https://medium.com/swlh/visualizing-thompsons-construction-algorithm-for-nfas-step-by-step-f92ef378581b) by Gregory Cernera


[Visualizing Thompson’s Construction Algorithm for NFAs, step-by-step](https://gregorycernera.medium.com/converting-regular-expressions-to-postfix-notation-with-the-shunting-yard-algorithm-63d22ea1cf88) by Gregory Cernera
