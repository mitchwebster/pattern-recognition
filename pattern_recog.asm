# This program solves a match puzzle.
#
# 10/23/14	       Mitch Webster -- Current Version

.data
Reference:   .alloc 1				# allocate space for reference pattern
Candidates:  .alloc 8				# allocate space for puzzle candidates

.text
MPuzzle:	addi	$1, $0, Reference	# set memory base
		swi	582			# create and display puzzle

		lw $1, 0($1)
		addi $3,$0,14	#count2
		addi $6,$0,2	#count1
		addi $2,$0,0	#result
InitialLoop:	srlv $8,$1,$6
		andi $8,$8,3
		sllv $8,$8,$3
		add $2,$2,$8
		addi $3,$3,-2
		addi $6,$6,2
		slti $8,$6,16
		bne $8,$0,InitialLoop	#end of initial loop
		andi $3,$1,3
		add $2,$2,$3
		
		#1 - reference choice 1
		#2 - reversed choice 1
		#3 - candidate counter
		#6 - temp
		#8 - temp


Loop:		add $3,$0,$0		#register 5 holds inner loop 
Loop2:		lw $6, Candidates($3)
		beq $6,$1,Exit
		beq $6,$2,Exit
		addi $3,$3,4
		slti $6, $3, 32
		bne $6,$0,Loop2

		sll $8, $1, 12		# reference shifted left x
		andi $8,$8,65535
		srl $3,$1,4		# reference shifted right 8-x
		or $1,$8,$3		#store current reference shifted in 4

		sll $6, $2,12		# reference shifted left x
		andi $6,$6,65535
		srl $3,$2,4		# reference shifted right 8-x
		or $2,$6,$3		#store current reference shifted in 4

		j Loop
Exit:		swi	583
		jr      $31			# return to operating system

