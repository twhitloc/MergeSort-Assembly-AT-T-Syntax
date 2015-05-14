
.extern _cout
.data
arraySize: .long = 0


.bss
sorted:  .space 64
temp:    .space 4*50000000


    .text

  .global print.args, _asmMain
_asmMain:


;//move arguments from registers that will get beaten up and save them ecx->esi is location of array
movl %ecx, %esi
movl %ecx, sorted
movl %eax, %ecx
;//eax->arraySize is size of array
movl %eax, arraySize
movl 8(%ebp), %eax
movl sorted, %edi
;//sorted location->edi

rep
;//repeat until sorted
movsl
pushl arraySize
;//put array size onto stack (maximum index)
pushl $0
;// 0(minimum index)  && push sorted onto stack
push sorted
call mergesort
;//call the sort
addl $12, %esp
movl sorted, %eax
ret
;//while it is not sorted continue


;//now that we finished with all the partitions here we go to merging
merge:
pushl %ebp
movl %esp, %ebp
;//manage stack frame
pushl %eax
;//push partitions onto stack
pushl %ecx
pushl %edx
pushl %edi
pushl %esi
;//done with pushing partition

movl 20(%ebp), %ecx
subl 12(%ebp), %ecx
;//shifting bits around
shll $2,12(%ebp)
;//moving indexes 
shll $2,16(%ebp)
shll $2,20(%ebp)
movl $temp, %edx
;//move temp into edx
movl 8(%ebp), %edi
;//move stack variable to edi
addl 16(%ebp), %edi
;//index change
movl 8(%ebp), %esi
addl %esi,12(%ebp)
addl %esi,16(%ebp)
addl %esi,20(%ebp)
movl 12(%ebp), %esi



merge.next:
;//compare indices
cmpl 16(%ebp), %esi
jnz merge.second
    ;//if merging needs to continue
    cmpl 20(%ebp), %edi
    jnz merge.first
        jmp merge.end




merge.first: 
cmpl 16(%ebp), %esi
jnz merge.second
;//if the values arent equal go to second
    movl (%edi), %eax
    movl %eax, (%edx)
;//move through indices
    addl $4, %edx
    addl $4, %edi
jmp merge.next



merge.second:
cmpl 20(%ebp), %edi
jnz merge.third
;//compare next, if not equal go to third

;//if they are equal..
movl (%esi), %eax
;//move whats at the address of esi into eax
movl %eax, (%edx)
;//move that to the what is at the address of edx
addl $4, %edx
;//increment
addl $4, %esi
jmp merge.next


merge.third:
;//compare indices
movl (%esi), %eax
cmpl (%edi), %eax
jnl merge.forth
;//if it is less continue and go to merge.next, otherwise go to merge.forth
movl %eax, (%edx)
addl $4, %edx
;//increment
addl $4, %esi
jmp merge.next


;//the comparison was true and we need to move it
merge.forth:
movl (%edi), %eax
movl %eax, (%edx)
;//move contents around
addl $4, %edi
addl $4, %edx
;//increment and go back up
jmp merge.next



merge.end:
movl $temp, %esi
;//move partition to edi
movl 12(%ebp), %edi
rep
movsl
;//grab values from the stack
popl %esi
;//getting sorted partitions put them in registers and go back
popl %edi
popl %edx
popl %ecx
popl %eax
;//return current stack frame
movl %ebp, %esp
popl %ebp
ret
;//continue while




mergesort: 
pushl %ebp
movl %esp, %ebp
;//set up the stack
pushl %eax
;//put eax onto stack
movl 16(%ebp), %eax
;//maximum index -> eax
subl 12(%ebp), %eax
;//subtract the partition # from eax #
cmpl $2, %eax
;//compare # of indices left to 2, if less then we must be done dicing our array up
jL mergesort.end
    pushl %edx
    pushl %ebx
    ;//throw the addresses onto stack and clear edx
    xorl %edx, %edx
    movl $2, %ebx
    ;//move 2 into ebx then divide eax (split array (partition))
    divl %ebx
    popl %ebx
    ;//put the index of partition in stack
    popl %edx
    ;//get frame back->ebx
    addl 12(%ebp), %eax

    pushl %eax
    ;//eax goes onto stack again
    pushl 12(%ebp)
    pushl 8(%ebp)

    ;//call some recursion
    call mergesort
    addl $12, %esp
    pushl 16(%ebp)
    ;//go through the indexes
    pushl %eax
    pushl 8(%ebp)
    call mergesort
    ;//merge the list together
    addl $12, %esp
    pushl 16(%ebp)
    ;//sort them as they get merged
    pushl %eax
    ;//index pushed
    pushl 12(%ebp)
    pushl 8(%ebp)
    ;//why not 20?
    call merge
    addl $16, %esp



mergesort.end:
;//we finished partitioning, now start merging
popl %eax
movl %ebp, %esp
popl %ebp
;//stack frame
ret
.end


