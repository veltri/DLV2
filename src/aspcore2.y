%{
//////////////////////////////////////////////////////////////////////////////
// aspcore2.y

//////////////////////////////////////////////////////////////////////////////
/*
This file is part of the ASPCOMP2013 ASP-Core-2 validator (validator in the following)

    The validator is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    The validator is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the validator.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "input/InputDirector.h"

%}
%error-verbose
%union {
    char* string;
    int integer;
}

%type <integer> term term_
%type <integer> terms
%type <string> identifier

%token <string> SYMBOLIC_CONSTANT NUMBER VARIABLE STRING

%token ERROR NEWLINE   

%token DOT SEMICOLON COLON CONS QUERY_MARK

%token PLUS TIMES SLASH

%token ANON_VAR

%token PARAM_OPEN PARAM_CLOSE
%token SQUARE_OPEN SQUARE_CLOSE
%token CURLY_OPEN CURLY_CLOSE

%token EQUAL UNEQUAL LESS GREATER LESS_OR_EQ GREATER_OR_EQ

%token DASH COMMA NAF AT WCONS

%token VEL EXISTS AGGR_COUNT AGGR_MAX AGGR_MIN AGGR_SUM

%left PLUS DASH
%left TIMES SLASH

%start program
%%

HEAD_SEPARATOR  : VEL;

program
    : 
    | rules
    | rules query { InputDirector::getInstance().getBuilder()->onQuery(); }
    | error { yyerror("Generic error"); }
    ;

rules
    : rules rule {}
    | rule {}
    ;

rule
    : head DOT { InputDirector::getInstance().getBuilder()->onRule(); }
    | head CONS DOT { InputDirector::getInstance().getBuilder()->onRule(); }
    | head CONS body DOT { InputDirector::getInstance().getBuilder()->onRule(); }
    | CONS body DOT /*constraint*/ { InputDirector::getInstance().getBuilder()->onConstraint(); }
    | WCONS body DOT weight_at_levels {}
    ;

head
    : disjunction {}
    | choice_atom {}
    ;       

body
    : conjunction {}
    ;

weight_at_levels : SQUARE_OPEN term SQUARE_CLOSE {}
         | SQUARE_OPEN term levels_and_terms SQUARE_CLOSE {}
                 ;

levels_and_terms : AT term {} 
                 | AT term COMMA terms {}
         | COMMA terms {} 
             ;
          
disjunction
    : classic_literal 
        { 
            InputDirector::getInstance().getBuilder()->addToHead(); 
        }
    | disjunction HEAD_SEPARATOR classic_literal 
        { 
            InputDirector::getInstance().getBuilder()->addToHead(); 
        }
    | existential_atom 
        { 
            InputDirector::getInstance().getBuilder()->addToHead(); 
        }
    | disjunction HEAD_SEPARATOR existential_atom 
        { 
            InputDirector::getInstance().getBuilder()->addToHead(); 
        }
    ;

conjunction
    : naf_literal_aggregate { InputDirector::getInstance().getBuilder()->addToBody(); }
    | conjunction COMMA naf_literal_aggregate { InputDirector::getInstance().getBuilder()->addToBody(); }
    ;

choice_atom : term binop CURLY_OPEN choice_elements CURLY_CLOSE binop term {}
        | term binop CURLY_OPEN choice_elements CURLY_CLOSE {}    
        | CURLY_OPEN choice_elements CURLY_CLOSE {}    
        | CURLY_OPEN choice_elements CURLY_CLOSE binop term {}        
        ;

choice_elements : choice_elements SEMICOLON choice_element {}
        | choice_element {}
                ;

choice_element : atom {}
               | atom COLON naf_literals {}
               ;

naf_literals
    : naf_literal {}
    | naf_literals COMMA naf_literal {}
    ;    
          
naf_literal
    : classic_literal { InputDirector::getInstance().getBuilder()->onNafLiteral(); }
    | NAF classic_literal { InputDirector::getInstance().getBuilder()->onNafLiteral(true); }
    | builtin_atom {}
    ;

naf_literal_aggregate
    : naf_literal {}
    | aggregate_atom {}
    | NAF aggregate_atom {}
    ;      

existential_atom
    : EXISTS vars atom 
        { 
            InputDirector::getInstance().getBuilder()->onExistentialAtom(); 
        }

classic_literal
    : atom { InputDirector::getInstance().getBuilder()->onAtom(); }
    | DASH atom { InputDirector::getInstance().getBuilder()->onAtom(true); }
    ;  

atom
    : identifier { InputDirector::getInstance().getBuilder()->predicateName($1); }
    | identifier PARAM_OPEN terms PARAM_CLOSE { InputDirector::getInstance().getBuilder()->predicateName($1); }
    | identifier PARAM_OPEN PARAM_CLOSE { InputDirector::getInstance().getBuilder()->predicateName($1); }
    ;              
         
terms
    : term { $$ = $1; }
    | terms COMMA term { $$ = $1 + $3; }
    ;

basic_terms : basic_term {}
         | basic_terms COMMA basic_term    {}
         ;



builtin_atom    : term binop term {}
                ;

compareop : EQUAL         {} 
          | UNEQUAL       {}
          ;       
         
binop    : compareop     {} 
         | leftwardop        {}
         | rightwardop       {}
         ;       
         
arithop   : PLUS     {} 
          | DASH    {}
          | TIMES    {}
          | SLASH      {}
          ;      

term_ 
    : identifier 
        { 
            InputDirector::getInstance().getBuilder()->onTerm($1); 
            $$ = 1; 
        }
    | NUMBER 
        { 
            InputDirector::getInstance().getBuilder()->onTerm($1); 
            $$ = 1; 
        }
    | ANON_VAR 
        { 
            InputDirector::getInstance().getBuilder()->onTerm("_"); 
            $$ = 1; 
        }
    | identifier PARAM_OPEN terms PARAM_CLOSE 
        { 
            InputDirector::getInstance().getBuilder()->onFunction($1, $3); 
            $$ = 1; 
        }
    | PARAM_OPEN term PARAM_CLOSE 
        { 
            $$ = 1;
        }
    | DASH term 
        { 
            InputDirector::getInstance().getBuilder()->onTermDash(); 
            $$ = $2;
        }
    ;

term
    : term_ { $$ = $1; }
    | term arithop term_ { $$ = 1; }
    ;        

basic_term : ground_term {}
       | variable_term {}
       ;

ground_term 
    : SYMBOLIC_CONSTANT 
    | STRING
    | NUMBER
    | DASH NUMBER
    ;

variable_term 
    : VARIABLE {}
    | ANON_VAR {}
    ;

vars
    : VARIABLE 
        { 
            InputDirector::getInstance().getBuilder()->onExistentialVariable($1); 
        }
    | vars COMMA VARIABLE 
        { 
            InputDirector::getInstance().getBuilder()->onExistentialVariable($3); 
        }
    ;

identifier
    : SYMBOLIC_CONSTANT { $$ = $1; }
    | STRING { $$ = $1; }
    | VARIABLE { $$ = $1; }
    ;
                
query     : atom QUERY_MARK {}
          ; 

compare_aggregate : term compareop aggregate {}
                  | aggregate compareop term {}            
                  ;

leftward_left_aggregate  : term leftwardop aggregate {}
                         ;
left_aggregate : leftward_left_aggregate
               | rightward_left_aggregate {}
               ;

rightward_left_aggregate  : term rightwardop aggregate {}
                          ;
                          
right_aggregate : aggregate leftwardop term {}
                |  aggregate rightwardop term {}
                ;

aggregate_atom   : left_aggregate {}
            | right_aggregate {}
            | compare_aggregate {}
            | leftward_left_aggregate leftwardop term {}
            | rightward_left_aggregate rightwardop term {}
            ;   

leftwardop : LESS {}
       | LESS_OR_EQ {}
       ;    

rightwardop : GREATER {}
        | GREATER_OR_EQ {}
        ;           
            
aggregate  : aggregate_function CURLY_OPEN aggregate_elements CURLY_CLOSE {}
                ;

aggregate_elements : aggregate_elements SEMICOLON aggregate_element {}
           | aggregate_element {}
           ;
        
            
aggregate_element    : basic_terms COLON naf_literals {}
                    ;

aggregate_function  : AGGR_COUNT {}
                    | AGGR_MAX {}
                    | AGGR_MIN {}
                    | AGGR_SUM {}
                    ;   
