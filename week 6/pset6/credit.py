from cs50 import get_int


def main():
    card = get_int("Number: ")
    digits = numberofdigits(card)
    validity = checksum(card)
    
    if validity == 1:
        if digits == 15:
            start = int(card / 10000000000000)
            if start == 34 or start == 37:
                print("AMEX")
            else:
                print("INVALID")
        elif digits == 13:
            start = int(card / 1000000000000)
            if start == 4:
                print("VISA")
            else:
                print("INVALID")
        elif digits == 16:
            start = int(card / 100000000000000)
            if start in range(51, 56, 1):
                print("MASTERCARD")
            else:
                start = int(card / 1000000000000000)
                if start == 4:
                    print("VISA")
                else:
                    print("INVALID")
        else:
            print("INVALID")
    else:
        print("INVALID")


def checksum(n):
    sum = 0
    checker = 0
    while n > 0:
        dig = n % 10
        if checker == 0:
            sum = sum + dig
            checker = 1
        else:
            dig = dig * 2
            while dig > 0:
                sum = sum + (dig % 10)
                dig = int(dig / 10)
            checker = 0
        n = int(n / 10)
    if sum % 10 == 0:
        return 1
    else:
        return 0
        
        
def numberofdigits(n):
    num = 0
    while n > 0:
        num += 1
        n = int(n / 10)
    return num


main()
                