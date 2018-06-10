; ModuleID = 'Pascal'
source_filename = "Pascal"

@a = global i32 0
@i = global i32 0
@.str = private constant [4 x i8] c"%d\0A\00"
@.str.1 = private constant [4 x i8] c"%d\0A\00"
@.str.2 = private constant [4 x i8] c"%d\0A\00"

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
  call void @addX(i32 20)
  %5 = load i32, i32* @a
  %6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %5)
  %7 = call i32 @addXF(i32 20)
  store i32 %7, i32* @a
  %8 = load i32, i32* @a
  %9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0), i32 %8)
  br label %REPEATloopStmt

REPEATloopStmt:                                   ; preds = %REPEATloopEnd, %WHILEloopEnd
  %10 = load i32, i32* @a
  %sub = sub i32 %10, 1
  store i32 %sub, i32* @a
  br label %REPEATloopEnd

REPEATloopEnd:                                    ; preds = %REPEATloopStmt
  %11 = load i32, i32* @a
  %eq_cmp = icmp eq i32 %11, 200
  br i1 %eq_cmp, label %REPEATloopExit, label %REPEATloopStmt

REPEATloopExit:                                   ; preds = %REPEATloopEnd
  %12 = load i32, i32* @a
  %eq_cmp3 = icmp eq i32 %12, 200
  br i1 %eq_cmp3, label %thenStmt, label %elseStmt

thenStmt:                                         ; preds = %REPEATloopExit
  %13 = load i32, i32* @a
  %add4 = add i32 %13, 33
  store i32 %add4, i32* @a
  br label %mergeStmt

elseStmt:                                         ; preds = %REPEATloopExit
  br label %mergeStmt

mergeStmt:                                        ; preds = %elseStmt, %thenStmt
  %14 = load i32, i32* @a
  %15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i32 %14)
  ret void
}

declare i32 @printf(i8*, ...)

define void @addX(i32 %x1) {
entry:
  %x = alloca i32
  store i32 %x1, i32* %x
  %0 = load i32, i32* @a
  %1 = load i32, i32* %x
  %add = add i32 %0, %1
  store i32 %add, i32* @a
  ret void
}

define i32 @addXF(i32 %x1) {
entry:
  %x = alloca i32
  store i32 %x1, i32* %x
  %addXF = alloca i32
  %0 = load i32, i32* %x
  %1 = load i32, i32* @a
  %add = add i32 %0, %1
  store i32 %add, i32* %addXF
  %2 = load i32, i32* %addXF
  ret i32 %2
}
