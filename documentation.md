# Welcome to Beluga Docs!

![image](https://user-images.githubusercontent.com/76046349/216764405-f1192bd6-1410-409f-9538-520808d92672.png)

### Different language features and how-to's are explained in this document.

## What is the goal of Beluga?

Beluga is a Turing Machine simulator, and a Turing Machine compiler. It is designed to be simple, and easy to understand. In theory , it is capable of solving any problem that can be solved by a turing machine/ digital computer. Beluga supports multi tape turing machines.

## Current State of Beluga :

As of now (Feb 2023), the language compiles and executes only for a limited tested set of turing machines. The language is still in development, and is not ready for production use in any way.
To support this language:

- Please create your own turing machines and create a PR to the repo.
- In the process, if you find any bugs, please create an issue in the repo.

Doing so will help the language grow and mature.

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

#### Reserved Symbols :
- ( )
- { }
- ,
- :
- => 

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

### Question/ Error not listed here? 
- Please create an issue in the repo.

