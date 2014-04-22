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
    char single_char;
    int integer;
}

%type <integer> terms 
%type <single_char> arithop
%type <string> identifier compareop leftwardop rightwardop binop

%token <string> SYMBOLIC_CONSTANT NUMBER VARIABLE STRING
%token <string> EQUAL UNEQUAL LESS GREATER LESS_OR_EQ GREATER_OR_EQ
%token <string> AGGR_COUNT AGGR_MAX AGGR_MIN AGGR_SUM ANON_VAR

%token ERROR NEWLINE   

%token DOT DDOT SEMICOLON COLON CONS QUERY_MARK

%token PLUS TIMES SLASH

%token PARAM_OPEN PARAM_CLOSE
%token SQUARE_OPEN SQUARE_CLOSE
%token CURLY_OPEN CURLY_CLOSE

%token DASH COMMA NAF AT WCONS

%token VEL EXISTS

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
    : rules rule
    | rule
    ;

rule
    : head DOT 
        { 
            InputDirector::getInstance().getBuilder()->onRule(); 
        }
    | head CONS DOT 
        {
            InputDirector::getInstance().getBuilder()->onRule(); 
        }
    | head CONS body DOT 
        { 
            InputDirector::getInstance().getBuilder()->onRule(); 
        }
    | CONS body DOT /*constraint*/ 
        { 
            InputDirector::getInstance().getBuilder()->onConstraint(); 
        }
    | WCONS body DOT weight_at_levels 
        { 
            InputDirector::getInstance().getBuilder()->onWeakConstraint(); 
        }
    ;

head
    : disjunction
        {
            InputDirector::getInstance().getBuilder()->onHead();
        }
    | choice_atom 
        {
            InputDirector::getInstance().getBuilder()->onChoiceAtom();
            InputDirector::getInstance().getBuilder()->onHead();
        }
    ;       

body
    : conjunction 
        {
            InputDirector::getInstance().getBuilder()->onBody();
        }
    ;

weight_at_levels 
    : SQUARE_OPEN term SQUARE_CLOSE 
        {
            // There is only the weight. No level and terms.
            InputDirector::getInstance().getBuilder()->onWeightAtLevels(1,0,0); 
        }
    | SQUARE_OPEN term levels_and_terms SQUARE_CLOSE 
        {
            // There are also a level and/or some terms.
            // The finalization has been postponed to "level_and_terms".
        }
    ;

levels_and_terms 
    : AT term 
        {
            // There is no terms following the level.
            InputDirector::getInstance().getBuilder()->onWeightAtLevels(1,1,0); 
        } 
    | AT term COMMA terms 
        { 
            InputDirector::getInstance().getBuilder()->onWeightAtLevels(1,1,$4); 
        }
    | COMMA terms 
        { 
            // The level is omitted.
            // Thus, the first term, recognized as the
            // weight, should be a term of this list.
            InputDirector::getInstance().getBuilder()->onWeightAtLevels(0,0,$2+1); 
        } 
    ;
          
disjunction
    : classic_literal 
        { 
            InputDirector::getInstance().getBuilder()->onHeadAtom(); 
        }
    | disjunction HEAD_SEPARATOR classic_literal 
        { 
            InputDirector::getInstance().getBuilder()->onHeadAtom(); 
        }
    | existential_atom 
        { 
            InputDirector::getInstance().getBuilder()->onHeadAtom(); 
        }
    | disjunction HEAD_SEPARATOR existential_atom 
        { 
            InputDirector::getInstance().getBuilder()->onHeadAtom(); 
        }
    ;

conjunction
    : naf_literal_aggregate 
        { 
            InputDirector::getInstance().getBuilder()->onBodyLiteral(); 
        }
    | conjunction COMMA naf_literal_aggregate 
        { 
            InputDirector::getInstance().getBuilder()->onBodyLiteral(); 
        }
    ;

choice_atom 
    : lower_guard CURLY_OPEN choice_elements CURLY_CLOSE upper_guard 
    | lower_guard CURLY_OPEN choice_elements CURLY_CLOSE 
    | CURLY_OPEN choice_elements CURLY_CLOSE 
    | CURLY_OPEN choice_elements CURLY_CLOSE upper_guard 
    ;

lower_guard
    : term binop 
        { 
            InputDirector::getInstance().getBuilder()->onChoiceLowerGuard($2); 
            delete[] $2;
        } 
    ;

upper_guard
    : binop term 
        { 
            InputDirector::getInstance().getBuilder()->onChoiceUpperGuard($1); 
            delete[] $1;
        }
    ;

choice_elements 
    : choice_elements SEMICOLON choice_element
    | choice_element
    ;

choice_element 
    : choice_element_atom 
        {
            InputDirector::getInstance().getBuilder()->onChoiceElement(); 
        }
    | choice_element_atom COLON choice_elements_literals 
        {
            InputDirector::getInstance().getBuilder()->onChoiceElement(); 
        }
    ;

choice_element_atom 
    : atom 
        {
            InputDirector::getInstance().getBuilder()->onChoiceElementAtom(); 
        }
    ;

choice_elements_literals
    : naf_literal 
        { 
            InputDirector::getInstance().getBuilder()->onChoiceElementLiteral(); 
        }
    | choice_elements_literals COMMA naf_literal 
        {
            InputDirector::getInstance().getBuilder()->onChoiceElementLiteral();
        }
    ;    

naf_literals
    : naf_literal
        {
            InputDirector::getInstance().getBuilder()->onAggregateNafLiteral();
        }
    | naf_literals COMMA naf_literal
        {
            InputDirector::getInstance().getBuilder()->onAggregateNafLiteral();
        }
    ;    
          
naf_literal
    : classic_literal 
        { 
            InputDirector::getInstance().getBuilder()->onNafLiteral();
        }
    | NAF classic_literal 
        { 
            InputDirector::getInstance().getBuilder()->onNafLiteral(true);
        }
    | builtin_atom 
        {
            InputDirector::getInstance().getBuilder()->onNafLiteral();
        }
    ;

naf_literal_aggregate
    : naf_literal
    | aggregate_atom
        {
            InputDirector::getInstance().getBuilder()->onAggregate();
        }
    | NAF aggregate_atom
        {
            InputDirector::getInstance().getBuilder()->onAggregate(true);
        }
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
    : identifier 
        { 
            InputDirector::getInstance().getBuilder()->onPredicateName($1); 
            delete[] $1;
        }
    | identifier PARAM_OPEN terms PARAM_CLOSE 
        { 
            InputDirector::getInstance().getBuilder()->onPredicateName($1); 
            delete[] $1;
        }
    | identifier PARAM_OPEN PARAM_CLOSE 
        { 
            InputDirector::getInstance().getBuilder()->onPredicateName($1); 
            delete[] $1;
        }
    ;              
         
terms
    : term { $$ = 1; }
    | terms COMMA term { $$ = $1 + 1; }
    ;

basic_terms 
    : basic_term
    | basic_terms COMMA basic_term
    ;

builtin_atom
    : term binop term 
        {
            InputDirector::getInstance().getBuilder()->onBuiltinAtom($2);  
            delete[] $2;
        }
    ;

compareop 
    : EQUAL   { $$ = $1; } 
    | UNEQUAL { $$ = $1; }
    ;       
         
binop    
    : compareop   { $$ = $1; } 
    | leftwardop  { $$ = $1; }
    | rightwardop { $$ = $1; }
    ;       
         
arithop   
    : PLUS  { $$ = '+'; } 
    | DASH  { $$ = '-'; }      
    | TIMES { $$ = '*'; }
    | SLASH { $$ = '/'; }
    ;      

ddt
    : 
    |
    DDOT NUMBER
    ;
    
term_ 
    : identifier 
        { 
            InputDirector::getInstance().getBuilder()->onTerm($1); 
            delete[] $1;
        }
    | NUMBER ddt 
        { 
            InputDirector::getInstance().getBuilder()->onTerm($1); 
            delete[] $1;
        }
    | ANON_VAR 
        { 
            InputDirector::getInstance().getBuilder()->onTerm($1); 
            delete[] $1;
        }
    | identifier PARAM_OPEN terms PARAM_CLOSE 
        { 
            InputDirector::getInstance().getBuilder()->onFunction($1, $3); 
            delete[] $1;
        }
    | PARAM_OPEN term PARAM_CLOSE 
        { 
            InputDirector::getInstance().getBuilder()->onTermParams(); 
        }
    | DASH term 
        { 
            InputDirector::getInstance().getBuilder()->onTermDash(); 
        }
    ;

term
    : term_ {}
    | term arithop term_ 
        { 
            InputDirector::getInstance().getBuilder()->onArithmeticOperation($2); 
        }
    ;        

basic_term : ground_term {}
       | variable_term {}
       ;

ground_term 
    : SYMBOLIC_CONSTANT 
        {
            InputDirector::getInstance().getBuilder()->onAggregateGroundTerm($1);
            delete[] $1;
        }
    | STRING 
        {
            InputDirector::getInstance().getBuilder()->onAggregateGroundTerm($1);
            delete[] $1;
        }
    | NUMBER
        {
            InputDirector::getInstance().getBuilder()->onAggregateGroundTerm($1);
            delete[] $1;
        }
    | DASH NUMBER
        {
            InputDirector::getInstance().getBuilder()->onAggregateGroundTerm($2,true);
            delete[] $2;
        }
    ;

variable_term 
    : VARIABLE
        { 
            InputDirector::getInstance().getBuilder()->onAggregateVariableTerm($1);
            delete[] $1;
        }
    | ANON_VAR
        {
            InputDirector::getInstance().getBuilder()->onAggregateVariableTerm($1);
            delete[] $1;
        }
    ;

vars
    : VARIABLE 
        { 
            InputDirector::getInstance().getBuilder()->onExistentialVariable($1); 
            delete[] $1;
        }
    | vars COMMA VARIABLE 
        { 
            InputDirector::getInstance().getBuilder()->onExistentialVariable($3);
            delete[] $3;
        }
    ;

identifier
    : SYMBOLIC_CONSTANT { $$ = $1; }
    | STRING { $$ = $1; }
    | VARIABLE { $$ = $1; }
    ;
                
query     
    : atom QUERY_MARK 
        { 
            InputDirector::getInstance().getBuilder()->onAtom(); 
        }
    ; 

lower_guard_compare_aggregate
    : term compareop
        {
            InputDirector::getInstance().getBuilder()->onAggregateLowerGuard($2);
            delete[] $2;
        }
    ;

upper_guard_compare_aggregate
    : compareop term
        {
            InputDirector::getInstance().getBuilder()->onAggregateUpperGuard($1);
            delete[] $1;
        }
    ;

compare_aggregate 
    : lower_guard_compare_aggregate aggregate 
    | aggregate upper_guard_compare_aggregate
    ;

lower_guard_leftward_left_aggregate
    : term leftwardop
        {
            InputDirector::getInstance().getBuilder()->onAggregateLowerGuard($2);
            delete[] $2;
        }
    ;

leftward_left_aggregate  
    : lower_guard_leftward_left_aggregate aggregate
    ;

left_aggregate 
    : leftward_left_aggregate
    | rightward_left_aggregate 
    ;

lower_guard_rightward_left_aggregate
    : term rightwardop
        {
            InputDirector::getInstance().getBuilder()->onAggregateLowerGuard($2);
            delete[] $2;
        }
    ;

rightward_left_aggregate  
    : lower_guard_rightward_left_aggregate aggregate
    ;

upper_guard_leftward_right_aggregate
    : leftwardop term
        {
            InputDirector::getInstance().getBuilder()->onAggregateUpperGuard($1);
            delete[] $1;
        }
    ;

upper_guard_rightward_right_aggregate
    : rightwardop term
        {
            InputDirector::getInstance().getBuilder()->onAggregateUpperGuard($1);
            delete[] $1;
        }
    ;

right_aggregate 
    : aggregate upper_guard_leftward_right_aggregate
    | aggregate upper_guard_rightward_right_aggregate
    ;

aggregate_atom
    : left_aggregate
    | right_aggregate
    | compare_aggregate
    | leftward_left_aggregate upper_guard_leftward_right_aggregate
    | rightward_left_aggregate upper_guard_rightward_right_aggregate 
    ;   

leftwardop 
    : LESS { $$ = $1; }
    | LESS_OR_EQ { $$ = $1; }
    ;    

rightwardop 
    : GREATER { $$ = $1; }
    | GREATER_OR_EQ { $$ = $1; }
    ;           
            
aggregate  
    : aggregate_function CURLY_OPEN aggregate_elements CURLY_CLOSE
    ;

aggregate_elements 
    : aggregate_elements SEMICOLON aggregate_element
    | aggregate_element
    ;
        
            
aggregate_element 
    : basic_terms COLON naf_literals
        {
            InputDirector::getInstance().getBuilder()->onAggregateElement();
        }
    ;

aggregate_function  
    : AGGR_COUNT 
        {
            InputDirector::getInstance().getBuilder()->onAggregateFunction($1);
            delete[] $1;
        }
    | AGGR_MAX
        {
            InputDirector::getInstance().getBuilder()->onAggregateFunction($1);
            delete[] $1;
        }
    | AGGR_MIN
        {
            InputDirector::getInstance().getBuilder()->onAggregateFunction($1);
            delete[] $1;
        }
    | AGGR_SUM
        {
            InputDirector::getInstance().getBuilder()->onAggregateFunction($1);
            delete[] $1;
        }
    ;   
