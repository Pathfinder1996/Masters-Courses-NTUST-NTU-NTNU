.globl sort

# partition(addr, lo, hi)
partition:
	# ==== 保存 ra 與分配用到的 s 系列暫存器 stack 結束時復原歸還空間 ====
    addi    sp, sp, -40     
    sd      ra, 0(sp)      
    sd      s0, 8(sp)       
    sd      s1, 16(sp)       
    sd      s2, 24(sp)
    sd      s3, 32(sp)        

	# ==== 避免在調用函式 a0 到 a3 被覆蓋 先移到 callee 的 s 系列暫存器 ====
    mv      s0, a0           # s0 = 基址
    mv      s1, a1           # s1 = lo
    mv      s2, a2           # s2 = hi

    # ==== pivot = array[lo] ====
    slli    t0, s1, 3
    add     t0, s0, t0
    ld      t1, 0(t0)

    # ==== 初始化 index i(left), j(right) ====
    addi    t2, s1, -1       # t2 = i = lo - 1
    addi    t3, s2, 1        # t3 = j = hi + 1

# === 無限迴圈 ===
loop_forever:

# === do i = i + 1, while array[i] < pivot ===
do_i_add_one:
    addi    t2, t2, 1        # i = i + 1
    slli    t4, t2, 3        # t4 = i * 8
    add     t4, s0, t4       # t4 = 基址 + i * 8
    ld      t5, 0(t4)        # t5 = array[i]
    blt     t5, t1, do_i_add_one  # if array[i] < pivot 繼續 do_i_add_one

# === do j = j - 1, while array[j] > pivot ===
do_j_sub_one:
    addi    t3, t3, -1       # j = j - 1
    slli    t6, t3, 3        # t6 = j * 8
    add     t6, s0, t6       # t6 = 基址 + j * 8
    ld      t5, 0(t6)        # s3 = array[j]
    bgt     t5, t1, do_j_sub_one  # if array[j] > pivot 繼續 do_j_sub_one

    # ==== if i >= j return j ====
    bge     t2, t3, partition_exit

    # ==== swap array[i] 和 array[j] ====
    mv      a5, t4           # a0 = &array[i]
    mv      a6, t6           # a1 = &array[j]
    jal     swap             # swap array[i] with array[j]

    # === 無限迴圈 ===
    j       loop_forever

partition_exit:
    mv      a4, t3          # a4 = j

    ld      ra, 0(sp)      
    ld      s0, 8(sp)       
    ld      s1, 16(sp)      
    ld      s2, 24(sp)
    ld 	    s3, 32(sp)    
    addi    sp, sp, 40  
    ret

# === partition 的 swap(a, b), swap array[i] with array[j] ===
swap:
    ld      t0, 0(a5)        # t0 = *a
    ld      t1, 0(a6)        # t1 = *b
    sd      t1, 0(a5)        # *a = t1
    sd      t0, 0(a6)        # *b = t0
    ret

# quicksort(addr, lo, hi)
quicksort:
	# ==== 保存 ra 與分配用到的 s 系列暫存器 stack 結束時復原歸還空間 ====
    addi    sp, sp, -32      # 保存 ra 分配 stack
    sd      ra, 0(sp)        
    sd      s0, 8(sp)       
    sd      s1, 16(sp)       
    sd      s2, 24(sp)       

    # ==== 避免在調用函式 a0 到 a3 被覆蓋 先移到 callee 的 s 系列暫存器 ====
    mv      s0, a0           # s0 = 基址
    mv      s1, a1           # s1 = lo
    mv      s2, a2           # s2 = hi

    # ==== if lo < 0 || hi < 0 || lo >= hi goto quicksort_exit ====
    blt     s1, zero, quicksort_exit
    blt     s2, zero, quicksort_exit
    bge     s1, s2, quicksort_exit

    # ==== 呼叫 partition 取 j ====
    mv      a0, s0     
    mv      a1, s1         
    mv      a2, s2        
    jal     partition		
    mv      t0, a4      	 # t0 = j 

    # ==== 遞迴左半 ====
    mv      a0, s0           # 基址
    mv      a1, s1           # lo
    addi    a2, t0, 0	     # hi = j  
    jal     quicksort

    # ==== 遞迴右半 ====
    mv      a0, s0           # 基址
    addi    a1, t0, 1        # lo = j + 1
    mv      a2, s2           # hi
    jal     quicksort

quicksort_exit:     
    ld      ra, 0(sp) 
    ld      s0, 8(sp)   
    ld      s1, 16(sp) 
    ld      s2, 24(sp)  
    addi    sp, sp, 32
    ret

# sort(addr, count)
sort:
	# ==== 保存 ra 用於回到呼叫我的下一行 分配 stack 來儲存 結束時復原歸還空間====
    addi    sp, sp, -8       # 保存 ra 分配 stack
    sd      ra, 0(sp)        

    mv      t0, a1           # t0 = array size
    addi    t0, t0, -1       # t0 = array size - 1 = hi
    mv      a1, zero         # a1 = 0 -> 給 quicksort 的 lo
    mv      a2, t0           # a2 = array size - 1 -> 給 quicksort 的 hi
    jal     quicksort        

    ld      ra, 0(sp)        
    addi    sp, sp, 8
    ret
