import { func } from "./func";
//import { out } from "std";
//import { fib } from "./test_dynamic.dll"
import { p_suffix } from "ffi"

export function hello() {
    console.log("Hello World");
}

hello();

var i = 0;
for (; ;) {
    //console.log(i)
    ++i;
    if (i === 100) break;
}


var f = func();
f();

console.log(p_suffix);

//out.puts("123\n");

//console.log("fib(10)=", fib(10));