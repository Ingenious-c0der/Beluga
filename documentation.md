# Welcome to Beluga Docs!

![image](https://user-images.githubusercontent.com/76046349/216764405-f1192bd6-1410-409f-9538-520808d92672.png)

### Different language features and how-to's are explained in this document.

## What is the goal of Beluga?

Beluga is a Turing Machine simulator, and a Turing Machine compiler. It is designed to be simple, and easy to understand. In theory , it is capable of solving any problem that can be solved by a turing machine/ digital computer. Beluga supports multi tape turing machines.

## Current State of Beluga :

As of now (Aug 2023), the language compiles and executes only for a limited tested set of turing machines. The language is still in development, and is not ready for production use in any way.
To support this language:

- Please create your own turing machines and create a PR to the repo.
- In the process, if you find any bugs, please create an issue in the repo.

Doing so will help the language grow and mature.

## Okay, but what's the USE?
Beluga allows the ease to build a turing machines while being as close as possible to their mathematical representation to define them. This allows the user to focus on the logic of the turing machine rather than the syntax of the language. The language is designed to be simple, and easy to understand.
As of now, I can think of the following two prospects of using Beluga in the near future: 
### 1. Regular Expressions Matching : 
While this is a herculian task to achieve, it is possible to achieve this using Beluga. The idea is to build a turing machine which can match a given regular expression in linear time once the machine is contructed.This is a NP problem and linear regex matching as seen in google/re2 is built with the same idea but uses finite automata instead. 
The turing machine can be pipelined with other turing machines to achieve complex regular expressions.This would require the development of a regex transpiler which can convert a regex to a beluga turing machine, and I am currently working on this whenever I find time.

### 2. Educational Purposes :
The TM knowledge needed to code in beluga is something which is taught in any Theory of Computation class, you don't need to know any programming language/fundamentals to code in beluga. This makes it a great tool to teach the basics of turing machines to students.

### The race to build the first decimal/binary/unary adder. 
Again, constructing anything with a TM is a tough shot without having the right constucts. Right now I am planning to develop the constructs which can ease the process of building a universal adder or multiplier while maintaining the simplicity of the language. Once that is in place, this fundamental TM can be used/imported to construct heavier TMs and which will potentially increase the use cases of the language.





## Command Line Flags 
The language will have more command line flags in the future. As of now, the following flags are supported :
### 1. - t : execution time debug flag 
The time debug flags allows you to view the time taken for each process when running the .beluga file.The execution time is printed in nanoseconds. The time debug flag is useful to debug the performance of the language and your TM structure.
Lexing, Parsing, Machine name uniqueness check and Topological sorting are timed for the entire program at once and not for individual machine
It provides the execution time for each machine, and the total execution time for the program.
Usage : 
```c#
Beluga  <filename.beluga> -t
```
Output/s : 
```c#
Lexing time: 0 nanoseconds
Parsing time: 1089000 nanoseconds
Machine name uniqueness check time: 0 nanoseconds
Topological sorting time: 0 nanoseconds
unary_multiplier (Accepted) : 
t0 : 11B
t1 : K1111111B
t2 : 11111111111111
Machine unary_multiplier execution time: 2014000 nanoseconds
Total execution time: 11318000 nanoseconds
```
```c#
Lexing time: 0 nanoseconds
Parsing time: 1210000 nanoseconds
Machine name uniqueness check time: 0 nanoseconds
Topological sorting time: 0 nanoseconds
pipe_1 (Accepted) :
t0 : 2222222222B
Machine pipe_1 execution time: 1002000 nanoseconds
pipe_2 (Accepted) :
t0 : 3333333333B
Machine pipe_2 execution time: 913000 nanoseconds
Total execution time: 10240000 nanoseconds
```

 



## What are the constructs of Beluga?

Beluga at the moment comprises of and supports the following constructs:

### Consumes Construct :

The Consume Construct is a gatekeeper for accepting tapes from other turing machines which relay to the current Turing machine.
The whole idea of the consume construct is to allow Turing machines to be pipelined and run in a topologically sound order.
Consumes can take the following parameters: - null : This is the default value, and means that the current Turing machine accepts tapes from no other Turing machine. - Turing Machine Name/s : This means that the current Turing machine accepts tapes from the Turing machine with the name/s specified.
Syntax :

```c#
consumes : (null)
/* OR */
consumes : (TuringMachine1,TuringMachine2,TuringMachine3)
```

Consumes should be placed at the top of the Turing machine definition body.

### Tape Construct :

The Tape construct is used to define the tape/s of the Turing machine. The tape construct can take the following parameters: - Tape Name : This is the name of the tape. The tape name can be any string, and is used to identify the tape. - Tape Content : This is the content of the tape. The tape content can be any string, and is used to initialize the tape.
Syntax :

```c#
tape : ({TapeName,TapeContent},..,{TapeName,TapeContent})
```

### Def Construct :

The Def or Definition constructs houses several other definitions of the Turing machine, which are (in order)

- Finite Set of States
- Finite Set of Input Symbols
- Finite Set of Transitions
- Initial State
- Blank Symbol
- Final State/s
  Defining all of these in Def construct is necessary for the Turing machine to be compiled and executed.

### Transition Construct :

A single transition construct is standard row from a transition table defining :

- Current State
- Read Symbol
- Next State
- Write Symbol
- Direction of Movement
- Current Tape
- Next Tape
  Syntax :

```c#
 {
    (CurrentState,ReadSymbol,NextState,WriteSymbol,Direction,CurrentTape,NextTape),
    ..,
    (CurrentState,ReadSymbol,NextState,WriteSymbol,Direction,CurrentTape,NextTape)
}
```

### IgnoreUnknowns Construct : 
This construct is used to ignore unknown write symbols in transitions. If the value of this Construct is set to reject, the Turing machine will halt if it encounters an unknown symbol in/during the transition.
Syntax :
```c#
ignoreUnknowns : (accept)
/* OR */
ignoreUnknowns : (reject)
```

### Relay Constuct : 
This construct complements the consumes construct. It is used to relay tapes to other Turing machines. The relay can be success based or failure based using onAccept and onReject attributes respectively.
The relay construct can take the following parameters:
 - null : This is the default value, and means that the current Turing machine relays tapes to no other Turing machine.
 - Turing Machine Name/s : This means that the current Turing machine relays tapes to the Turing machine with the name/s specified.
 - Console : This means that the current Turing machine relays tapes to the console.
Syntax:
```c#
relay : {
        onAccept: (console) /* available relays are console, null,turing Machine(pipelined) */
        onReject: (null) /* available relays are console, null,turing Machine (pipelined) */
    }
/* OR */
relay : {
        onAccept: (console, TuringMachine1..,TuringMachineN) /* available relays are console, null,turing Machine(pipelined) */
        onReject: (console, TuringMachine2..,TuringMachineN) /* available relays are console, null,turing Machine (pipelined) */
    }
    /* OR */
relay : {
        onAccept: (null) /* available relays are console, null,turing Machine(pipelined) */
        onReject: (null) /* available relays are console, null,turing Machine (pipelined) */
    }
```
#### Note : If turing machine A relays to turing machine B , and turing machine B does not explicitly consume from turing machine A , then turing machine B will not accept the tapes from turing machine A.

### Using the Consumes and Relay constructs properly : 
Piping different turing machines can be an essential tool to solve complex problems without using complex logic. If turing machine A relays to B and B consumes A , it is logically known that A should execute before B. Two machines or more machines which are tied with this sort of consume-relay relationship will be always topologically executed irrespective of the order in which they are defined in the program. The unrelated machines will be executed in undeterministic order. 




### FAQs 
#### Reserved Keywords :
- consumes
- machine
- tape
- def
- transition
- ignoreUnknowns
- relay
- onAccept
- onReject
- null
- console
- accept
- reject
- import
- from 

#### Reserved Symbols :
- ( ) : Parenthesis Symbols
- { } : Curly Braces Symbols
- ,   : Comma Symbol
- :   : Colon Symbol
- =>  : Fat Arrow Symbol
- $   : Dollar Symbol
- #_# : Infinite Tape Symbol


### Infinite Tape Symbol (#_#)
This feature is supported from beluga version 0.0.3 !
It makes the language more powerful and closer to an actual turing machine repr. You can now represent an infinite tape and use it in your TM!  
#### Details 
For a lack of better symbols, the symbol "#_#" is reserved for depicting infinite tapes (Could be changed in the future)
as seen in examples/infinite_tape.beluga
You can also have multiple infinite tapes in a single machine.
```c#
tape : ({t0,#_#},{t1,ABDBAEW})
```
In the above code block, we use #_# to represent an infinite tape. The tape t0 is an infinite tape. The tape t1 is a finite tape.You cannot describe a repeating pattern in the infinite tape as of now. 

#### How does it work?
The infinite tape is basically implemented internally as a growing vector in both directions as and when the pointer overflows the current scope of the tape. The default element in the infinite tape is the "#" symbol. It can be changed/updated and stored in the tape as any other symbol.


### $  : Dollar Symbol 
Internally the dollar symbol is always appended at the both ends of tapes marking the absolute start and end of the tape. This is done to avoid out of bounds errors while reading the tape. The dollar symbol is not visible to the user.
If you get an Error "Unexpectedly hit the hard tape end : '$'", it means that the transition has evaded your bounding logic and has hit the absolute start/end of the tape. To resolve this error make sure that you are not moving left or right on any corner symbols of the tape. 

#### Should the order of appearance of constructs be maintained?
- Yes, the order of appearance of constructs should be maintained. The order of appearance of constructs is important for the language to be compiled and executed.

#### Can I use the same tape name in different tapes?
- No, the tape name should be unique. The tape name is used to identify the tape.

#### Can I use the same state name in different states?
- No, the state name should be unique. The state name is used to identify the state.

#### Can I use the same transition name in different transitions?
- Yes, the language does not care if you re-state the same transition in different ways.

#### Can state,tape,machine names be numbers/long strings?
- Yes, the names can be any string / combination of unreserved symbols.

#### Can I use the same machine name in different machines?
- No, the machine name should be unique. The machine name is used to identify the machine.

#### Error : Cyclic Dependency (Deadlock) detected between Turing Machines :
- This error is thrown when the Turing machines are pipelined in a cyclic manner. This error is thrown during the compilation phase. To resolve this error, make sure that the Turing machines are pipelined in a topologically sound manner.
For example if Turing machine A relays to Turing machine B and Turing machine B relays to Turing machine C, then Turing machine C should not relay to Turing machine A.

#### Error : Tape Name Clash :
- This error is thrown when Turing machine A relays its tapes to turing machine B and turing machine B already has a tape named the same as one of the tapes relayed by Turing machine A. This error is thrown during the compilation phase. To resolve this error,make sure that tape names are unique across pipelined Turing machines.
Example : 
 T.M. A with tapes {t0,t1,t2} relays to T.M. B with tapes {t0,t3,t4} will throw an error because T.M. B already has a tape named t0.To resolve, simply rename the tapes in T.M. B to {t5,t3,t4}.

### Question/ Error not listed here? 
- Please create an issue in the repo.

