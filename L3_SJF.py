# Lab 3 - Shortest Job FIrst Algorithm and Gannt Chart using Python2

n= input("Enter the number of processes: ")
burst=[]
arrival=[]
for i in range (n):
	bt = input("Enter the burst time for process %d: " %(i+1)) 
	#ar = input("Enter the Arrival time for process %d: "%(i+1))
	burst.append(bt)
	#arrival.append(ar)


Twt = 0.0
Bst = 0.0
aTat = 0.0
Wt = [0]
Tat=[0]
B = list(burst)
for i in range(int(n), 0, -1):
    for j in range(1, int(n)):
        if B[j - 1] > B[j]:
            temp = B[j - 1]
            B[j - 1] = B[j]
            B[j] = temp
Wt = [0]
for i in range(1, int(n)):
    temp = int(B[i - 1]) + int(Wt[i - 1])
    Wt.append(temp)
for i in range(0, int(n)):
    Twt = Twt + Wt[i]
for i in range(0, int(n)):
    Bst = Bst + Wt[i]
for i in range(0, int(n)):
    Tat = Wt[i]+int(B[i])

print"Total Waiting Time:"+str(Twt)
print"Average Waiting Time:"+str(Twt/int(n))
print"Total Turnaround Time:"+str(Tat)
print"Average Turnaround Time:"+str(Tat/int(n))
print"\nGannt Chart : \n"
for i in range (n):
	print "%d --- P%d ---" %(Wt[i],i+1),
print str(Tat)
