def Min(lst,myindex):
    return min(x for idx, x in enumerate(lst) if idx != myindex)

def Delete(matrix,index1,index2):
    del matrix[index1]
    for i in matrix:
        del i[index2]
    return matrix

def PrintMatrix(matrix):
    print("---------------")
    for i in range(len(matrix)):
        print(matrix[i])
    print("---------------")

n=int(input())
matrix=[]
H=0
PathLenght=0
Str=[]
Stb=[]
res=[]
result=[]
StartMatrix=[]

for i in range(n):
    Str.append(i)
    Stb.append(i)

for i in range(n): matrix.append(list(map(int, input().split())))
	
for i in range(n):StartMatrix.append(matrix[i].copy())

for i in range(n): matrix[i][i]=float('inf')

while True:
    for i in range(len(matrix)):
        temp=min(matrix[i])
        H+=temp
        for j in range(len(matrix)):
            matrix[i][j]-=temp


    for i in range(len(matrix)):
        temp = min(row[i] for row in matrix)
        H+=temp
        for j in range(len(matrix)):
            matrix[j][i]-=temp
    NullMax=0
    index1=0
    index2=0
    tmp=0
    for i in range(len(matrix)):
        for j in range(len(matrix)):
            if matrix[i][j]==0:
                tmp=Min(matrix[i],j)+Min((row[j] for row in matrix),i)
                if tmp>=NullMax:
                    NullMax=tmp
                    index1=i
                    index2=j
    #--------------------------------------

    res.append(Str[index1]+1)
    res.append(Stb[index2]+1)
	
    oldIndex1=Str[index1]
    oldIndex2=Stb[index2]
    if oldIndex2 in Str and oldIndex1 in Stb:
        NewIndex1=Str.index(oldIndex2)
        NewIndex2=Stb.index(oldIndex1)
        matrix[NewIndex1][NewIndex2]=float('inf')
    del Str[index1]
    del Stb[index2]
    matrix=Delete(matrix,index1,index2)
    if len(matrix)==1:break
	
for i in range(0,len(res)-1,2):
	if res.count(res[i])<2:
		result.append(res[i])
		result.append(res[i+1])
for i in range(0,len(res)-1,2):
	for j in range(0,len(res)-1,2):
		if result[len(result)-1]==res[j]:
			result.append(res[j])
			result.append(res[j+1])
print("----------------------------------")
print(result)

for i in range(0,len(result)-1,2):
    if i==len(result)-2:
        PathLenght+=StartMatrix[result[i]-1][result[i+1]-1]
        PathLenght+=StartMatrix[result[i+1]-1][result[0]-1]
    else: PathLenght+=StartMatrix[result[i]-1][result[i+1]-1]
print(PathLenght)
print("----------------------------------")
input()
