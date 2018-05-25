# SimplePascalComplier

课程作业，小型的pascal词法分析器，然后用yacc分析方法完成部分语法的语法分析，并生成语法树和中间代码。

目前pascal.y里面的if-then-else语句是有shift-reduce冲突的。但是，yacc在遇到冲突时，默认用shift来解决冲突，这样会进入else语句，也正好符合了if-then-else语句中else是和最近的if-then语句匹配的情况，所以说这个冲突对结果没有啥影响，可以忽略。
