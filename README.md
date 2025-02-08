# Sat-Solver
This is a set of toy implementations to learn about different SAT Solver techniques and algorithms.

## Input specification
The input to the solver is a list of newline seperated terms.
Each term is generated using this grammar in BNF form:

```
<start> ::= "(" <term> ")"
<term> ::= <literal> | <literal> <connective> <literal> | <literal> <connective> "(" <term> ")" | "NOT" "(" <term> ")" 
<literal> ::= "variable" | "(NOT variable)"
<connective> ::= " AND " | " OR " 
```

```
<start> :: = "(" <term> ")"
<term> ::= literal | literal connective literal
<literal> ::= "variable" | "NOT variable"
