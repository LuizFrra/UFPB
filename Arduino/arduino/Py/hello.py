#coding:utf-8

#Posso usar para comentarios o "" ("") ''

print "Hello World !!! "

print ("Hello World !!!")

print ("I Will Print The Number 8.") , ( (4*2) + 8 ) / 2

print 3 + 2 < 10 - 28 #Imprime False

print ("What's your name ? " )

my_name = raw_input()

print ("How Old Are You ? ")

my_age = int(raw_input())

food = ' ...I Love Ice Cream '

float_number = 3.14159283983

print ("My name is %s." %  my_name) # %s é para String

print ("Eu tenho %d  anos." %  my_age) # %d is to interger number

print (" This number rounded is %0.2f " % round(float_number) ) # to floating number is used %f

print (" My name is %r and i have %r years old and im lying when i say that i love the number %r ." % (my_name, my_age, round(float_number)))

print my_age + float_number # this sum the numbers

print my_name + food # this print the variable my_name and food together.
