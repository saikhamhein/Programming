import re
import os

here = os.path.dirname(os.path.abspath(__file__))  # find the working dir path
ip_file = os.path.join(here, 'input.txt')        # create correct dir path
ip = open(ip_file)


def extract_data():
    b = ""
    while 1:
        a = ip.read(1)
        if a == '\n':
            break
        b += a
    return b


def extract_num(string):

    number = re.sub(r'\D', "", string)
    return number


string = extract_data()
string = extract_num(string)
print(string)
string = extract_data()
string = extract_num(string)
print(string)
string = extract_data()
string = extract_num(string)
print(string)
