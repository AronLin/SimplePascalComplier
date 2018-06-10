program llvm;
var a, i: integer;
begin
    a := 1;
    for i:= 1 to 200 do
    begin
	a := a + 1;
    end;
    while a <> 234 do
	a := a + 1;
    repeat
	a := a - 1;
    until a = 200;
    if a = 200 then
        a := a + 33;
    writeln(a);
end.
