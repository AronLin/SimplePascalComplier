program llvm;
var a, i: integer;
function fib(x: integer): integer;
begin
    if x = 0 then
	fib := 0
    else
    begin
	if x = 1 then
	    fib := 1
        else
	    fib := fib(x - 1) + fib(x - 2);
    end;
end;  
begin
    for i:= 1 to 10 do
	writeln(fib(i));
end.
