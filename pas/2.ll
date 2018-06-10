; ModuleID = 'Pascal'
source_filename = "Pascal"

@a = global i32 0
@i = global i32 0
@.str = private constant [4 x i8] c"%d\0A\00"

define void @main() {
entry:
  store i32 1, i32* @a
  br label %FORloopEntry

FORloopEntry:                                     ; preds = %entry
  store i32 1, i32* @i
  br label %FORloopStmt

FORloopStmt:                                      ; preds = %FORloopEnd, %FORloopEntry
  %0 = load i32, i32* @a
  %add = add i32 %0, 1
  store i32 %add, i32* @a
  br label %FORloopEnd

FORloopEnd:                                       ; preds = %FORloopStmt
  %1 = load i32, i32* @i
  %add1 = add i32 %1, 1
  store i32 %add1, i32* @i
  %2 = load i32, i32* @i
  %gt_cmp = icmp sgt i32 %2, 200
  br i1 %gt_cmp, label %FORloopExit, label %FORloopStmt

FORloopExit:                                      ; preds = %FORloopEnd
  br label %WHILEloopStart

WHILEloopStart:                                   ; preds = %WHILEloopStmt, %FORloopExit
  %3 = load i32, i32* @a
  %ne_cmp = icmp ne i32 %3, 234
  br i1 %ne_cmp, label %WHILEloopStmt, label %WHILEloopEnd

WHILEloopStmt:                                    ; preds = %WHILEloopStart
  %4 = load i32, i32* @a
  %add2 = add i32 %4, 1
  store i32 %add2, i32* @a
  br label %WHILEloopStart

WHILEloopEnd:                                     ; preds = %WHILEloopStart
  br label %REPEATloopStmt

REPEATloopStmt:                                   ; preds = %REPEATloopEnd, %WHILEloopEnd
  %5 = load i32, i32* @a
  %sub = sub i32 %5, 1
  store i32 %sub, i32* @a
  br label %REPEATloopEnd

REPEATloopEnd:                                    ; preds = %REPEATloopStmt
  %6 = load i32, i32* @a
  %eq_cmp = icmp eq i32 %6, 200
  br i1 %eq_cmp, label %REPEATloopExit, label %REPEATloopStmt

REPEATloopExit:                                   ; preds = %REPEATloopEnd
  %7 = load i32, i32* @a
  %eq_cmp3 = icmp eq i32 %7, 200
  br i1 %eq_cmp3, label %thenStmt, label %elseStmt

thenStmt:                                         ; preds = %REPEATloopExit
  %8 = load i32, i32* @a
  %add4 = add i32 %8, 33
  store i32 %add4, i32* @a
  br label %mergeStmt

elseStmt:                                         ; preds = %REPEATloopExit
  br label %mergeStmt

mergeStmt:                                        ; preds = %elseStmt, %thenStmt
  %9 = load i32, i32* @a
  %10 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %9)
  ret void
}

declare i32 @printf(i8*, ...)
