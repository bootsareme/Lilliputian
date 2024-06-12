SET a := 0
SET b := 1
SET c := 0
SET i := 1
SET n := 10
MOV STDIN -> n
SET one := 1
CHECK 7 i!=n
MOV a -> STDOUT
ARITH b + a
MOV a -> c
MOV b -> a
MOV c -> b
ARITH one + i
JMP 8