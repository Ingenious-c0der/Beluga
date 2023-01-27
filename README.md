# Beluga
![logo](https://user-images.githubusercontent.com/76046349/215174192-1318ff0d-f4c1-466f-8896-a5893899429a.png)


Beluga Language is an esoteric language based on fundamental implementations of a turing machine. 
As of now, its in active development (Just Started Out!), and mimics the model of a Linear Bounded Automata and sooner that of a general 
turing machine(with finite tape). 

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
            (
                (q0,a,q0,a,->,t0,t0), /* transition */
                (q0,b,q0,b,<-,t0,t1), /* transition */
                (q0,^,q1,^,->,t0,t1), /* transition */
                (q1,a,q1,a,->,t1,t1), /* transition */
                (q1,b,q1,b,->,t1,t1), /* transition */
                (q1,^,q1,^,->,t0,t0), /* transition */
            ) /* finite set of transitions */
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
##### custom syntax highlighting Soon™

The language is designed to be simple, and easy to understand. In theory , it is capable of solving any problem that can be solved by a turing machine/ digital computer. Beluga supports multi tape turing machines

The language uses C++ for compilation, so you need a C++ compiler to compile beluga code.
