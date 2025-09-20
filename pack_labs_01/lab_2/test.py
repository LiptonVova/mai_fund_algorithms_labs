result = []
numbers = [0] * 1000000000
for i in range(2, 1000000):
    if (not numbers[i]):
        result.append(i)
        for j in range(i, 1000000, i):
            numbers[j] = 1


for i in range(len(result)):
    print(f" Порядковый номер {i + 1} соответствует числу {result[i]}")
            