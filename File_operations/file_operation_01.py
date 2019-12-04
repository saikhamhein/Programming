# open the input.txt
ip = open("input.txt")
# create output.txt file with write operation
output = open("output.txt", "w")
string = ""
data_list = []
a = ip.read()
a = a.split()
print("a="+str(a))
for b in a:
    #b = a[0]
    print("b="+b)
    for c in b:
        if c == 'a':
            continue
        string += c
    print("string="+string)
    data_list = string
    print(data_list)
    string = ""


def Convert(string):
    li = list(string.split())
    return li


#a = open("input.txt")
ip.seek(0)
a = ip.read()
data_list = Convert(a)
print(data_list)
