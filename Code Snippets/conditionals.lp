SET true := 84
SET false := 70
STR str_true = true
STR str_false = false
SET x := 0
SET y := 0
MOV STDIN -> x
MOV STDIN -> y
CHECK 2 x=y
MOV str_true -> STDOUT
MOV str_false -> STDOUT
CHECK 2 x!=y
MOV str_true -> STDOUT
JMP 16
MOV str_false -> STDOUT
CHECK 2 x<=y
MOV str_true -> STDOUT
JMP 20
MOV str_false -> STDOUT