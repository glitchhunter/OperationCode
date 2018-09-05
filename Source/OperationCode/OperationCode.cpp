// Fill out your copyright notice in the Description page of Project Settings.

#include "OperationCode.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, OperationCode, "OperationCode" );


/* TODO:


- Add Pass by reference to function parameters
- Add const to functions and function parameters
- Add final to functions
- Add static to functions
- Using proper function signature, fix symbol table
- Refactor how the functions are stored. Function signature does not take into consideration some data (const params and function itself, pass by reference params and return type, parameter names)
- Allow function overrides to return derived types
- Redefine operator overloads from c++ style to c# style (static with all arguments)
- Redo function and operator management. Seriously, shits fucked up. Everything is commented so it can compile. DO NOT RUN!

- Finish A_FunctionCall
- UValues need references to class definitions they represent
- Add action for function definition (UA_FunctioNDefinition, which actualy runs the function)
- Basic and Main should not queue children actions if child is function definition
- Add "unique" keyword to mark classes that they should be created as pointers (C# class vs struct)
- Turn AST_Nodes to data classes (remove getters and setters)
- Find a way to differentiate between prefix and sufix increment and decrement

- Find out why some class inheritance code crashes. NOTE: Defined functions differ every time it is run, until crash. Maybe stored data asset keeps data between sessiosn?


- Differentiate between variable names and types. a.function(), a can be a variable, or a type on which a static function is called. Semantic analysis needed.
- Create expression analysis. It makes sure every type used in code exists, all types are compatible with functions, converts variable names to types where aplicable, adds conversion functions where aplicable.
- Create flow control analyser. It makes sure breaks and continues are inside loops, and that all execution paths inside non-void functions return a value.
- Create a PasByReference analyser (or implement it in expression analysis) that checks that all pass by reference arguments and returns are variables instead of literals.




- Accept you lost. Create a satic member access operator (::) which will keep a type as caller.
- This means type no longer needs to be an expression, and all the expression problems it caused are gone.
- Converting variable calls to types will still be necesary. This also means taht member access nodes will have
- to be converted to static member access nodes if variable call gets converted to type.

- Accepting I lost is too easy, and therefore not allowed. Making static member access a different operator,
- I still have issues with type having to be an expression.
- Current idea is to store expression returns in a struct instead of just using a string.
- That way I can tell if we return a value or type, as well as have the option to know we if use an array or not in the future.

- If an operator overload that is defined in two different classes is detected only if it's called. Move that code from Expression analysis to operator analysis.

- Make sure static functions do not use instance members.

- Everything in semantic analysis I can think of is done (untested, yay!) except for flow controll analysis and implicit conversion

- Flow controll has been split in two parts, flow controll for loops, and return analysis for returns. Both have been completed.
- Could easely add detection for certain hardcoded condition (eg. while(true)) but there are more importatn things left to do
- Other then line number for errors, only type conversion needs to be done, and then I can reach the final phase at last (again).

- My fucking mouse wheel just died for no reason whatsoever.
- Need to check for function calls in expression analysis. Prefer functions signature that require no conversions.
- If there are multiple signatures that fit with conversions, then just throw an error for ambiguous function calls.
- Place that code in symbol table so it can be reused during code execution.
- Almost other then function calls, everything that returns or uses a value must change to support conversion.
- This includes function calls, operators, variable ect in expression analysis, as well as potentially other phases.
- Need to make a pass through all of them to verify. Good chance to also add "prerequisites" to phases, to quickly
- figure what phases need to run before other phases.

- Symbol table can now see if a function call matches a function signature. Inheritance and implicit conversions taken in account.
- Next step is to store static function and variable calls to definitions in symbol table. (Static analysis store)
- Expression analysis must also change to use sgnature comparison to find correct return values. 
- However expression analysis is done before static analysis, so it will do twice the work for static stuff. Figure it out.

- It has been done! Expression analysis now takes in account implicit conversions when looking for definitions from calls.
- Since it has to check that function or variable caller was a type (is static),
- it takes that opportunity to store all static calls to definitions in symbol table. No new phase required.

- Great. More poopoo. All the default node behaviour in phases is not getting called cause the parent phase has the more suiting
- argument type. So I need to call all of them everywhere. Screw inheritance, eh?

- Used PURE_VIRTUAL macro on all functions in parent Semantic analysis phase class. This will crash if one phase calls a functions that it did not override.
- That is good. That way the assert will not go unnoticed. Remember to scroll all the way to the right on crash report at the top to see which function did it.
- This should finaly be it with semantic analysis. For the third time...

- Some boilerplate is done. Most classess are created, except maybe for all compound assignments. Might require some work. 
- Need to figure out how to incorprorate conversions at runtime. Could probably do it at RTS_Expression level.
- Function definitions RTS will run run the actual function in new stack frame. Function call RTS gets a param value per step, optionally calling converters as needed.
- (Semantic analysis makes sure that there is one correct answer in symbol table per function call). 
- Class definition RTS can be used to create all the necesary variables in constructor, since classes cant be run anyway, and all the needed data is already there.
- Special (top level) and flow control RTS are defined. Expressions and definitions are next. 
- NOTHING HAS BEEN TESTED YET AGAIN! This will come back to bite me in the ass, and not in a good way.

- Most RTS are completed. Operators (other then Member access) are not done, as well as class definition.
- Variable definition is incomplete. In case it does not have an init expression, it needs to decide if it can create a null value, or a default value,
- depending if the class it represents is a "class" or "struct".
- Variable call is incomplete. It needs to query the list of global variables by class and name. For that I need to add yet another semantic analysis phase.
- I am so glad i made each phase its own class. having all that stuff in one object would make my code and my brain explode.
- Also added another Value in codeRunner, that represents the owner. It is set by member access to the value of caller, and is clear only when caller completes.
- This is probably unwise, since a function calling another function overrides the caller of the first once once it completes. This should probably be a stack.
- Every time a member access left value is evaluated, the value is added to the stack. When right value is evaluated, owner is poped. This stores the owner between 
- function calls and basically acts as scope stack. Only works if "owner scope" can change only by using member access, which I believe is correct.
- Tomorrow when I read this I am going to be so confused...

- Added some more boilerplate code. All the ASTs now properly initialize RTS when created.
- Should move FindOverloadedOperator function from Expression analysis to Symbol table. That way it can be used by RTS operators.
- RTS operator should find and call the function based on given values. OneArgument and TwoArguments should store those values, and then call Super::RunStep to call the function.
- Basic class should act like a struct, while those inheriting Object act as a class, getting passed by pointer, and can be null.
- Same way base class is recreated, while pointer is copied on = operator. That leaves the copy and init job on operator = functions, instead of codeRunner. 
- A value is just a type name and instance variables. Might need to store variables in another class, to have the null option. CodeRunner then handles if a values can have null (maybe)
- Also possible to make the variables a struct with IsNull bool? Then might as well store variables on Value, and have IsNull bool on it too.
- TODO: Buy a rubber duck.

- I thought I had to make another phase which stores all global variables so I can query then at runtime. Good thing I made a phase called StoreStatics that does just that.
- A moment of brilliance, for certain.
- Nontheless, I decided on the "values is a class with map of other values a variables, a string representing type, and bool showing if it's null" path. Another benefit is that 
- values can init themselves, and i can use them all without needing to know their subclass (sounds like anything other then this is just bad design when I put it that way).
- Values are split in 2 parts, ClassInstance and TypeValue. At the start of code run, all type values are created, and all global variables are stored in their respective class.
- This allows member access, variable calls and function calls to not care if they got a type or class instance, since they works the same.
- Values are also smart enough to know if they are nullable or not, depending on class they represent. If they are nullable, on creation, they have no variables, and are marked as null.
- if they are not nullable, they create all their variables, and so the chain continues. 
- There is an issue if a struct has (directly or indirectly) a variable of its own type, since that would cause an infinite loop. Needs more semantic analysis.
- Can't have enough semantic analysis.
- For now, variables, when created do not care about value. That means if they are created from another instance initialization, or through the variable definition.
- Ideally Variable definitions would call the = operator of they have a InitExpression. This applies to when an instance is created as well. 
- Not being able to set default values outside the constructor, while at the same time not being able to use constructors doesn't seem like you could do anything usefull.
- Reminder, again, for class vs struct differentiation, object is passed by reference if it somehow inherits from Object class. Object class then overloads the = operator,
- So all that is logic is contained outside the codeRunner. This allows him to just run the code without caring what it is, as well as making my life easier.
- Now it's time to stop. For honor stream starts soon.

- Jesus Christ, this is not good. Valk is now a true Mixup lord. Puts kensei to shame, especially considering how safe shield crush is. 
- Even if you read her softfeint right and dodge correctly, you still need to guess the punish. So ironic. Gladiator is classified as "Mixup intensive",
- and was considered a superior Valk. How the tables have turned (even though Glad was never mixup intensive).
- Warden on the other hand got a good rework, mostly. Still SB oriented, but without the "50/50". Forward dash heavy is nice, but Hesus Christus, that range. 3 fucking backdashes range.
- Also still no heavy-light combo. Devs realy don't want him to actually use his sword.
- btw, Code running part should be completed. Just have to create all the predefined types and basic operator functions and then i can try it out. Fuck that shield crush, man. Valk next Shaman.

- Wow! Wow! Wow! People actually super mad about valk rework. I understand that blocking a heavy or dodging if you see unblocakble might be easy to react to, but it's still a guess on a punish.
- Still most of them complain that they changed the way she used to play. And the old way is terrible. All the lawbringers and shugokis must be so mad at them. 
- Anyway, things and stuff have been done. Now classes, functions and variables can be created directly in the editor. And best part is, only functions need actuall behaviours.
- Everything else is just DATA. Can even set default values for the literals in variables (int float bool and string).
- Added code to GetVariable function in code runner that now allows query of variables from owner if the variable is not in scope.
- Next step is to make a constructor. That means even more semantic analysis. YAY! However, since no constructor can be called on an instance or type (a.vector(1, 1, 1) is not valid),
- and constructors are not inherited, this would make the function calls by name fast. Maybe it wont be neccessary to store constructors seperatly.
- Another thing to look at is passing values in functions. Every value is being passed by reference now. 
- This will actually need a change. The "Keep values in a map and have a isNull bool" thingy is actually wrong. Cannot Identify if two objects are same or not if they have same values.
- So I have to change values to have a pointer to object UVariables which holds the map with variables. Another pro is that since it's an object it can actually be null 
- while the value can still exists without the need to keep that data seperate, like the magical isNull bool. Another pro is that is nuller, the values are gone and memory is freed. 
- Another big advantage is that now I can check if two objects are the same by comparing the UVariable objects pointers together. This allows easy creation of values as well.
- Assigning or copying nullable value just stores the same UVariables object pointer. On non-nullable classes, I create a new UVariables object, and copy the variables map.
- Placing that behavior in "operator =" function may not be wise, since I need to duplicate values outside that function. 
- Instead behavior should be stored in UValue, and "operator =" should simply call it.
- There is only one "must do " thing left after that. Call conversions before calling functions if necessary. Then just safety checks in semantiy analysis, including:
- Pass by reference must pass a variable instead of literal, non-nullable class cannot indirectly contain a variable to self unless it does so through a nullable class variable.
- Constructor analysis. They must be valid, and must create default constructors for classes that have none. Might consider leaving a constructor with no arguments valid at all times
- to make in-class variable initializations easier. Also still need a good way to diferentiate between prefix and sufix increments and decrements for function definitions.
- Then comes the scary part. Actually running and testing the code... May god help us all...

- I am absolutly beffadled. I think I know why that old code was crashing. Seems like maps sometimes just don't recognise keys properly. so they they either say they dont have the value
- that should be there, so accessing it crashes, or even worse, techincally they could return the wrong value (even though i have my doubts it could). Seems to be completly random as well.
- The most viable answer i found so far is that pointers must be in a memory address that is a multiple of 8. That's just how windows works. So if i have something else in the struct i'm 
- using as key, it is possible to have some unused bytes. If some data takes like 20 bytes, then the pointer cannot start on the 21st byte, but on 24th. This leaves bytes 3 bytes (21, 22, 23)
- Uninitialized, aka. have random values that was there before. However, the hashing function takes them in consideration. This would explain why the only errors were not found when it
- exists, and not the other way around. The solution would be to add a dummy bool value of x bytes with false value, to make sure those bytes are always the same. 
- But here is the part that bamboozeled me. When i tested the size of FFunctionID, it came out to be 40 bytes. Which is a multiple of 8, 
- which means that the pointer should already be at the correct place. Same way, the child member FFunctionSignature has 32 bytes (A string and an array of strings), 
- which together with the UAST_ClassDeffinition pointer in FFunctionID gives the correct number of 40.
- I have done another test as well. I printed the hashed value of a FFunctionID and FFunctionSignature with same values. While mostly repeating the same number, it would change and give a different one.
- That number would then again repeat for a while until it changes to another. That would happen about 4-5 times in a loop of 200. 
- Reason why it would repeat for a while could be cause the loop only used that one variable, so the same adress was being used over and over, until garbage collector cleared something.
- So the logical answer would be the hashing function is bad. Maybe it uses actual memory address for hashing? So I did another test. Ran the same loop in blueprints a few times.
- Gave it the same data as in code, and tested if the map contains that key (cant get hash in blueprints).
- Result was facinating. In a loop of 300 iterations, it always found the key. Ran that again a few times. Maybe it worked cause it had onyl a single value?
- Since it could find key in blueprints, maybe the variations in hash were unimporant. After all, it still has to use the == operator for comparison.
- However, in code, vector struct always returns the same hash, no matter how many times i ran it.
- The only thing I can think of at this point is that the string array changes the hash value somehow. Im comparing values  in == operator, but maybe the hash is comparing references to the array?
- But if that was the case, then the key would never be found, and yet it sometimes does.
- This is preety bad, considering that the entire semantic analyser and code runner uses that data a lot. And while it doesnt work properly, I cant actually test or run anything.
- I have absolutly no clue what to do...

- Behold a miracle! I actually fixed the bug. I was right, it was the array that was ruining everything. Probably cause it is dinamic, so the pointers to values change with each isntance, 
- which in turn changes the memory footprint, throwing the MemCrc32 hash off. The way I fixd it is actually super simple, makes sense and is terrible.
- Instead of hashing the memory footprint of FFunctionSignature, which contains a string of function name and an array of strings representing parameter types,
- I totally cheated. Since hash is just a number, what I did was that I combined all the array elements in one string, which I then appended to the Function name.
- That gave me one string containing all the data, which then I hashed. Still only functions with same signature can have the same hash (as much as anything hashed does).
- So I tested that and it didnt't work. The reason why is that FFunctionID, which contains FFunctionSignature still uses the memory footprint, 
- which indirectly uses the FFunctionSignature memory footprint.
- Again, fix was easy, though not perfect. The hash is now calculated as the sum of FFunctionSignature hash and the hash of the UAST_ClassDefinition pointer.
- In theory this could have more keys return the same hash, but with the scope of the project, and the relativly small ammounts of functions, it should be a non-issue.
- So, with the bug fixed, the code can now be ran. Classes and functions created in the editor can now be compiled properly. A static function which prints a string has also been called successfully.
- The next idea is to have URTS_VariableDefinition be the only thing that is allowed to create variables. I already added a member which notates if hte variable is local, 
- or if it should persist with the instance. In other words, should it be stored in scope, or in the class instance value itself. Problem is Calling that code from start of RunCode function.
- Perhaps I could do the same thing I did with CallFunction. Move it in CodeRunner, and just let VariableDefinition call it.
- Which leads to another problem. The CallFunction function in CodeRunner needs to change. Since it is now in charge of actually calling functions, it should take in consideration conversions.
- Since multiple conversions can happen for one function call, and I need to fetch the result after each one, I cant do it inline inside the function. 
- Perhaps I could make CallFunction force the completion of the calling RTS, and then it can take over until the specified function is completed.
- Considering VariableDefinitions can contain functionCalls in initExpression as well, similar thing should be done for them. Seems a bit akward though, if function calls call other function calls,
- ect, all requirering conversions. Perhaps having a specialized objects that handle function calls would fix that. Need to see if URTSFunctionCall could still be used somehow for that.

- The actual function call with the validated parameters needs to be called on multiple locations, but it cannot be called from CodeRunner, since it may require conversions. The solution is to 
- make the CallFunction function inside URTS_FunctionCall, and make it static, while the instance part (RunStep()) takes care of validating and converting argumnents. 
- However, this may still have issues if operators need to convert values.
- CallFuncition also duplicates the value before passing it on to the function definition if the parameter is not passed by reference.
- Another thing I decided, but havent done yet is a change on creation of values, which would solve the initialization of values upon creating instances.
- Idea is to have CodeRunner create values, but not inline, and instead store the value in the globaly access value member.
- This allows value creation to use RTSs without issues. In short, this allows code runner to run all variable deffinitions upon creation, as well as a constructor.
- There are a few caveats though. For one, I will probably need to have two functions, one for such creation, the other for "inline" creation.
- Inline creation would instantly return the value, instead of storing it. It would be used in instances where a class needs to be created that I know holds no variables
- or constructors, such as bool, int, float and string, though this would also apply to nullable values containing null value.
- Will need to add extra checks to make sure no non-nullable value can be created inline.
- The inline creation would work similar to the way it works now, without any variable initializations, however, the normal creation will change.
- For starters, other then returning a value to the "global" access point, which could add extra steps/states to some RTSs, that function would also require a new parameter.
- An array of values, which would be passed over to the constructor.
- First step would be to create all the variables the instance has through VariableDefinitions, since they can now take over that job.
- Then I need to loop through all the parents, and add all of their variables as well. In the end, I run the constructor specified by the parameters passed.
- This would require yet another semantic analysis, to make sure the constructor calls are valid. But that will have to wait,
- I'll just add an assert if valid constructor cannot be found (though every class should have a valid default constructor).
- Nothing says "Look, this shouldn't have happened" like a forced crash and a custom error message next to the callstack.
- Consider storing constructors in symbol table with classes as keys. That way I can not only find them quickly, but can quickly check if any constructors actually exist on a class.
- This allows me to call default constructors only when no other constructor is specified. (Might change that is it gets annoying creating empty constructors)
- Something else to investigate is how conversions are affected by inheritance. If class b can be converted to class a, and class c inherits class b, then c could get converted to a.
- I believe that this should work without any modifications (perhaps there is a small chance that it might cause issues if passed by reference)
- Since child has all the variables of the parent, there could be no errors. Only issue could come if I need to read variable type inside a function at runtime.
- other then casting, that should never happen. However, if it does for some reason, the solution would be to store variable type in value, and actual type in UVariables of that value.
- Tl,Dr; If I'm reading this Tl,Dr;, I'm an idiot. I wrote all of this for me and just me, and was too lazy to read it the next day.

- Ok, remember when I said that i made the CallFunction function static so it can be used anywhere, while still being able to convert types?
- That would work greatly, if that function actually converted types. Now I decided on something new. Made a concept of "implicit runtime state". These RTS are run whenever something
- should change, but are not directly linked to a specific AST node. Some of these things include things like converting all types to a correct type before calling a function, 
- or Initializing values properly on instance creation. Next step is to use the RTS_StaticInitializer to initialize all the static values at the start of RunCode().
- Implicit RTS solve the problem that I had with other solutions, since now I can actually have a way to have easely accessible actions that can be broken in steps, without 
- changing other RTS. 
- Note to self, Static initializer should be run before the actual code. So add the RTS_Basic on rts stack first, then the static initializer. When initializer is completed, 
- basic will already be next in line to run. This order allows me to just set them up and start the code, without keeping track of specific states just for static initializer.
- Also remember that RTS_instanceCreator is not fully completed. It just needs one line, and that is to call a construction at the end. Reason why it doesn't is cause
- I don't have constructors specifically defined yet. It can wait, need to make the sure the rest works first.

- Beholding a miracle intensifies. Basic code is successfully run. And by basic i mean, printing strings (on just basic print string on screen, but it shows on debug UI),
- concatenating strings, implicit conversion from int to string which, surprisingly, worked first try with no issues 
- (other then me forgetting to initialize URTS_ChainedFunctionCall, which was just one line to add, 20 seconds of work).
- For loop also works, as well as branching with ifs (including the false branch).
- Expressions containing operators with different precedence also returned the correct result. Surprisingly correct. Though I though that reusing a variable might have given the old result.
- Just something to test next time. Can't be sure what happened, if anything at all happened.
- So, under the hood work that was done: Finished static initializer. Ran into a problem with declaring all static functions at runtime start. Variables defined in Main are considered
- in global scope, however, that is not correct. Scopes can exist in Main block as well. Decided to have the topmost scope for Main variables. Since that scope is always active, 
- They work just like static variables, as they are accessible from anywhere. Another advantage is that now variable definition rts does not need to care if the variable it reached
- is in main block or not, it simply adds it to the scope.
- Also had to fix the blueprint functions, since they still called the old value creation functions in code runner. Fixed now.
- Need to add more custom functions as well, however, the basic types will be converted to c++ code anyway, so I might just do it then. 
- There is something that will probably need to change with simple custom functions. Make the actual function return the value,
- instead of letting rts do it. This would pass the value as the blueprint function is completed, instead of waiting on stack to reach the real return node.
- This also kills the function once its completed, which would free memory, and would probably greatly increase the iteration count, since in a loop of 50 functions,
- only once action would be called, instead of 50, and then they all close when the program finishes.
- Another benefit is that it would make blueprint functions even simpler, since there would be no need to call for custom return. 
- Also guarantees that the function will instantly end, which cuts down on human error.

- Today I spent a lot of time debugging stuff. Took me forever to find out why loops would crash. (Spoilers: They would properly check if the loop condition is true,
- But would run the condition only the first time. So second time it would be a random value not meant for them, and it would crash when casting to bool instance.)
- So I decided to do some debugging tools, to speed up future work. I added a function that gets called on every RunNextStep for every RTS, that would explain what it was doing in that step.
- It was terrible. I couldn't access data i needed, since at the time the function was called, the step wasn't running yet. 
- So I removed all those, and made it so that RTS can add debug messages at any time during a step. Seems to be working nicely, if we ignore my incredible explanations skills.
- Also fixed the "reusing variable bug" i mentioned yesterday. Yes, it kinda was a bug, and kinda not. The 4 predefined types are just handled differently, so they needed their own
- version of operator = function. That was all. It was a quick fix. There were some other minor details with function calls, and missing null checks, but thats all taken care of.
- Even the "Basic code" template works now, if I delete the operator overload for integers which is already defined (and is defined in a wrong place anyway). 
- I'm still surprised that complex expressions work without any modifications, at least as far as I know.

- Today i recreated all functions (other then Print) to c++. Unreal no longer detects "infinite" loop on iteration higher then 45 in test code, as expected.
- However, It seems to throw weird exceptions and crashes at around iteration 79. My guess is that I'm simply creating too many objects.
- Seriously, I don't even want to know how many objects get dynamically created during runtime. 
- Next idea is too see if I could make the Runtime states structs. I was against it at first, cause I needed inheritance, but since the code works better then expected,
- and now i have more debug tools, I no longer need to access them from the editor. That was the main issue, as UStructs do not support inheritance in editor.
- However, since I no longer need them in editor, I should convert them. This will allow them to get created on stack instead of heap, which should be a great help.
- While every other object that is created is "static", for instance, a function definition is a function definition. It does not change at runtime,
- a new RTS is created more or less every time something happens. a + b can be up to 5 RTSs, 2 for a and b values, one for function call, one for chained function call, 
- and up to 2 more, if a and b need conversions. This number quickly grows, so loops are not my friends. In case I fail to convert to structs, or structs themselves do not 
- fix the issue, then the only thing I can think of is that maybe they are not getting destroyed properly.
- Anyway, Yesterday i managed to inherit from a multiline editable text, and damn, slate is complicated. However, I am now able to properly insert tabs.
- All important operator functions for all predefined classes are done, as well as classes themselves. Implicit conversions work as well.
- Added 2 checkboxes in main ui. One for autorun and the other for outputing log. They can both be changed during the code execution (though the way i actually read log is terrible).
- I'll probably need to hook up some delegates for that on one point.
- Also made function definitions array in AST Class no longer isntanced. There was no point in doing that, since i need to actually create a simple function to add behaviour.
- This will probably change to another array of TSublassOf FunctionDefinition, which will then be created before the code gets analyzed. 

- I have some rules i follow in order to keep my stupidity in check. One of those rules is that I never do some work, finish it, and then come back in the same day.
- If it was something I could do quickly, I would've already done it. If I thought of something new, I need too sleep on it, cause chances are, it's bad.
- Another rule is that i don't work after 8pm, unless its writing this document for the next day. I noticed that, while I do get more stuff done by working more,
- I also do dumb stuff. So I waste time fixing it up the next day (Example: sword and board).
- Today I broke both of those rules.
- I know structs are not meant to be inherited. That's what objects are for. I still thought I could use some magic to get polymorphisms, and save me the heap memory.
- So what do I do? I go and change the URuntimeState class to FRuntimeState struct. Which of course means that I have to update the code in every location where it's used.
- The struct is either using it's data, so I have to change every -> with ., since its not passed by pointer anymore.
- If it's not getting data, but is getting passed through functions, then I still need to update URuntimeState* to FRuntimeState.
- And do so for every child, in every location. I have almost 100 files with just predefined functions for ints, bools, floats and strings. Not to mention the entire framework.
- So I spent a few hours, changing it one by one, going through so many errors, that the compiler gave up on showing them all at once.
- I was super amazed that it compiled in the end. But when i ran the test code, it crashed.
- It crashed cause I told it to crash. It called a function from the abstract class it should never actually access, so in that case I kill it to get the callstack.
- And why it called that function suddenly? Cause I changed every line of code so it passes the copy of the now struct FRuntimeState.
- And when you copy a struct and store it in parent struct, you lose all the child specific data, since its actually the parent type now. That's how c++ works.
- And I knew it, and I still went through all that code to "fix" it. And now it's almost 11pm, I hate myself so much, and tomorrow I'll spend even more time putting it all back as it was.
- Have to redo everything.

- I still hate myself for what I did yesterday, but it is fixed now. Reverted all the changes to the way it used to be. I did take the opportunity to make a small change though.
- Now CodeRunner is the owner of RuntimeStates, and not the AST node. That is useful now cause I made another change. InterpreterComponent can now return a valid World pointer,
- if it is owned by some class that can do the same (most probably an actor, possibly console).
- This allows RTSs to actually get references to objects in the world, as well have access to blueprint function libraries and timers.
- Another change is that I have added two more classes similar to SimpleFunctionDefinitions and its RTS counterpart. ComplexFunctionDefinition and its own RTS counterpart.
- I did have to move the Blueprint helper functions for getting variables and values upwards to PredefinedFunctionDefinition class. This allows the complex version to access it as well.
- The difference between the two is that the simple version is guaranteed to end instantly, while the complex version can complete at any point, by calling return on RTS.
- This allowed me to create a Wait function, that delays the code execution for the given time. 
- This could be dangerous, however. Since it could end at any point, it is probable that it may need to store state between frames. 
- Function definitions should not store states, that is what RuntimeStates are for. However, for simplicity sake, as long as the state is reset every time the function is called,
- and the function cannot call itself, directly or otherwise, there should be no issue. In most cases the simple version will suffice.
- Also fixed the issue with the "Random" crash on "high" iteration count. True, accessed data was seemingly random, but that was cause "long" iterations (100+) would cause a stack overflow.
- Code that performs a loop of 100 iterations and prints the iteration count completes over 2700 steps. I knew that could be an issue, so I made sure I write the code accordingly.
- I expected that Visual studio would optimize for tail recursion in order to avoid that issue, however it did not. No matter, depending on compiler optimizations is bad in most cases.
- Besides, I fixed it with a feater I planed to add anyway.
- Since I gave CodeRunner access to the UWorld it belongs to, it can also have access to timer manager. I simply added a counter that counts the current number of steps.
- If steps reach over a configurable number, the next step would be delayed by one frame. This allows the stack to empty till next frame.
- It also allows user to go through code step by step for debugging. By user, I mostly mean me.
- This feature solves another problem. Since it waits one frame every given number of steps, in the most simplest of ways, it runs the code, then waits a frame, then runs the code, etc.
- This allows other game code to run since it frees the game thread with the frame delay.
- This means that if user creates an infinite loop, it can be stopped since the game wont be frozen.
- Turing Church proved 80 years ago that the halting problem cannot be solved. This solution eliminates the need to even try.
- There is still work left to do. Currently, if the code is constantly running, it runs at around 32-35 fps, with 1000 steps per frame. Occasional sudden drops to 0 fps due to garbage collection.
- Depending on how the game will work, that may not be bad. If nothing is moving on the screen, but just writing output log, the 30 fps will not be noticed.
- If there are other stuff moving, then it will require some modifications. Good thing is that max allowed number of steps per frame is linearly negatively proportional to the fps.
- If I halve the number of max allowed steps per frame, the frame will (with minuscule differences, depending on code) finish twice as fast, therefore doubling fps.
- NOTE: the way I handle logging right now is absolutely terrible. setting it over and over every frame, and every time it is set, it must loop through every log and connect it in
- a single string. The difference between constantly running code at 1000 MaxStepsPerFrame with allowed debug log and not is around 30 and 8 fps.
- The idea would be to listen to the code runner for every time a new log or output is added. Comperativly to the global code executions, the time it needs to actually call the
- delegate is small. Then instead of adding it in one text block, I create a list of text blocks and add a new one for every entry. Even though creating a widget is more expensive then
- changing short text, it scales linearly. If I add text to the previous one every time new log gets called, then the text gets longer, which makes the operation on it longer as well.
- Adding a new text block for every entry is linear and will always take the same amount of time.
- Another benefit is that I could attach metadata to every block, such as, on which line did the log happen, etc.
- Currently, the max number of iterations from constantly running code is over 2 000 000 without any issues. Got bored after that and stopped it.
- Thats a big jump from crashing after 100.

- This will be a quick one, Stream starts in 15 minutes. I changed the way owners for functions and member accesses work.
- The version before didn't really make much sense. Now the owner (caller) of a function is stored in stack frame, where it belongs.
- I also made a custom class vector, containing 3 float variables. made a function to convert it to a string, 
- added two vectors together and printed the result. Also verified that static functions work, at least the basic ones.
- Also realized that not having constructors sucks, but I can work around it for now.
- Fixed some other bugs etc.
- For tomorrow, I need to fix the operator = problem. In this example, I have a function overriding operator =, taking two classes as arguments.
- Since I allowed to implicitly convert from vector to string, instead of calling that function, it called the operator = function for strings.
- There are two solutions. One is quick and dirty, the other is proper but long.
- The quick and dirty is to make a special case if I call operator =, and only accept functions that have the exactly matching first argument.
- The proper way is to make it a rule that if a parameter is passed by reference, then it has to be the exact matching type. Thats how c++ and C# work.
- That also means ill probably have to change all the pass by ref params in all my other functions, since im not taking in account consts.
- Have to go now, its almost stream time.

- God dammit. It keeps happening. I've been working on this for so long, and just know i found out that string comparisons are made case insensitive.
- Since im using string to store function and variable names, that makes my entire code case insensitive.
- Even though I hate it, it still works, since strings are compared the same way everywhere. Due to time constraints, it will have to say like this.
- I knew not testing sooner would come back and bite me in the ass. Behold, the birth of a feature.
- In other news, Today i managed to make constructors work. It isn't nice, by all means, but it works.
- In order to call constructors for a type, you write down the type. Problem is that during the parsing I cannot know if something is a type.
- Even though I could've work around it, I chose not to. Instead constructors are defined using the constructor keyword.
- No point in writing the class name inside the class. This also makes it less error prone from users side, as well more obvious what the function is.
- I used function analysis phase to check for constructors, so I didn't had to make another SemanticAnalysisPhase. While checking for constructors, 
- those function definitions are renamed in to the name of the class they construct. That way they can be called properly.
- Issue is that constructors are defined inside a class. However, they are not static. so calling vector(1, 2, 3) in global scope would be an error,
- since there is no function named vector in global scope. This required some special case handling(read: ifs) to make them work.
- It is quite unfortunate that the special cases I had to define were quite a few, on various places. 
- Kinda isn't pretty, but considering nothing else will affect constructors, it should not cause issues.
- For the last official feature left to do, I need to create an array.
- It will not be easy. I can pass the data about array in the FExpressionReturns struct for semantic analysis, that should work.
- A simple bool will suffice. Don't plan to add sets or maps anyway. Then I would have to check everywhere for that bool as well. Lots of searching, but doable.
- Problem would be passing it around in function signature. I returns a list of types as arguments.
- I can either add array<type> on string, or make it a struct and add a bool. Either way, more checking.
- It may be bothersome, but it is doable.
- Fun fact: When I was changing back the RTS from struct to class, I used find and replace, too speed up the work, even though I dont like to use it.
- At that time, I already had some stuff set up for constructors.
- After searching and replacing, all my constructors got renamed to conclassors.
- 
- Well, arrays can now exist in the code. I can create them, add to them, check their size, and remove from them. Can also assign one array to another.
- There is only one problem. I can't call any of those functions.
- In order to do so, I need to make another semantic analysis. Right after class and type conversion ones. 
- This analysis will go through all nodes, and check where element types is used. and store the reference from that node to real type.
- I think I can know the type at compile time, though not sure if I do in all cases. Will still need to figure it out.
- Working on this is getting really annoying, but it's almost over. Constructors and arrays added so much spaghetti that i have enough to eat for months.

- Magic. I made arrays work. And most of the time spent was trying to figure out why my values were shared between classes when they shouldn't be.
- Spoilers: It was variable definition RTS. It would take a value and assign it to the lhs, instead of duplicating it first.
- Also managed to add a feature to allow getting and setting array elements using array[int] syntax. Since the [] are supposed to be operators, 
- but for did not program a possibility to add an expression to square brackets, I simply change that to appropriate AST nodes at parser level. 
- Which led to me to another great discovery. I managed to crash the engine. A lot
- All this time, I didn't check if I had an error during parsing. (or lexing for that matter).
- It was pure luck (or lack of testing) that every time there was a parser error, there was a semantic error as well. Makes sense, but it isn't guaranteed it would happen.
- Well, it is fixed now. Arrays work, and all is well. 
- Also quickly tested the = for objects. Worked as expected (other then a puny error that took like 20 seconds to fix).
- As a testing case, I craeted a class called boubble that has a float representing radius. Then I sorted the bubbles using bubble sort. 
- The arrays are passed by reference as well, and it worked. Magic, I tell ya...

- Schhhhhh, I'm hunting wabbits. Bugs bunny, to be precise, and he aint no bunny. Just Bugs.
- Got a few, there was one where types were considered same as values. Done.
- There was another one for objects. Done.
- Also added the nullptr to the mix.
- With it came more Bugs bunnys.
- Got those too. Done.
- Made the RTS parameter in Return function for complex functions a parameter so I could null it inside. Makes stuff simpler.
- Finaly got the document as well. Now I can plan the rest of the stuff.
- in the meantime, I should do the interpreter class, as a whole.
- Maybe make the UI better?
- After that the magical actor classes stuff.
- I think I need a break...

- Made the interpreter today. Till now, every interpreter component (Lexer, parser, semantic analyser adn code runner) handled it's own errors.
- Now errors are just sent up to interpreter. Interpreter also handles all the necesary preperations for compilation and running the code.
- It does everything from lexing to analysing, and it stops on first error.
- It returns errors, and where they happened (durting which stage), tokens, ast, warnings (if any) and symbol table.
- Good for debuging and showing needed data.
- Started working on the console as well. Gonna make it proper now, since i know it probably will end up being "good enough" no matter what it is.
- Next step is to make the framework for "hackable" actors, and I also need to add some information on the console about them.
- Still need to decide how hacking will work. Idea for now is you get to the thing, and you hack it. However, that means that there is no way to have two things interact
- with each other in the code.
- Possible solution would be to have some hackable actors "referencable", aka store their reference, and use it on necesary hacked actor.
- This is now getting into gpp, so this will need actual playtesting.

- Today I completed most of the console UI. Only debug stuff that is no lenger important remains.
- The character is now part of the third person character template, and inputs are properly handeled depending if the console is open or not.
- Added the ability to stop the execution of code at any time.
- Used bindings to enable and disable buttons for compiling, pause running code etc. It's so much simpler then making all the delegates for each change.
- Found more bugs. For instance Print(i) ++i is considered as Print(i) + (+i), or as Print(i)++ i. In any case, semantic analysis should have cought that,
- but it crashes while running the code.
- Created 2 code data assets, to keep examples of "bad code". One that has code that works when i shouldn't, and one that doesn't work when it should.
- Will add to it as I find more of examples. (Example above already added)
- Decided to make the player controller the main class that keeps controlls the interpreter. makes most sense, considering that no one but player will interact with it,
- and it will always be available. allowed the UI to clear itself when recompiling. It is no olonger necessary to destroy and recreate the console.
- Might make the console persistant. Persistant UI would allow me to make it 3d in world, since I wouldn't have to worry if it exists, and where it should be.
- It can always be there, since it always exists. No special spawning logic required.
- But it is not yet the time for that. Tomorrow during work I need to have a little chat to get more details about the interactions between different hackable actors.
- Then I can start working on the framework for them. After that, keep poping out new levels, and fix up some rough edges.

- Hackable objects are no longer a thing. They are now called code actors. There are a few reasons:
- Not every code actor will be hackable, while it could still be referenced.
- Somce code actors could be hacked while not being referenced.
- The framework for that is coming along quite well. Sucessfully managed the entire referencing part. Code actors can be stored
- in variables and arrays of any type (that compiler will accept), and there is also a quick shortcut to make them autoreference.
- While doing that, I ran into a bug where game would crash if I called a function or variable that uses a undefined type.
- It is fixed now.
- There is a potential issue with using variables. While it is possible, it would require a long chain from code actor isntance to reach the variable.
- It would be simpler to make geters and setters for the code actor. That would allow the code actor to keep the values on itself, rather then the isntance.
- that is important if it needs it during editing time.
- Next step would be to create the hackable part.
- NOTE: I still need to streamlilne the part where interpreter gets the outside data before compilation. One of that data should be the instance that is getting hacked.
- (That would be the only way to directly interact with non-referencable code actors.)

- Forgot to write this yesterday, since most work was done in editor. Moslty tested that code actors can be referenced and work properly.
- Also renamed complex functions and complex rts to simple delayed predefined functions and rts. Made the new complex ones, and they work as they should, 
- where function definition contains the function data and rts the states.
- Will probably remove the delayed ones, since they are no longer necessary.

- Still here today. Work has been done. Created 3 interfaces, IInteractable, IInspectable and IHackable.
- CodeObject is hackable by default, and only code objects will likely be hackable.
- Pawn now detects and stores the the object it loks at if it is at least one of the three above mentions classes.
- Changed the pawn to first person pawn from the FPS template.
- Added a little hud in top left to show if the object we are aiming at is interactable, hackable or inspectable.
- Distance can be changed for each type indivisually.
- Also Tested if inheritance works with code. It does.
- Added the ability to add a Top owner when starting the compile. This acts as if the entire code is written inside that owner.
- The console is now persistant. It is no olonger destroyed when closed and recreated when opened. This should keep all the writted stuff between opening and closing.
- Should also make it simpler to cache some static data, such as the functions for the predefined types.
- Should probably create a new UI for the "pip boy". Console is just a part of it. Inspecting data and such should also go through "pip boy".
- Pip boy should be a 3D widget.
- Before I start that, I should probably do the entire level framework. Need to create the entrance and exit conditions and blueprints.
- Also need a way to choose the levels (Probably through pip boy, Seems like the Go To place for everything).
- Levels will need some description, name, and it needs to know if it was already completed or not.
- This means that there will need to be a main Nexus from which player can select the level.
- Completing levels opens new ones, and probably best way to start a level would be to hack something with the console. (Hack a program and enter in it storyline maybe?)


*/



/*======================
 Large comment
======================*/