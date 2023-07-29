import { func } from "./func";
import { out } from "std";

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

out.puts("123")