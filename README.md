# Beluga
![logo](https://user-images.githubusercontent.com/76046349/215174192-1318ff0d-f4c1-466f-8896-a5893899429a.png)


Beluga Language is an esoteric programming language based on fundamental implementations of a turing machine. 
As of now, its in active development (Just Started Out!), and mimics the model of a Linear Bounded Automata and sooner that of a general 
turing machine(with finite tape). 

## [How to run Beluga on windows](https://github.com/Ingenious-c0der/Beluga/blob/master/README.md#installation) ?  

### [Read the docs](https://github.com/Ingenious-c0der/Beluga/blob/master/documentation.md#welcome-to-beluga-docs)
You now have the power to directly write and run turing machines!

### Sample Beluga Code (According to current design decisions)

first.beluga
```c#

 machine (beluga) => {
    consumes : (null) 
    tape : ({t0,abbb^bab^bab},{t1,abbb^bbedr^})
    def: (
            {q0,q1} /* finite set of states */
            {a,b} /* finite set of input symbols */
            {
                (q0,a,q0,a,->,t0,t0), /* transition */
                (q0,b,q0,b,<-,t0,t1), /* transition */
                (q0,^,q1,^,->,t0,t1), /* transition */
                (q1,a,q1,a,->,t1,t1), /* transition */
                (q1,b,q1,b,->,t1,t1), /* transition */
                (q1,^,q1,^,->,t0,t0), /* transition */
             } /* finite set of transitions */
            (q0) /* initial state  */
            (^) /* blank symbol  */
            (q1) /* final states */
         ) /* tuple of 6 entities  */
    ignoreUnknowns : (accept) /* ignore unknown tape symbols, basic booleans are accept (true) and reject (false) */ 
    relay : {
        onAccept: (console) /* available relays are console, null,turing Machine(pipelined) */
        onReject: (null) /* available relays are console, null,turing Machine (pipelined) */
    }
}
```
helloworld.beluga
```c#
machine (helloWorld!) => {
    consumes : (null) 
    tape : ({outputTape,^HelloWorld!^})
    def: (
            {q0,exit} /* finite set of states */
            {H,e,l,o,W,o,r,d,!} /* finite set of input symbols */
            {
                (q0,l,q0,l,->,outputTape,outputTape), /* transition */
                (q0,^,q0,^,->,outputTape,outputTape), /* transition */
                (q0,H,q0,H,->,outputTape,outputTape), /* transition */
                (q0,e,q0,e,->,outputTape,outputTape), /* transition */
                (q0,o,q0,o,->,outputTape,outputTape), /* transition */
                (q0,W,q0,W,->,outputTape,outputTape), /* transition */
                (q0,r,q0,r,->,outputTape,outputTape), /* transition */
                (q0,d,q0,d,->,outputTape,outputTape), /* transition */
                (q0,!,exit,!,->,outputTape,outputTape) /* transition */
            } /* finite set of transitions */
            (q0) /* initial state  */
            (^) /* blank symbol  */
            (exit) /* final states */
         ) /* tuple of 6 entities  */
    ignoreUnknowns : (accept) /* ignore unknown tape symbols, basic booleans are accept (true) and reject (false) */ 
    relay : {
        onAccept: (console) /* available relays are console, null,turing Machine(pipelined) */
        onReject: (console) /* available relays are console, null,turing Machine (pipelined) */
    }
}
```
Output
```c#
helloWorld! (Accept) : 
outputTape : ^HelloWorld!^
```

##### custom syntax highlighting Soon™

The language is designed to be simple, and easy to understand. In theory , it is capable of solving any problem that can be solved by a turing machine/ digital computer. Beluga supports multi tape turing machines


## Installation 

### Windows 
#### 1. Download the beluga exe file from [here](https://github.com/Ingenious-c0der/Beluga/releases/download/v0.0.2/Beluga.exe)
#### 2. Add the directory in which the exe is downloaded to your *PATH* variable
for example if the beluga.exe lies in C:/Users/username/Desktop/src/beluga.exe then C:/Users/username/Desktop/src should be the path
#### 3. You are good to go!
Run the file as Beluga <filename.beluga>

![image](https://user-images.githubusercontent.com/76046349/216761110-0dfd9be5-f993-4a61-89e5-601086684d6d.png)

