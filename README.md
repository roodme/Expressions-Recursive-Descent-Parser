# Expression Parsing by Recursive Descent

## About

The parser takes as input a list of tokens and calculates the expression given by recursive descent. <br />
That means that it utilizes the call stack to comput the expression, thus making the code simplier <br />
and the error checking much easier, since we know what to expect. <br />

This module can be easily modified to support an actual list of tokens or more operators etc <br />
and has been with great easy used in my project of the final [assignment](http://cgi.di.uoa.gr/~ip/iphw2021_4.pdf) <br />
during the course "Intro to Programming" by DIT, UoA (first semester) 

## Grammar

```bash
<log_expr>  ->  <term_log> <term_log_tail>

<rel_expr>  ->  <term_rel> <term_rel_tail>

<expr>      ->  <term> <term_tail>


<term_log_tail>     ->   || <rel_expr> <term_log_tail> 
                       | e

<term_log>          ->   <rel_expr> <factor_log_tail>

<factor_log_tail>   ->   && <rel_expr> <term_log_tail> 
                       | e


<term_rel_tail>     ->   <eq_op> <term_rel> <term_rel_tail>
                       | e

<term_rel>          ->  <expr> <factor_rel_tail>

<factor_rel_tail>   ->   <rel_op> <expr> <factor_rel_tail>
                       | e


<term_tail>     ->   <add_op> <term> <term_tail>
                   | e


<term>          ->   <factor> <factor_tail>

<factor_tail>   ->   <mult_op> <factor> <factor_tail>
                   | e

<factor>        ->   ( <log_expr> ) 
                   | - <factor>
                   | ! <factor> 
                   | int

<add_op>    ->  + | -
<mult_op>   ->  * | / | %
<eq_op>     ->  == | !=
<rel_op>    ->  > | >= | < | <=
```


## License
[MIT](https://choosealicense.com/licenses/mit/)
  
