program llvm;
var a: integer;
function mul(x: integer): integer;
begin
   if x = 1 then
	mul := 1
   else 
	mul := x * mul(x - 1);
end;  
begin
    a := mul(5);
    writeln(a);  
end.
