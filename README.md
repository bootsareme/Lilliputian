# Lilliputian Assembly Language (LILLI)
Lilliputian is an interpreted psuedo-assembly language that is written in C++. While it is not a true assembly language, it mimics the behavior of actual assemblies. The name "Lilliputian" comes from the 1726 novel Gulliver's Travels by Jonathan Swift. The word lilliputian has become an adjective meaning "very small in size", which is fitting to this assembly language as it was not meant to have the full capabillities of an x86 or NASM assembler.

<h2>Downloads</h2>
Lilliputian can be ran as a standalone executable. Your browser will probably warn you that it is a virus but don't fret, the source code is for you to judge. You can also view code snippets inside the "Snippets" folder for examples of Lilliputian assembly code. If the .exe file prints nothing, you might be missing some C++ redistributable frameworks. Download the latest ones here: https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads.

<h2>Background</h2>
Lilliputian programs take on the file extension of (.lp). They can be executed through a CLI by running this command:

```
lilli program.lp
```
An instruction in Lilliputian is takes on the form of one single line. It may look something like this:

```
MOV x -> STDOUT
```
Within an instruction statement, there are 4 parts (all separated by spaces).

```
MOV - Opcode: The command that modifies the arguments.
x and STDOUT - Operands: The parameters of the opcodes.
"->" - Operator: Helps the opcode bind two operands together.
```
The SETault variable type is an integer. Strings do not exist in Lilliputian and must be converted to an ASCII value through STR. STRs are variable types that specialize in representing strings. Using the STR opcode implies that the operand on the right side have already-defined integer variables. There are two reserved variables, STDIN and STDOUT (it must be in ALL-CAPS), that represents the input and output streams of the program, respectively. It is used to print long strings (MOV x -> STDOUT) or take user input (MOV STDIN -> x). Using the "MOV" function for a string will automatically create a newline for each iteration when "MOV" is called.

<h2>Control Flow</h2>
Lilliputian supports IF statements and their behavior is very simple. The number proceeding immediately after the CHECK opcode displays how many lines after the original statement the IF statement should consider for. If the condition is not met, skip past the specified amount of lines MINUS ITSELF AS A LINE. Note the spaces between each segment. When using CHECK statements, both variables have to be a single character, comparing mutiple words (foo<=baz) is not allowed, instead use (f<=b). 

```
CHECK 5 x=y // Equal to; Next 5 statements, inside IF block.
CHECK 4 x!=y // NOT Equal to; Next 4 statements, inside IF block
CHECK 6 x<=y // Less than equal to; Next 6 statements, inside IF block
```
Jump statements are also included in the language and it only has one operand that you can modify:

```
JMP 123 - Jumps to lines 123.
JMP x - Jumps to value stored in x.
```
This can be used in conjunction with CHECK statements to create while or for loops. Here is a simple for loop statement that prints the integers from 1 to 10.

```
SET i := 1
SET a := 10
SET m := 0
ARITH i + m
MOV m -> STDOUT
CHECK 2 a!=m
JMP 4
```
Because CHECK statements have to be a single character for each variable, a statement, DEL (delete) comes into play here. It is used to delete unused variables therefore freeing space so new variables can be assigned. To use the delete statement:

```
DEL x 
```
Another opcode, INT, interrupts the thread for the specified amount of milliseconds (ms). This instruction will pause the thread for exactly 1 second (1000 ms):

```
INT 1000
```
That is it for now, although Lilliputian is far from finished. Please report any bugs you find in the "Issues" section and the most upvoted one will be prioritized to be fixed first. Check out the bottom table for a list of Opcodes.

<h2>Opcodes</h2>

| Opcode | Description |
| --- | --- |
| SET x := y | Sets variable called x the value of y. |
| MOV x -> y | Moves the value of x into y. |
| ARITH x � y | Performs arithmetic on x and y and saves the results to y. (+, -, �, �) |
| STR x = y,z | Creates a string x and joins the ASCII values of y and z. |
| CHECK 123 x=y | If condition is met, run the next 123 lines and return back to main thread. Otherwise skip the next 123 lines. |
| JMP 123/x | Jumps to line number 123/(value @ x). CAUTION: If left unhandled, it may cause infinite loops. |
| DEL x | Deletes the variable x from scope entirely. |
| INT 1234 | Pauses the thread for 1234 ms (milliseconds). |


<h2>Conventions</h2>
While not required, some conventions are put in place to simplify workflow. The following naming conventions are listed below:

* All user-defined variables shall be in lowercase.
* Built-in functions and variables should be in ALL-CAPS.
* All STR variables should have an lowercase "str_" in front of the variable name (ex. "str_var").
* Do not put new lines between your code, it may cause unwanted behavior.